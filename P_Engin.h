#pragma once
#include "gameNode.h"


#define GRAVITY 9.8 // [m/s]
#define PI 3.141592654f

struct s2D
{
	float x;
	float y;
};

struct sObject
{
	RECT size;
	s2D netforce;
	s2D myaccel;
	s2D myspeed;
	s2D accel;
	s2D netspeed;
	s2D reflecspeed;
	s2D forcespeed;
	s2D friction;		//마찰력
	s2D spring;
	s2D nomalforce;

	
	

	int weight;

	float e; //반발계수

	bool isfix;
	
	float hp;
};

struct sPE
{
	float gravity;
};

struct sSwitch
{
	bool graon;
	bool B;
	bool F;
};


class P_Engin :
	public gameNode
{
public:
	image* sky;
	sObject _sPl;
	sObject _sGr;
	sSwitch _sKind;
	float _gravity;
	float _speed;
	float _angle;
	RECT ground;
	RECT _stbutton;
	RECT _edbutton;
	int _squeence;
	int _sec;
	int _msec;
	float _time;
	float _timestop[3];
	bool _isbounce;
	RECT _rWrite[2];
	bool _isfloat;
	bool _iswrite[2];
	HBRUSH brush;
	int _loofx;
	int _loofy;

public:
	P_Engin();
	~P_Engin();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	

	void gra(sObject *obj);
	void  calculate_netforce(sObject *obj);
	bool debug();

	void test1(sObject *obj1, sObject *obj2);
	void writenumber(float *num,bool* out);

};
