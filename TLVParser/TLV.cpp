#include "StdAfx.h"
#include "TLV.h"

TLV::TLV(void)
{
	Tag = 0;
	Len = 0;
	memset(Value, 0, 1024);
}

TLV::~TLV(void)
{
}


