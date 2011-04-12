#pragma once
#include "node.h"
#include "NodeList.h"

class CNodeTable
{
public:
	CNodeTable(void);
	~CNodeTable(void);
	void initTable(int [9][9]);
	CNode *GetNode(int, int);
	CNode *GetFirstNode(int, int);
	bool delSurround(int, int, int);
	int AwrNum();
private:
	CNode m_node[9][9];
	CNodeList m_nodeList[9];
	CNode m_firstNode[9][9];
public:
	bool ConfirmNode(void);
private:
	bool m_bOne;
};
