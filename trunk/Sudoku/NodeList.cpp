#include "StdAfx.h"
#include "NodeList.h"

using namespace std;

CNodeList::CNodeList(void)
{
	m_ptHead = NULL;
	m_ptEnd = m_ptHead;
	m_len = 0;
}

CNodeList::~CNodeList(void)
{
}

void CNodeList::AddNode(CNode *node)
{
	if(m_ptHead != NULL)
	{
		m_ptEnd->next = node;
		m_ptEnd = node;
	}
	else
	{
		m_ptHead = node;
		m_ptEnd = node;
	}

	node->next = NULL;
	m_len ++;
}

void CNodeList::RemoveNode(CNode *node)
{
	if(node == m_ptHead)
	{
		m_ptHead = m_ptHead->next;
		if(m_ptHead == NULL)
			m_ptEnd = NULL;
		m_len --;
		return;
	}

	//Removing node is not the first node.
	/*
	for(CNode* pt = m_ptHead;pt->next != NULL;pt = pt->next)
		{
			if(pt->next == node)
			{
				if(node->next == NULL)
				{
					//Check whether it's the end node.
					m_ptEnd = pt;
				}
				pt->next = pt->next->next;
				m_len --;
				return;
			}
		}*/
	

	CNode *pt = m_ptHead;
	for(pt;pt->next != node;pt = pt->next);
	pt->next = pt->next->next;
	m_len --;
	if(pt->next == NULL)
	{
		m_ptEnd = pt;
	}
}

CNode* CNodeList::GetNode(const int num)
{
	CNode *pt = m_ptHead;
	for(int i = 0;i < num;i ++)
		pt = pt->next;
	return pt;
}

CNode* CNodeList::GetHead(void)
{
	return m_ptHead;
}

const int CNodeList::getLen()
{
	return m_len;
}