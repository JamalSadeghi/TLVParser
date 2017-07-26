#include "stdafx.h"
#include "gtest/gtest.h"
#include <TlvParser.h>
TEST(TestStream, TestStreamUnconsturctedTag)
{		
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

	unsigned char StreamedBuffer[33] = { 0 };
	TlvData.Stream(StreamedBuffer);

	EXPECT_TRUE( 0 == std::memcmp( StreamedBuffer, Data, 8) );
}

TEST(TestStream, TestStreamConsturctedTag)
{
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

	unsigned char StreamedBuffer[33] = { 0 };
	TlvData.Stream(StreamedBuffer);

	EXPECT_TRUE( 0 == std::memcmp( StreamedBuffer, Data , 10 ) );
}

TEST(TestStream, TestStreamMultiLayerConsturctedTag)
{
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

	unsigned char StreamedBuffer[33] = { 0 };
	TlvData.Stream(StreamedBuffer);

	EXPECT_TRUE( 0 == std::memcmp( StreamedBuffer, Data, 16) );
}

// Test Data with constructed and not constructed tag
TEST(TestStream, TestStreamMixedTag)
{
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

	unsigned char StreamedBuffer[33] = { 0 };
	TlvData.Stream(StreamedBuffer);

	EXPECT_TRUE( 0 == std::memcmp( StreamedBuffer, Data, 14) );
}