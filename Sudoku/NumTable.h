#pragma once

class CNumTable
{
public:
	CNumTable(void);
	~CNumTable(void);
	void CreateNumTbe(int [9][9]);
private:
	void ListAdd(int* &, int &, int);
	void ListMus(int* &, int &, int);
	bool CreateTable(int, int);
	int table[9][9];
	int CreateNew(int* &, int);
	int Random(int);
	int finRes[9][9];
};
