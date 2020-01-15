#pragma once
#include "gameNode.h"

#define MAXNUM 3

class intro :
	public gameNode
{
private:
	unsigned int _title;
	RECT _selectBox;
public:
	intro();
	~intro();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

