#include "Stdafx.h"
#include "TLVUtil.h"

TLVUtil::TLVUtil(void)
{
}

TLVUtil::~TLVUtil(void)
{
}

bool TLVUtil::IsTagConstructed(unsigned long Tag)
{
	short NumByte = 0;
	unsigned int FindSize = Tag;
	while (FindSize != 0) {
		FindSize = FindSize >> 8;
		NumByte++;
	}

	unsigned char LastByteTag = 0;
	memcpy(&LastByteTag, &Tag + (NumByte - 1), 1);
	if((LastByteTag & 0x40) == 0x40)
		return true;
	else
	    return false;
}

bool TLVUtil::ValueToTlvLenFormat(
			      unsigned long ValueLen, char* TLVLenFormat,
				  unsigned short* NumBytesTLVLen)
{
	unsigned int FindSize = ValueLen;
	char NumByte = 0;
	while (FindSize != 0) {
		FindSize = FindSize >> 8;
		NumByte++;
	}
	if (NumByte <= 1 &&  ValueLen <= 127) {
		TLVLenFormat[0] =  (char)ValueLen;
		*NumBytesTLVLen = 1;
	}
	else
	{
		TLVLenFormat[0] = 0x80 + NumByte;
		memcpy(TLVLenFormat + 1, &ValueLen, NumByte);
		*NumBytesTLVLen= 1 + NumByte;
	}

	return true;
}

bool TLVUtil::Serialize(
					  unsigned long Tag, unsigned long Len, unsigned char* Value,
					  unsigned char* SerializedBuffer)
{
	char TagBuff[9] = { 0 }; 
	unsigned char TagHex[9] = { 0 };
	Util::Ulong2Bin(Tag, (unsigned char*)TagBuff);
	Util::Bin2Hex((unsigned char*)TagBuff, TagHex, strlen(TagBuff));

	int Offset = 0;
	memcpy(SerializedBuffer + Offset, TagHex, strlen((char*)TagHex));
	Offset += strlen((char*)TagHex);

	char TLVLenFormat[5] = { 0 };
	unsigned short NumBytesTLVLen = 0;
	unsigned char TLVLenFormatHex[9] = { 0 };
	ValueToTlvLenFormat(Len, TLVLenFormat, &NumBytesTLVLen);
	Util::Bin2Hex((unsigned char*)TLVLenFormat, TLVLenFormatHex, NumBytesTLVLen);

	memcpy(SerializedBuffer + Offset, TLVLenFormatHex, strlen((char*)TLVLenFormatHex));
	Offset += strlen((char*)TLVLenFormatHex);
	memcpy(SerializedBuffer + Offset, Value, Len);

	return true;
}

bool TLVUtil::Stream(
				   unsigned long Tag, unsigned long Len, unsigned char* Value,
				   unsigned char* StreamBuffer)
{
	int Offset = 0;
	char TagBuff[9] = { 0 };
	Util::Ulong2Bin(Tag, (unsigned char*)TagBuff);
	memcpy(StreamBuffer + Offset, TagBuff, strlen((char*)TagBuff));

	char TLVLenFormat[9] = { 0 };
	unsigned short NumBytesTLVLen = 0;
	Offset += strlen((char*)TagBuff);
	ValueToTlvLenFormat(Len, TLVLenFormat, &NumBytesTLVLen);

	memcpy(StreamBuffer + Offset, TLVLenFormat, NumBytesTLVLen);
	Offset += NumBytesTLVLen;
	memcpy(StreamBuffer + Offset, Value, Len);

	return true;
}

void TLVUtil::PickHexTAG(unsigned char* Tag, vector<char> &Data)
{
	unsigned char TagStr[16] = { 0 };
	unsigned char PartOfTag = 0;
	unsigned short Offset = 2;

	memset(TagStr, 0, 16);
	memcpy(TagStr, &Data[0], 2);
	Data.erase(Data.begin(), Data.begin() + 2);
	Util::Hex2Bin(TagStr, &PartOfTag, 1);

	if ((PartOfTag & TAG_MASK) == TAG_MASK)
	{
		do 
		{
			// Tag field is longer than 1 byte
			memcpy(TagStr + Offset, &Data[0], 2);
			Data.erase(Data.begin(), Data.begin() + 2);
			Util::Hex2Bin(TagStr + Offset, &PartOfTag, 1);
			Offset += 2;
		} while ((PartOfTag & 0x80) == 0x80);
	}

	memcpy(Tag, TagStr, strlen((char*)TagStr));
}

void TLVUtil::PickBinaryTAG(unsigned long* Tag, vector<char> &Data)
{
	unsigned char  TagByte = 0;
	TagByte = Data[0] & 0xff;
	// Skip padding chars
	if (TagByte == 0x00)
	{
		do {
			TagByte = Data[0] & 0xff;  
			Data.erase(Data.begin());
		} while ((TagByte == 0x00) && Data.size() > 0);
	}
	else
	{
		Data.erase(Data.begin());
	}

	// Get first byte of Tag Identifier
	int Findtag = 0x00000000;
	Findtag = TagByte;
	// Get rest of Tag identifier if required
	if ((TagByte & TAG_MASK) == TAG_MASK)
	{
		do {
			Findtag <<= 8;
			TagByte = Data[0];
			Data.erase(Data.begin());
			Findtag |= TagByte & 0xFF;
		} while ((TagByte & 0x80) == 0x80);
	}

	*Tag = Findtag;
}
unsigned long TLVUtil::PickTag(vector<char> &Data, unsigned short TagFormat)
{
	unsigned long Tag = 0;

	if (TagFormat == Hex)
	{
		unsigned char TagHex[9] = { 0 };
		PickHexTAG(TagHex, Data);
		Util::Hex2Long(TagHex, (long*)&Tag);
	}
	else if(TagFormat == Binary)
	{
		PickBinaryTAG(&Tag, Data);
	}

	return Tag;
}

bool TLVUtil::PickHexLenght(unsigned long* BuffLen, vector<char> &Data)
{
	/* if Length is greater less than 127
	   set the 8bit as 0 indicating next 7 bits is the length
	   of the message
	   if length is more than 127 then, set the first bit as 1 indicating
	   next 7 bits will indicate the length of following bytes used for
	   length */
	char Byte;
	Util::Hex2Bin((unsigned char*)&Data[0], (unsigned char*)&Byte, 1);
	Data.erase(Data.begin(), Data.begin() + 2);

	int Count = 0;
	Count = Byte & 0xFF;
	int Length = 0;
	if ((Count & 0x80) == 0x80)
	{
		// check first byte for more bytes to follow
		Count -= 0x80;
		for (Length = 0; Count > 0; Count--)
		{
			Length <<= 8;
			Util::Hex2Bin((unsigned char*)&Data[0], (unsigned char*)&Byte, 1);
			Data.erase(Data.begin(), Data.begin() + 2);
			Length |= Byte & 0xFF;
		}
	} 
	else
	{
		Length = Count;
	}

	*BuffLen = Length;

	return true;
}

bool TLVUtil::PickBinaryLenght(unsigned long* BuffLen, vector<char> &Data)
{		
	char Byte = 0;
	Byte = Data[0];
	Data.erase(Data.begin());

	int Count = 0;
	Count = Byte & 0xFF;
	int Length = 0;
	if ((Count & 0x80) == 0x80)
	{
		// check first byte for more bytes to follow
		Count -= 0x80;
		for (Length = 0; Count > 0; Count--)
		{
			Length <<= 8;
			Byte = Data[0];
			Data.erase(Data.begin());
			Length |= Byte & 0xFF;
		}
	} 
	else
	{
		Length = Count;
	}

	*BuffLen = Length;

	return true;
}

unsigned long TLVUtil::PickLenght(vector<char> &Data, unsigned short TagFormat)
{
	unsigned long Len = 0;

	if (TagFormat == Hex)
	{
		PickHexLenght(&Len, Data);
	}
	else if (TagFormat == Binary)
	{
        PickBinaryLenght(&Len, Data);
	}

	return Len;
}