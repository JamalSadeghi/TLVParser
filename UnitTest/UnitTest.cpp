// UnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include <TlvParser.h>
#include "UnpackDataHexFormat.h"
#include "SerializeData.h"
#include "StreamData.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cin>>i;
	return 0;
}

