#pragma once

class CNode
{
public:
	CNode(void);
	CNode(const int);
	~CNode(void);
	bool hasNum(const int);
	bool addNum(const int);
	bool removeNum(const int);
	int getLen() const;
	void setNum(const int);
	CNode *next;
	const int getData();
	const int getRow();
	const int getCol();
	void setLoc(int, int);
private:
	bool m_bNum[9];
	int m_data;
	int m_len;
	int m_row;
	int m_col;
};
