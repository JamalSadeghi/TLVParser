#include "StdAfx.h"
#include "TLVNode.h"

TLVNode::TLVNode(void)
{
}

TLVNode::~TLVNode(void)
{

}

void TLVNode::SetTag(unsigned long TLVTag)
{
	this->Tag = TLVTag;
}

void TLVNode::SetLen(unsigned long TLVLen)
{
	this->Len = TLVLen;
}

void TLVNode::SetValue(char* TLVValue, unsigned long TLVValueLen)
{
	memcpy(this->Value, TLVValue, TLVValueLen);
}

unsigned long  TLVNode::GetTag()
{
	return Tag;
}

unsigned long  TLVNode::GetLen()
{
	return Len;
}

void  TLVNode::GetValue(char* TLVValue)
{
	memcpy(TLVValue, this->Value, Len);
}

void TLVNode::Serialize(char* SerializedBuff)
{
	TLVUtil::Serialize(Tag, Len, (unsigned char*)Value, (unsigned char*)SerializedBuff);
}

void TLVNode::Stream(unsigned char* StreamBuffer)
{
	TLVUtil::Stream(Tag, Len, (unsigned char*)Value, (unsigned char*)StreamBuffer);
}
