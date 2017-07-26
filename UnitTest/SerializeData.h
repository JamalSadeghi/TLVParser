#include "stdafx.h"
#include "gtest/gtest.h"
#include <TlvParser.h>
TEST(TestSerialize, TestSerializeUnconsturctedTag)
{		
	TlvParser TlvData(Hex);
	unsigned char Data[33] = { 0 };
	memcpy(Data, "e70aa0011a1012", 18);
	TlvData.UnpackData(Data);

	unsigned char SerializedData[513] = { 0 };
	TlvData.Serialize(SerializedData);

	EXPECT_TRUE( 0 == std::memcmp( SerializedData, Data, strlen( (char*)SerializedData ) ) );
}

TEST(TestSerialize,  TestSerializeConsturctedTag)
{	
	TlvParser TlvData(Hex);
	unsigned char Data[33] = { 0 };
	memcpy(Data, "e70ee40aa0011a1012", 18);
	TlvData.UnpackData(Data);

	unsigned char SerializedData[513] = { 0 };
	TlvData.Serialize(SerializedData);

	EXPECT_TRUE( 0 == std::memcmp( SerializedData, Data, strlen( (char*)SerializedData ) ) );
}

TEST(TestSerialize,  TestSerializeMultiLayerConsturctedTag)
{			
	TlvParser TlvData(Hex);
	unsigned char Data[33] = { 0 };
	memcpy(Data, "e718e41480011a00B80012810222", 28);
	TlvData.UnpackData(Data);

	unsigned char SerializedData[513] = { 0 };
	TlvData.Serialize(SerializedData);

	EXPECT_TRUE( 0 == std::memcmp( SerializedData, Data, strlen( (char*)SerializedData ) ) );
}

// Test Data with constructed and not constructed tag
TEST(TestSerialize,  TestSerializeMixedTag)
{			
	TlvParser TlvData(Hex);
	unsigned char Data[33] = { 0 };
	memcpy(Data, "e714a00222e40aa0011a1012", 24);
	TlvData.UnpackData(Data);

	unsigned char SerializedData[513] = { 0 };
	TlvData.Serialize(SerializedData);

	EXPECT_TRUE( 0 == std::memcmp( SerializedData, Data, strlen( (char*)SerializedData ) ) );
}