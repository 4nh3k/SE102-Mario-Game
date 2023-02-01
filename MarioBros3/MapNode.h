#pragma once
#define NULL 0
class MapNode
{
	int id;
	int x, y;
	int l, r, t, b;
public: 
	MapNode* Left;
	MapNode* Right;
	MapNode* Bot;
	MapNode* Top;
	MapNode(int id, int x ,int y,int left, int right, int top, int bot)
	{
		this->id = id;
		this->x = x;
		this->y = y;
		this->l = left;
		this->r = right;
		this->t = top;
		this->b = bot;
		Left = NULL;
		Right = NULL;
		Bot = NULL;
		Top = NULL;
	}
	void GetNextNode(int& l, int& r, int &t, int &b)
	{
		l = this->l;
		r = this->r;
		b = this->b;
		t = this->t;
	}
	int GetId()
	{
		return this->id;
	}
	void GetPos(int& x, int& y)
	{
		x = this->x;
		y = this->y;
	}
};

