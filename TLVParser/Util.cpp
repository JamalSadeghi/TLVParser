#include "Stdafx.h"
#include "Util.h"

Util::Util(void)
{
}

Util::~Util(void)
{
}

void Util::Bin2Hex(
	           unsigned char* BinDataIn, unsigned char* HexDataOut, unsigned short BinDataLength)
{
	unsigned char FormatedData[5] = { 0 };
	unsigned short i = 0;
	HexDataOut[0] = 0;
	for(i = 0; i < BinDataLength; i++)
	{
		sprintf((char*)FormatedData, "%02x", BinDataIn[i]);
		strcat((char*)HexDataOut, (char*)FormatedData);
	}
}

void Util::Hex2Bin(
	           unsigned char* HexDataIn, unsigned char* BinDataOut, unsigned short BinDataLength)
{
	unsigned long Len = strlen((char*)HexDataIn);
	char* FormatedData = new char[Len + 1];
	memset(FormatedData, 0, Len);

	unsigned short I = 0;
	for(I = 0; I < Len; I++)
	{
		if((HexDataIn[I] >= '0') && (HexDataIn[I] <= '9'))
			FormatedData[I] = (unsigned char)(HexDataIn[I] - 48);
		else
			if((HexDataIn[I] >= 'a') && (HexDataIn[I] <= 'f'))
				FormatedData[I] = (unsigned char)(HexDataIn[I] - 87);
			else
				if((HexDataIn[I] >= 'A') && (HexDataIn[I] <= 'F'))
					FormatedData[I] = (unsigned char)(HexDataIn[I] - 55);
	}
	for(Len = 0, I = 0; Len < BinDataLength; Len++, I += 2)
		BinDataOut[Len] = (unsigned char)((FormatedData[I] << 4) | (FormatedData[I + 1] & 0x0f));

	delete[] FormatedData;
}

void Util::Hex2Long(unsigned char* hexInput, long* longOutput)
{	
	char HexBuffer[9] = { 0 };
	memcpy((char*)HexBuffer, hexInput, strlen((char*)hexInput));
	PadLeft((unsigned char*)HexBuffer, 8,'0');	

	char FormatedData[9] = { 0 };
	unsigned short i = 0;
	for (i=0;i<8;i+=2)
	{
		FormatedData[i]=HexBuffer[6-i];
		FormatedData[i+1]=HexBuffer[7-i];
	}
	FormatedData[8]= 0;

	union intHex
	{
		long longData;
		char hexData[8];
	} unionData;
	Hex2Bin((unsigned char*)FormatedData, (unsigned char*)unionData.hexData, 4);
	*longOutput =unionData.longData;	
}

void Util::PadLeft(unsigned char* StrData, unsigned short Len, char Fill)
{
	unsigned long i;
	unsigned long j;
	char* FormatedStr = new char[Len + 1];
	memset(FormatedStr, Fill, Len);
	j = Len - 1;

	for (i = strlen((char*)StrData); i > 0; i--)
	{
		//Padding the StrTemp with 0 to StrLen
		FormatedStr[j--] = StrData[i-1]; 
	}
	FormatedStr[Len] = 0;
	memcpy((char*)StrData, FormatedStr, Len);
	StrData[Len] = 0;

	delete[] FormatedStr;
}

void Util::Ulong2Bin(unsigned long ulongValue, unsigned char* OutBuff)
{
	unsigned long  FindSize = ulongValue;
	short NumByte = 0;	
    while ((FindSize != 0) && (NumByte<sizeof(unsigned long))) {
		FindSize = FindSize >> 8;
		NumByte++;
	}

	memcpy(OutBuff, &ulongValue, NumByte);
	unsigned char Buff[9] = { 0 };
	memcpy(Buff, OutBuff, 4);
	int i = 0;
	for (i = 0; i < NumByte; i++)
		OutBuff[i] = Buff[NumByte - i - 1];
}