/**
 * @author Jamal Sadeghi, 3/14/17 9:15 AM
 */
#pragma once
class Util
{
public:
	Util(void);
	~Util(void);
	static void Bin2Hex(
		            unsigned char* BinDataIn, unsigned char* HexDataOut,
					unsigned short BinDataLength);
	static void Hex2Bin(
		            unsigned char* HexDataIn,unsigned  char* BinDataOut,
		            unsigned short BinDataLength);
	static void Hex2Long(unsigned char* hex_in, long* long_out);
	static void PadLeft(unsigned char* StrData, unsigned short Len, char Fill);
	static void Ulong2Bin(unsigned long ulongValue, unsigned char* OutBuff);
};
