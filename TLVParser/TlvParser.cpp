#include "StdAfx.h"
#include "TlvParser.h"
#include <typeinfo>
#include <iostream>
using namespace std;

TlvParser::TlvParser(DataFormat TagFormat)
{
	this->TagFormat = TagFormat;
}

TlvParser::~TlvParser(void)
{
   CleanUp(this->Nodes);
}

void TlvParser::UnpackData(unsigned char* Data)
{	
	vector<char> NodeData;
	int DataLen = strlen((const char*)Data);
	NodeData.insert(NodeData.end(), Data, Data + DataLen);

	unsigned long Tag = 0;
	unsigned long Len = 0;
	Tag = TLVUtil::PickTag(NodeData, this->TagFormat);
	Len = TLVUtil::PickLenght(NodeData, this->TagFormat);

	TLVNode* RootNode = new TLVNode();
	RootNode->SetTag(Tag);
	RootNode->SetLen(Len);
	char Value[1024] = { 0 };
	memcpy(Value, &NodeData[0], Len);
	RootNode->SetValue(Value, Len);

	DataToTLV(RootNode);
	this->Nodes = RootNode;
}

void TlvParser::Serialize(unsigned char* SerializedBuffer)
{
	unsigned long Tag = 0;	
    Tag = Nodes->GetTag();

    unsigned long Len = 0;
	Len = Nodes->GetLen();

	char Value[1024] = { 0 }; 
	Nodes->GetValue(Value);

	TLVUtil::Serialize(Tag, Len, (unsigned char*)Value, SerializedBuffer);
}

void TlvParser::Stream(unsigned char* StreamBuffer)
{			
	unsigned long Tag = 0;
	Tag = Nodes->GetTag();

	unsigned long Len = 0;
	Len = Nodes->GetLen();

	char Value[1024] = { 0 }; 
	Nodes->GetValue(Value);

	TLVUtil::Stream(Tag, Len, (unsigned char*)Value, StreamBuffer);
}

bool TlvParser::GetTagValue(vector<unsigned long> TagDirectory, char* TagValue)
{
	unsigned long Tag = 0;
	unsigned long Len = 0;
	char Value[1024] = {}; 

    Tag = this->Nodes->GetTag();
	if (TagDirectory.size() == 1 && TagDirectory[0] == Tag)
	{
		Len = this->Nodes->GetLen();
		this->Nodes->GetValue(Value);

		memcpy(TagValue, Value, Len);
		return true;
	}

	//unsigned long TagRequested = TagDirectory.front();	
	bool PartialTagFinded = true;
	TLVNode* SingleNode; 
	SingleNode = dynamic_cast<TLVNode*>(this->Nodes);
	unsigned short TagDirectoryIndex = 0;

	for (unsigned short i = 0; i <= TagDirectory.size(); i++)
	{
		PartialTagFinded = false;
		TagDirectoryIndex = i;
		Tag = SingleNode->GetTag();
		if (Tag != TagDirectory[TagDirectoryIndex])
		{
			return false;
		}

		TagDirectoryIndex++;
		for (unsigned int j = 0; j < SingleNode->Childs.size(); j++ )
		{
            Tag = SingleNode->Childs[j]->GetTag();
			if (Tag == TagDirectory[TagDirectoryIndex])
			{
				PartialTagFinded = true;
				if (TagDirectoryIndex == TagDirectory.size() - 1)
				{
					SingleNode->Childs[j]->GetValue(Value);
					Len = SingleNode->Childs[j]->GetLen(); 

					memcpy(TagValue, Value, Len);
					return true;
				}
				else
				{
					SingleNode =dynamic_cast<TLVNode*>(SingleNode->Childs[j]);
					break;
				}
               
			}
		}
		if (PartialTagFinded == false)
		{
			return false;
		}
	}
    
	return false;
}

bool TlvParser::SetTagValue(
                    vector<unsigned long>  TagDirectory, char* TagValue, unsigned long ValueLen)
{
	unsigned long Tag = 0;

	Tag = this->Nodes->GetTag();
	if (TagDirectory.size() == 1 && TagDirectory[0] == Tag)
	{
		this->Nodes->SetValue(TagValue, ValueLen);
		this->Nodes->SetLen(ValueLen);
		return true;
	}

//	unsigned long TagRequested = TagDirectory.front();
	unsigned short TagDirectoryIndex = 0;
	bool PartialTagFinded = true;
	TLVNode* SingleNode;
	SingleNode = dynamic_cast<TLVNode*>(this->Nodes);

	for (unsigned short i = 0; i <= TagDirectory.size(); i++)
	{
		PartialTagFinded = false;
		TagDirectoryIndex = i;
		Tag = SingleNode->GetTag();
		if (Tag != TagDirectory[TagDirectoryIndex])
		{
			return false;
		}

		TagDirectoryIndex++;
		for (unsigned int j = 0; j < SingleNode->Childs.size(); j++ )
		{
			Tag = SingleNode->Childs[j]->GetTag();
			if (Tag == TagDirectory[TagDirectoryIndex])
			{
				PartialTagFinded = true;
				if (TagDirectoryIndex == TagDirectory.size() - 1)
				{
                    this->Nodes->SetValue(TagValue, ValueLen);
					this->Nodes->SetLen(ValueLen);
					return true;
				}
				else
				{
					SingleNode =dynamic_cast<TLVNode*>(SingleNode->Childs[j]);
					break;
				}

			}
		}
		if (PartialTagFinded == false)
		{
			return false;
		}
	}

	return false;
}

void TlvParser::DataToTLV(TLVNode* CurrenNode)
{
	unsigned long Tag = 0;
	unsigned long Len = 0;

	TLVNode* TLVNodeObject;

	char Value[1024] = {}; 
	CurrenNode->GetValue(Value);
	Len = CurrenNode->GetLen();
	vector<char> NodeData;
	NodeData.insert(NodeData.end(), Value, Value + Len);
	while (NodeData.size() > 0)
	{
		Tag = TLVUtil::PickTag(NodeData, TagFormat);
		Len = TLVUtil::PickLenght(NodeData, TagFormat);
		memset(Value, 0, 1024);
		if (TLVUtil::IsTagConstructed(Tag) == true)
		{

			TLVNodeObject = new TLVNode();
			TLVNodeObject->SetTag(Tag);
			TLVNodeObject->SetLen(Len);
			memcpy(Value, &NodeData[0], Len);
			TLVNodeObject->SetValue(Value, Len);
			NodeData.erase(NodeData.begin(), NodeData.begin() + Len);
			DataToTLV(TLVNodeObject);
			CurrenNode->Childs.push_back(TLVNodeObject);
		}
		if (TLVUtil::IsTagConstructed(Tag) == false)
		{
			TLVLeaf*  TlvLeafObject = new TLVLeaf();
			TlvLeafObject->SetTag(Tag);
			TlvLeafObject->SetLen(Len);
			memcpy(Value, &NodeData[0], Len);
			TlvLeafObject->SetValue(Value, Len);
			NodeData.erase(NodeData.begin(), NodeData.begin() + Len);
			CurrenNode->Childs.push_back(TlvLeafObject);
		}
	}
}

void TlvParser::CleanUp(TLV* TlvObject)
{	
	if (typeid(*TlvObject) == typeid(TLVLeaf))
	{
		TlvObject = NULL;
		delete TlvObject;
	}
	else
	{
		TLVNode* IntermediateNode;
		IntermediateNode = dynamic_cast<TLVNode*>(TlvObject);
		for (unsigned int i = 0; i < IntermediateNode->Childs.size(); i++)
		{
			CleanUp(IntermediateNode->Childs[i]);
			delete IntermediateNode;

		}
	}
}
