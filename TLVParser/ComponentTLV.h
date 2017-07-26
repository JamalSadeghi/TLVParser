#pragma once

class ComponentTLV
{
public:
	ComponentTLV(void);
	~ComponentTLV(void);
	virtual void GetChild() = 0;
	virtual void GetLen() = 0;
	virtual void GetValue() = 0;
	virtual void GetTag()= 0;

	virtual void SetChild() = 0;
	virtual void SetLen() = 0;
	virtual void SetValue() = 0;
	virtual void SetTag()= 0;



};
