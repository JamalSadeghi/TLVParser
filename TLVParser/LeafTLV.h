#pragma once
#include "ComponentTLV.h"
class LeafTLV:public ComponentTLV
{
public:
	LeafTLV(void);
	~LeafTLV(void);
	void GetChild();
	void GetLen();
	void GetValue();
	void GetTag();

	void SetChild();
	void SetLen();
	void SetValue();
	void SetTag();
};
