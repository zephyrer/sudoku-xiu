#include "StdAfx.h"

#include "NodeTable.h"

using namespace std;

CNodeTable::CNodeTable(void)
: m_bOne(false)
{
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_node[i][j].setLoc(i, j);
		}
	}
}

CNodeTable::~CNodeTable(void)
{
}

CNode* CNodeTable::GetNode(int col, int row)
{
	return &m_node[col][row];
}

CNode* CNodeTable::GetFirstNode(int col, int row)
{
	return &m_firstNode[col][row];
}

void CNodeTable::initTable(int num[9][9])
{
	for(int i = 0;i < 9;i ++)
	{
		for(int j= 0;j < 9;j ++)
		{
			if(num[i][j] == 0)
			{
				m_nodeList[8].AddNode(&m_node[i][j]);
			}
			else
			{
				m_node[i][j].setNum(num[i][j]);
				m_nodeList[0].AddNode(&m_node[i][j]);
			}
		}
	}
	

	for(CNode* pt = m_nodeList[0].GetHead();pt != NULL;pt = pt->next)
	{
		delSurround(pt->getData(), pt->getCol(), pt->getRow());
	}

	while (ConfirmNode());
}

bool CNodeTable::delSurround(int num, int col, int row)
{
	for(int i = 0;i < 9;i ++)
	{
		if(m_node[i][row].removeNum(num))
		{
			m_nodeList[m_node[i][row].getLen()].RemoveNode(&m_node[i][row]);
			m_nodeList[m_node[i][row].getLen() - 1].AddNode(&m_node[i][row]);
			if(m_node[i][row].getLen() == 1 && 
				!delSurround(m_node[i][row].getData(), m_node[i][row].getCol(), m_node[i][row].getRow()))
			{
				return false;
			}
		}
		else if(i != col && m_node[i][row].getLen() == 1 && m_node[i][row].getData() == num)
		{
			return false;
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		if(m_node[col][i].removeNum(num))
		{
			m_nodeList[m_node[col][i].getLen()].RemoveNode(&m_node[col][i]);
			m_nodeList[m_node[col][i].getLen() - 1].AddNode(&m_node[col][i]);
			if(m_node[col][i].getLen() == 1 && 
				!delSurround(m_node[col][i].getData(), m_node[col][i].getCol(), m_node[col][i].getRow()))
			{
				return false;
			}
		}
		else if(i != row && m_node[col][i].getLen() == 1 && m_node[col][i].getData() == num)
		{
			return false;
		}
	}

	int baseCol = col / 3 * 3;
	int baseRow = row / 3 * 3;

	//cout << "BaseCol:" << baseCol << "BaseRow:" << baseRow << endl;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if(m_node[baseCol + i][baseRow + j].removeNum(num))
			{
				m_nodeList[m_node[baseCol + i][baseRow + j].getLen()].RemoveNode(&m_node[baseCol + i][baseRow + j]);
				m_nodeList[m_node[baseCol + i][baseRow + j].getLen() - 1].AddNode(&m_node[baseCol + i][baseRow + j]);
				if(m_node[baseCol + i][baseRow + j].getLen() == 1 && 
					!delSurround(m_node[baseCol + i][baseRow + j].getData(), m_node[baseCol + i][baseRow + j].getCol(), m_node[baseCol + i][baseRow + j].getRow()))
				{
					return false;
				}
			}
			else if(!((baseCol + i) == col && (baseRow + j) == row) && 
				m_node[baseCol + i][baseRow + j].getLen() == 1 && m_node[baseCol + i][baseRow + j].getData() == num)
			{
				return false;
			}
		}
	}
	
	
	
	return true;
}

int CNodeTable::AwrNum()
{
	if(m_nodeList[0].getLen() == 81)
	{
		if(!m_bOne)
		{
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					m_firstNode[i][j] = m_node[i][j];
				}
			}
			m_bOne = true;
		}
		//check whether it's right.
		for(int i = 0;i < 9;i ++)
		{
			bool rowBl[9] = {false};
			bool rowCl[9] = {false};
			for(int j = 0;j < 9;j ++)
			{
				if(!rowBl[m_node[i][j].getData() - 1])
				{
					rowBl[m_node[i][j].getData() - 1] = true;
				}
				else
				{
					return 0;
				}

				if(!rowCl[m_node[j][i].getData() - 1])
				{
					rowCl[m_node[j][i].getData() - 1] = true;
				}
				else
				{
					return 0;
				}
			}
		}

		for(int i = 0;i < 3;i ++)
		{
			for(int j = 0;j < 3;j ++)
			{
				bool num[9] = {false};
				for(int k = 0;k < 3;k ++)
				{
					for(int l = 0;l < 3;l ++)
					{
						if(!num[m_node[i * 3 + k][j * 3 + l].getData() - 1])
						{
							num[m_node[i * 3 + k][j * 3 + l].getData() - 1] = true;
						}
						else
						{
							return 0;
						}
					}
				}
			}
		}
		return 1;
	}

	int lev = 1;
	for(lev;m_nodeList[lev].getLen() == 0;lev ++);
	/*
	for(int lev = 1;lev < 9;lev ++)
		{
			for(int inListIndex = 0;inListIndex < m_nodeList[lev].getLen();inListIndex ++)
			{*/
	
	int result;
	bool hasOne = false;
	
	for(int hasNum = 1;hasNum < 10;hasNum ++)
	{
		if(m_nodeList[lev].GetHead()->hasNum(hasNum))
		{

			CNode tempNode[9][9];
			CNodeList tempNodeList[9];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					tempNode[i][j] = m_node[i][j];
				}
				tempNodeList[i] = m_nodeList[i];
			}
			
			CNode *tempN = m_nodeList[lev].GetHead();
			tempN->setNum(hasNum);
			
			m_nodeList[lev].RemoveNode(tempN);
			m_nodeList[0].AddNode(tempN);
			if(!delSurround(hasNum, tempN->getCol(), tempN->getRow()))
			{
				result = 0;
			}
			else
			{
				//while (ConfirmNode());
				result = AwrNum();
			}

			//Check next.
			
			if(result == 0)
			{
				for(int i = 0;i < 9;i ++)
				{
					for(int j = 0;j < 9;j ++)
					{
						 m_node[i][j] = tempNode[i][j];
					}
					m_nodeList[i] = tempNodeList[i];
				}
				
			}
			else if(result == 2)
			{
				return 2;
			}
			else
			{
				
				if(!hasOne)
				{
					
					hasOne = true;

					for(int i = 0;i < 9;i ++)
					{
						for(int j = 0;j < 9;j ++)
						{
							m_node[i][j] = tempNode[i][j];
						}
						m_nodeList[i] = tempNodeList[i];
					}
				}
				else
				{
					
					return 2;
				}
			}
			
		}
		
	}

	if(hasOne)
	{
		return 1;
	}
	else
	{
		//This doesn't have an answer.
		return 0;
	}
		/*
		}
			}*/
}
bool CNodeTable::ConfirmNode(void)
{
	int lev = 1;
	for(int lev = 1;lev < 9;lev ++)
	{
		for(CNode *pt = m_nodeList[lev].GetHead();pt != NULL;pt = pt->next)
		{
			for(int num = 1;num < 10;num ++)
			{
				if(pt->hasNum(num))
				{
					bool otherHas = false;
					for(int i = 0;i < 9;i ++)
					{
						if(m_node[i][pt->getRow()].hasNum(num) && i != pt->getCol())
						{
							otherHas = true;
							break;
						}
					}

					if(otherHas)
					{
						otherHas = false;
						for(int i = 0;i < 9;i ++)
						{
							if(m_node[pt->getCol()][i].hasNum(num) && i != pt->getRow())
							{
								otherHas = true;
								break;
							}
						}
					}
					else
					{
						goto labelEnd2;
					}
					
					if(otherHas)
					{
						otherHas = false;
						int baseRow = pt->getRow() / 3 * 3;
						int baseCol = pt->getCol() / 3 * 3;
						for(int i = baseRow;i < baseRow + 3;i ++)
						{
							for(int j = baseCol;j < baseCol + 3;j ++)
							{
								if(m_node[j][i].hasNum(num) && !(i == pt->getRow() && j == pt->getCol()))
								{
									otherHas = true;
									goto labelEnd2;
								}
							}
						}
					}
					else
					{
						goto labelEnd2;
					}
				labelEnd2:
					if(!otherHas)
					{
						m_nodeList[pt->getLen() - 1].RemoveNode(pt);
						pt->setNum(num);
						
						m_nodeList[0].AddNode(pt);
						delSurround(num, pt->getCol(), pt->getRow());
						return true;
					}
					
				

				}
			}
		}
	}
	return false;
}
