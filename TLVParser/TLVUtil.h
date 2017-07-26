/**
 * @author Jamal Sadeghi, 3/14/17 9:15 AM
 */
#pragma once
#include "DataFormat.h"
class TLVUtil
{
public:

	TLVUtil(void);
	~TLVUtil(void);

	static bool IsTagConstructed(unsigned long Tag);
	static bool ValueToTlvLenFormat(
		            unsigned long ValueLen, char* TLVLenFormat,
					unsigned short* NumBytesTLVLen);
	static bool Serialize(
					unsigned long Tag, unsigned long Len, unsigned char* Value,
					unsigned char* SerializedBuffer);
	static bool Stream(
					unsigned long Tag, unsigned long Len, unsigned char* Value,
		            unsigned char* StreamBuffer);

	static void PickHexTAG(unsigned char* Tag, vector<char> &Data);
	static void PickBinaryTAG(unsigned long* Tag, vector<char> &Data);
	static unsigned long PickTag(vector<char> &Data, unsigned short TagFormat);

	static bool PickHexLenght(unsigned long* BuffLen, vector<char> &Data);
	static bool PickBinaryLenght(unsigned long* BuffLen, vector<char> &Data);
	static unsigned long PickLenght(vector<char> &Data, unsigned short TagFormat);

private:
	static const unsigned char TAG_MASK = 0x1F;
};
