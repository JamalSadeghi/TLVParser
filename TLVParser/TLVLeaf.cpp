#include "StdAfx.h"
#include "TLVLeaf.h"

TLVLeaf::TLVLeaf(void)
{
}

TLVLeaf::~TLVLeaf(void)
{
}

void TLVLeaf::SetTag(unsigned long TLVTag)
{
	this->Tag = TLVTag;
}

void TLVLeaf::SetLen(unsigned long TLVLen)
{
    this->Len = TLVLen;
}

void TLVLeaf::SetValue(char* TLVValue, unsigned long TLVValueLen)
{
    memcpy(this->Value, TLVValue, TLVValueLen);
}

unsigned long  TLVLeaf::GetTag()
{
	return Tag;
}

unsigned long  TLVLeaf::GetLen()
{
	return Len;
}

void  TLVLeaf::GetValue(char* TLVValue)
{
	memcpy(TLVValue, this->Value, Len);
}

void TLVLeaf::Serialize(char* SerializedBuff)
{
	TLVUtil::Serialize(Tag, Len, (unsigned char*)Value, (unsigned char*)SerializedBuff);
}

void TLVLeaf::Stream(unsigned char* StreamBuffer)
{
	TLVUtil::Stream(Tag, Len, (unsigned char*)Value, (unsigned char*)StreamBuffer);
}