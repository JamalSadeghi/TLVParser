#include "stdafx.h"
#include "gtest/gtest.h"
#include <TlvParser.h>
TEST(TestUnpack, TestUnpackUnconsturctedTagHexFormat)
{	
	vector<unsigned long> TagDirectoty;

	vector <char> Result;
	unsigned char Data[33] = { 0 };
	unsigned char OupPutData[513] = { 0 };
	memcpy(Data, "e70aa0011a1012", 18);
	TlvParser TlvData(Hex);
	TlvData.UnpackData(Data);

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "a0011a1012", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xa0); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "1", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7);
	TagDirectoty.push_back(0xa1); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "2", strlen( (char*)OupPutData ) ) );
}

TEST(TestUnpack, TestUnpackConsturctedTagHexFormat)
{
	unsigned char Data[33] = { 0 };
	unsigned char OupPutData[513] = { 0 };
	vector<unsigned long> TagDirectoty;

	memcpy(Data, "e70ee40aa0011a1012", 18);
	TlvParser TlvData(Hex);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "1", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "e40aa0011a1012", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "a0011a1012", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa1);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "2", strlen( (char*)OupPutData ) ) );
}

TEST(TestUnpack, TestUnpackMultiLayerConsturctedTagHexFormat)
{
	unsigned char Data[33] = { 0 };
	unsigned char OupPutData[513] = { 0 };
	vector<unsigned long> TagDirectoty;

	memcpy(Data, "e718e41480011a00B80012810222", 28);
	TlvParser TlvData(Hex);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "80012810222", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "e41480011a00B80012810222", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "80011a00B80012810222", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0x81);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "22", strlen( (char*)OupPutData ) ) );
}

// Test Data with constructed and not constructed tag
TEST(TestUnpack, TestUnpackMixedTagHexFormat)
{
	unsigned char Data[33] = { 0 };
	unsigned char OupPutData[513] = { 0 };
	vector<unsigned long> TagDirectoty;

	memcpy(Data, "e714a00222e40aa0011a1012", 24);
	TlvParser TlvData(Hex);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "1", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "a00222e40aa0011a1012", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "a0011a1012", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa1);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "2", strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, "22", strlen( (char*)OupPutData ) ) );
}