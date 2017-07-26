/**
 * @author Jamal Sadeghi, 3/14/17 9:15 AM
 */
#pragma once

class TLV
{

public:
	TLV(void);
	~TLV(void);

	virtual void SetTag(unsigned long TLVTag) = 0;
	virtual void SetLen(unsigned long TLVLen)  = 0;
	virtual void SetValue(char* TLVValue, unsigned long TLVValueLen) = 0;

	virtual unsigned long  GetTag() = 0;
	virtual unsigned long  GetLen()  = 0;
	virtual void  GetValue(char* TLVValue) = 0;

	virtual void Serialize(char* SerializedBuffer) = 0;
	virtual void Stream(unsigned char* StreamBuffer) =  0;
protected:
	unsigned long Tag;
	unsigned long Len;
	char Value[1024];
};
