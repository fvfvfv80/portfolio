#pragma once
#include "gameNode.h"

#define MAX_BUTTOM_NUM 3
#define GRAVITY 9.8/3600
enum eButtom
{
	start,
	load,
	off
};

class AliceIntro :
	public gameNode
{
private:
	RECT _rPlayer;
	RECT _rFloor;
	float _fGravity;
	RECT _rButton[MAX_BUTTOM_NUM];
	bool _bIsLoad;
	int _iMotion;
	int _iFadeTime;
	int _iFadelevel;
	int _iMoveLevel;
		
public:
	AliceIntro();
	~AliceIntro();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fadeinout();
	
};

