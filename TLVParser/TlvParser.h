/**
 * @author Jamal Sadeghi, 3/14/17 9:15 AM
 */
#pragma once
#include "TLVNode.h"
#include "TLVLeaf.h"
#include "Util.h"
#include "TLVUtil.h"
#include "DataFormat.h"

class TlvParser
{	
public:
	TlvParser(DataFormat TagFormat);
	~TlvParser(void);

    void UnpackData(unsigned char* Data);
	//Serialize applies for hex format and Stream format
	void Serialize(unsigned char* SerializedBuffer);
	void Stream(unsigned char* StreamBuffer);

	bool GetTagValue(vector<unsigned long>  TagDirectory, char* TagValue);
	bool SetTagValue( vector<unsigned long>  TagDirectory, char* TagValue, unsigned long ValueLen);

private:
	TLV* Nodes;
	DataFormat TagFormat;

	void DataToTLV(TLVNode* CurrenNode);
	void CleanUp(TLV* TlvObject);
};
