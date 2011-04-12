#include "StdAfx.h"
#include "Node.h"

using namespace std;

CNode::CNode(void)
{
	for(int i = 0;i < 9;i ++)
	{
		m_bNum[i] = true;
	}
	m_len = 9;
}

CNode::CNode(const int num)
{
	for(int i = 0;i < 9;i ++)
	{
		this->m_bNum[i] = false;
	}
	m_len = 1;
	m_data = num;
}

CNode::~CNode(void)
{
}

//whether the node has the num
bool CNode::hasNum(const int num)
{
	return m_bNum[num - 1];
}

//Add the num to the node, if it already has, return false, else true
bool CNode::addNum(const int num)
{
	if(this->m_bNum[num - 1])
	{
		return false;
	}
	else
	{
		if(m_len == 1 && m_data == num)
		{
			return false;
		}
		else if(m_len == 1)
		{
			m_bNum[m_data - 1] = true;
			m_bNum[num - 1] = true;
			m_len ++;
			return true;
		}
		else
		{
			this->m_bNum[num - 1] = true;
			m_len ++;
			return true;
		}
	}
}

int CNode::getLen() const
{
	return m_len;
}

bool CNode::removeNum(const int num)
{
	if(this->m_bNum[num - 1])
	{
		this->m_bNum[num - 1] = false;
		m_len --;
		if(m_len == 1)
		{
			//Has only one num, number confirmed.
			for(int i = 0;i < 9;i ++)
			{
				if(this->m_bNum[i])
				{
					m_data = i + 1;
					this->m_bNum[i] = false;
					//len = 0;
					return true;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

//Known the node has only one num, number confirmed
void CNode::setNum(const int num)
{
	for(int i = 0;i < 9;i ++)
	{
		this->m_bNum[i] = false;
	}

	m_data = num;
	m_len = 1;
}

const int CNode::getData()
{
	return m_data;
}

const int CNode::getRow()
{
	return m_row;
}

const int CNode::getCol()
{
	return m_col;
}

void CNode::setLoc(int col, int row)
{
	m_row = row;
	m_col = col;
}