#include "stdafx.h"
#include "gtest/gtest.h"
#include <TlvParser.h>
TEST(TestUnpack, TestUnpackUnconsturctedTagBinaryFormat)
{	
	vector<unsigned long> TagDirectoty;
	unsigned char OupPutData[513] = { 0 };
	unsigned char ExpectedBuffer[33] = { 0 };
	unsigned char Data[33] = { 0 };
	Data[0] = 0xe7;
	Data[1] = 0x06;
	Data[2] = 0xa0;
	Data[3] = 0x01;
	Data[4] = 0x01;
	Data[5] = 0xa1;
	Data[6] = 0x01;
	Data[7] = 0x02;

	TlvParser TlvData(Binary);
	TlvData.UnpackData(Data);
	
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memcpy(ExpectedBuffer, Data + 2, 6);
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)ExpectedBuffer ) ) );

	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xa0); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x01;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7);
	TagDirectoty.push_back(0xa1); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );
}

TEST(TestUnpack, TestUnpackConsturctedTagBinaryFormat)
{	
	unsigned char OupPutData[513] = { 0 };
	unsigned char ExpectedBuffer[33] = { 0 };
	vector<unsigned long> TagDirectoty;
	unsigned char Data[33] = { 0 };
	Data[0] = 0xe7;
	Data[1] = 0x08;
	Data[2] = 0xe4;
	Data[3] = 0x06;
	Data[4] = 0xa0;
	Data[5] = 0x01;
	Data[6] = 0x01;
	Data[7] = 0xa1;
	Data[8] = 0x01;
	Data[9] = 0x02;
	TlvParser TlvData(Binary);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	ExpectedBuffer[0] = 0x01;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0xe4;
    ExpectedBuffer[1] = 0x06;
	ExpectedBuffer[2] = 0xa0;
	ExpectedBuffer[3] = 0x01;
	ExpectedBuffer[4] = 0x01;
    ExpectedBuffer[5] = 0xa1;
	ExpectedBuffer[6] = 0x01;
	ExpectedBuffer[7] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0xa0;
	ExpectedBuffer[1] = 0x01;
	ExpectedBuffer[2] = 0x01;
	ExpectedBuffer[3] = 0xa1;
	ExpectedBuffer[4] = 0x01;
	ExpectedBuffer[5] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa1);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );
}

TEST(TestUnpack, TestUnpackMultiLayerConsturctedTagBinaryFormat)
{	
	unsigned char OupPutData[513] = { 0 };
	unsigned char ExpectedBuffer[33] = { 0 };
	vector<unsigned long> TagDirectoty;
	unsigned char Data[33] = { 0 };
	Data[0] = 0xe7;
	Data[1] = 0x0e;
	Data[2] = 0xe4;
	Data[3] = 0x0c;
	Data[4] = 0x80;
	Data[5] = 0x01;
	Data[6] = 0x01;
	Data[7] = 0xa0;
	Data[8] = 0x07;
	Data[9] = 0x80;
	Data[10] = 0x01;
	Data[11] = 0x02;
	Data[12] = 0x81;
	Data[13] = 0x02;
	Data[14] = 0x02;
	Data[15] = 0x02;

	TlvParser TlvData(Binary);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);

	ExpectedBuffer[0] = 0x80;
	ExpectedBuffer[1] = 0x01;
	ExpectedBuffer[2] = 0x02;
	ExpectedBuffer[3] = 0x81;
	ExpectedBuffer[4] = 0x02;
	ExpectedBuffer[5] = 0x02;
	ExpectedBuffer[6] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);

	ExpectedBuffer[0] = 0xe4;
	ExpectedBuffer[1] = 0x0c;
	ExpectedBuffer[2] = 0x80;
	ExpectedBuffer[3] = 0x01;
	ExpectedBuffer[4] = 0x01;
	ExpectedBuffer[5] = 0xa0;
	ExpectedBuffer[6] = 0x07;
	ExpectedBuffer[7] = 0x80;
	ExpectedBuffer[8] = 0x01;
	ExpectedBuffer[9] = 0x02;
	ExpectedBuffer[10] = 0x81;
	ExpectedBuffer[11] = 0x02;
	ExpectedBuffer[12] = 0x02;
	ExpectedBuffer[13] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x80;
	ExpectedBuffer[1] = 0x01;
	ExpectedBuffer[2] = 0x01;
	ExpectedBuffer[3] = 0xa0;
	ExpectedBuffer[4] = 0x07;
	ExpectedBuffer[5] = 0x80;
	ExpectedBuffer[6] = 0x01;
	ExpectedBuffer[7] = 0x02;
	ExpectedBuffer[8] = 0x81;
	ExpectedBuffer[9] = 0x02;
	ExpectedBuffer[10] = 0x02;
	ExpectedBuffer[11] = 0x02;	
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );


	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0x81);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(OupPutData, 0, 512);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x02;
	ExpectedBuffer[1] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );
}

// Test Data with constructed and not constructed tag
TEST(TestUnpack, TestUnpackMixedTagBinaryFormat)
{	
	unsigned char OupPutData[513] = { 0 };
	unsigned char ExpectedBuffer[33] = { 0 };
	vector<unsigned long> TagDirectoty;
	unsigned char Data[33] = { 0 };
	Data[0] = 0xe7;
	Data[1] = 0x0c;
	Data[2] = 0xa0;
	Data[3] = 0x02;
	Data[4] = 0x02;
	Data[5] = 0x02;
	Data[6] = 0xe4;
	Data[7] = 0x06;
	Data[8] = 0xa0;
	Data[9] = 0x01;
	Data[10] = 0x01;
	Data[11] = 0xa1;
	Data[12] = 0x01;
	Data[13] = 0x02;

	TlvParser TlvData(Binary);
	TlvData.UnpackData(Data);

	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x01;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0xa0;
	ExpectedBuffer[1] = 0x02;
	ExpectedBuffer[2] = 0x02;
	ExpectedBuffer[3] = 0x02;
	ExpectedBuffer[4] = 0xe4;
	ExpectedBuffer[5] = 0x06;
	ExpectedBuffer[6] = 0xa0;
	ExpectedBuffer[7] = 0x01;
	ExpectedBuffer[8] = 0x01;
	ExpectedBuffer[9] = 0xa1;
	ExpectedBuffer[10] = 0x01;
	ExpectedBuffer[11] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0xa0;
	ExpectedBuffer[1] = 0x01;
	ExpectedBuffer[2] = 0x01;
	ExpectedBuffer[3] = 0xa1;
	ExpectedBuffer[4] = 0x01;
	ExpectedBuffer[5] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xe4);
	TagDirectoty.push_back(0xa1);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );

	memset(OupPutData, 0, 512);
	TagDirectoty.clear();
	TagDirectoty.push_back(0xe7); 
	TagDirectoty.push_back(0xa0);
	TlvData.GetTagValue(TagDirectoty, (char*)OupPutData);
	memset(ExpectedBuffer, 0, 33);
	ExpectedBuffer[0] = 0x02;
	ExpectedBuffer[1] = 0x02;
	EXPECT_TRUE( 0 == std::memcmp( OupPutData, ExpectedBuffer, strlen( (char*)OupPutData ) ) );
}