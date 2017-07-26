// TLVParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ComponentTLV.h"
#include "ChildTLV.h"
#include "LeafTLV.h"

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char Data[512] = { 0 };
	ComponentTLV* TlvTester;
	TlvTester = new ChildTLV();
	// test data
    //00E9458001081012821a8202568302568402568504313683198202238301284032588503516

	return 0;
}

