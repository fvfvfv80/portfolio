#pragma once
#include "gameNode.h"


enum ROBOT_STATE
{
	STATE_IDLE,
	STATE_LEFT,
	STATE_RIGHT,
	STATE_UP,
	STATE_DOWN,
	STATE_TEMP,
};


enum eTOKEN_TYPE
{
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
	DARK,
	
};
enum COLOR
{
	RED,
	BLUE,
	GREEN,
	YELLOW,
	WHITE,
	ALL,
	
};
struct sTile
{
	RECT rc;
	POINT pos;
	eTOKEN_TYPE type;
	bool isGo;
	int color;
	bool isToken;

};
struct sWall
{
	RECT rc;
	bool isVer;
};
struct sToken
{
	RECT rc;
	eTOKEN_TYPE type;
	COLOR color;
	bool isOpen;
	bool isOpened;
};

struct sRobot
{
	RECT rc;
	RECT prevRc;
	POINT pos;
	POINT prevPos;
	ROBOT_STATE state;
	int speed;
	int color;
};

struct sBottom
{
	RECT rc;
};

struct sPlayer
{
	int tokenNum;

};

struct sRoute
{
	POINT record;
	sRobot* prRob;
};

class cRobotGame :
	public gameNode
{
private:
	sTile _tile[16][16];

	sRobot _robot[5];
	vector<sWall*> _wall;
	sRobot* _pRobot;
	sRobot _tRt;
	sToken _token[17];

	int _moveNum;
	vector<sRoute*> _route;
	HBRUSH _gray;
	HBRUSH _white;
	HBRUSH _red;
	HBRUSH _blue;
	HBRUSH _yellow;
	HBRUSH _green;
	HPEN _pen;
	int a;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void ImageInit();
	
	void SpeedMode();
	void NormalMode(sRobot* rt);

	void TestWallSet();
	void WallSet(POINT pt, bool isver);
	void TokenSet(int num, sTile* tk, int type, int color);

	void PlayerSet();

	



	cRobotGame();
	~cRobotGame();
};

