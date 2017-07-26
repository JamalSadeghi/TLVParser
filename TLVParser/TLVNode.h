/**
 * @author Jamal Sadeghi, 3/14/17 9:15 AM
 */
#pragma once
#include "TLV.h"
#include <vector>
using namespace std;

class TLVNode :public TLV
{
public:
	TLVNode(void);
	~TLVNode(void);
	vector<TLV*> Childs;

	void SetTag(unsigned long TLVTag);
	void SetLen(unsigned long TLVLen);
	void SetValue(char* TLVValue, unsigned long TLVValueLen);

	unsigned long  GetTag();
	unsigned long  GetLen();
	void  GetValue(char* TLVValue);

	void Serialize(char* SerializedBuff);
	void Stream(unsigned char* StreamBuffer);
};
