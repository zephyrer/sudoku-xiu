#pragma once
#include "Node.h"

class CNodeList
{
public:
	CNodeList(void);
	~CNodeList(void);
	void AddNode(CNode *);
	void RemoveNode(CNode *);
	CNode *GetNode(const int);
	CNode *GetHead(void);
	const int getLen();
private:
	CNode *m_ptHead;
	CNode *m_ptEnd;
	int m_len;
};
