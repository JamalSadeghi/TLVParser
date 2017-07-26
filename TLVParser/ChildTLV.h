#pragma once
#include "ComponentTLV.h"
#include <vector>
class ChildTLV:public ComponentTLV
{
	std::vector<ComponentTLV*> ChildTag;
public:
	ChildTLV(void);
	~ChildTLV(void);

	void GetChild();
	void GetLen();
	void GetValue();
	void GetTag();

	void SetChild();
	void SetLen();
	void SetValue();
	void SetTag();
};
