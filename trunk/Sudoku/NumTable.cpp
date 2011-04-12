#include "StdAfx.h"
#include <ctime>
#include "NumTable.h"

using namespace std;

CNumTable::CNumTable(void)
{
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			table[j][i] = 0;
		}
	}
	srand((unsigned) time(NULL));
}

CNumTable::~CNumTable(void)
{
}

void CNumTable::CreateNumTbe(int tbe[9][9])
{
	CreateTable(0, 0);
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			tbe[i][j] = table[i][j];
		}
	}
}



void CNumTable::ListAdd(int* &head, int &size, int num)	//add a num to a full list.
{
	bool has = false;
	for(int i = 0;i < size;i ++)
	{
		if(*(head + i) == num)
		{
			has = true;
			break;
		}
	}

	// doesn't have the num add it to the list
	if(!has)
	{
		int* pt = head;
		head = new int[size + 1];
		//copy the num to the new list.
		for(int i = 0;i < size;i ++)
		{
			*(head + i) = *(pt + i);
		}

		*(head + size) = num;
		delete[] pt;
		size ++;
	}
}

void CNumTable::ListMus(int* &head, int &size, int num)	//add a num to a full list.
{
	for(int index = 0;index < size;index ++)
	{
		if(*(head + index) == num)
		{
			int* pt = head;
			head = new int[size - 1];

			//Copy the old data to the new list.
			for(int i = 0;i < index;i ++)
			{
				*(head + i) = *(pt + i);
			}

			for(int i = index;i < size - 1;i ++)
			{
				*(head + i) = *(pt + i + 1);
			}

			size --;
			delete[] pt;
			break;
		}
	}

}

bool CNumTable::CreateTable(int row, int col)
{
	/*
	0 1 2  3 4 5  6 7 8
	1
	2

	3
	4
	5

	6
	7
	8*/

	if(9 > row)
	{
		int *range = NULL;

		int num[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		range = new int[9 - row];
		for(int i = 0;i < row;i ++)
		{
			num[table[i][col] - 1] = 0;
		}

		int left = 0; 
		int right = 0;

		// add the acceptable num to the range.
		while(right < 9)
		{
			if(num[right] != 0)
			{
				range[left] = num[right];
				left ++;
				right ++;
			}
			else
			{
				right ++;
			}
		}

		// create the num.

		int size = 9 - row;

		for(int i = 0;i < col;i ++)
		{
			ListMus(range, size, table[row][i]);
		}

		if(0 == col % 3)
		{
			if (1 == row % 3)
			{

				ListMus(range, size, table[row - 1][col + 1]);
				ListMus(range, size, table[row - 1][col + 2]);
			} else if (2 == row % 3)
			{

				ListMus(range, size, table[row - 1][col + 1]);
				ListMus(range, size, table[row - 1][col + 2]);
				ListMus(range, size, table[row - 2][col + 1]);
				ListMus(range, size, table[row - 2][col + 2]);
			}
		} else if(1 == col % 3)
		{
			if (1 == row % 3)
			{

				ListMus(range, size, table[row - 1][col - 1]);
				ListMus(range, size, table[row - 1][col + 1]);
			} else if (2 == row % 3)
			{

				ListMus(range, size, table[row - 1][col + 1]);
				ListMus(range, size, table[row - 2][col + 1]);
				ListMus(range, size, table[row - 1][col - 1]);
				ListMus(range, size, table[row - 2][col - 1]);
			}
		} else if(2 == col % 3)
		{
			if (1 == row % 3)
			{

				ListMus(range, size, table[row - 1][col - 1]);
				ListMus(range, size, table[row - 1][col - 2]);
			} else if (2 == row % 3)
			{

				ListMus(range, size, table[row - 1][col - 1]);
				ListMus(range, size, table[row - 2][col - 1]);
				ListMus(range, size, table[row - 1][col - 2]);
				ListMus(range, size, table[row - 2][col - 2]);
			}
		}

		//Create the random.
		bool found = false;

		for(int i = size;i > 0;i --)
		{
			table[row][col] = CreateNew(range, i);
			bool result;
			if(col < 8)
			{
				result = CreateTable(row, col + 1);
			}
			else
			{
				result = CreateTable(row + 1, 0);
			}
			if(result)
			{
				delete[] range;
				found = true;
				return true;
			}
		}

		if(!found)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		for(int i = 0;i < 9;i ++)
		{
			for(int j = 0;j < 9;j ++)
			{
				finRes[i][j] = table[i][j];
			}
		}
		return true;
	}
}

int CNumTable::CreateNew(int* &head, int rge)
{
	int tmp = Random(rge);
	int* pt = head;
	head = new int[rge - 1];

	int index = 0;
	for(index;index < tmp;index ++)
	{
		*(head + index) = *(pt + index);
	}

	index ++;

	for(index;index < rge;index ++)
	{
		*(head + index - 1) = *(pt + index );
	}

	int val = *(pt + tmp);
	delete[] pt;

	return val;
}

int CNumTable::Random(int rge)
{
	return (rand() % rge);
}