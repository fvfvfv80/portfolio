#include "stdafx.h"
#include "P_Engin.h"


P_Engin::P_Engin()
{
}


P_Engin::~P_Engin()
{
}

HRESULT P_Engin::init(void)
{
	
	

	ZeroMemory(&_sPl, sizeof(_sPl));
	ZeroMemory(&_sGr, sizeof(_sGr));
	
	sky = new image;
	
	_sPl.weight = 1;
	_gravity = 0;
	_speed = 0;
	_angle=0;
	_sGr.size = RectMakeCenter(9000, WINSIZEY - 55, 180000, 120);
	_sPl.size = RectMakeCenter(100,_sGr.size.top-100, 50, 50);
	_stbutton = RectMakeCenter(980, 480, 200, 100);
	_sKind.graon = false;

	IMAGEMANAGER->addImage("sky", "image\\sky.bmp",2000 , 1500);
	IMAGEMANAGER->addImage("ground", "image\\ground.bmp", 960, 150, true, RGB(255, 0, 255));
	
	
	_sGr.e = 0.9;
	_sPl.e = 0.9;

	brush = CreateSolidBrush(RGB(10, 10, 10));

	_sPl.forcespeed.y = 0;

	_isfloat = false;
	_iswrite[1] = false;
	_iswrite[0] = false;
	_rWrite[0] = RectMakeCenter(600, 220, 200, 50);
	_rWrite[1] = RectMakeCenter(600, 400, 200, 50);
	_edbutton = RectMakeCenter(1000, 500, 200, 100);
	_sec = 0;
	_time = 0;
	_squeence = 0;
	_isbounce = false;
	
	_loofx = 0;
	_loofy = 0;

	return S_OK;
	
}

void P_Engin::release(void)
{
	SAFE_DELETE(sky);
}


void P_Engin::update(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
	//	if (_sPl.myspeed.x > 0)_sPl.myspeed.x = 0;
		//_sPl.myspeed.x -= 2;
		if (!_isbounce)_isbounce = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		//if (_sPl.myspeed.x < 0)_sPl.myspeed.x = 0;
		///_sPl.myspeed.x += 2;
	}


	if(_sec>3)
		_isbounce = true;

	gra(&_sPl);
	
	if (_sPl.size.left < WINSIZEX / 2 - 30)
	{
		OffsetRect(&_sPl.size, _sPl.netspeed.x, 0);
	}
	else
	{
		//OffsetRect(&_sGr.size, _sPl.netspeed.x, 0);
		_loofx += _sPl.netspeed.x;
	}
	if (_sPl.size.top > 200||_loofy<=0)
	{
		
		OffsetRect(&_sPl.size, 0, _sPl.netspeed.y);
	}


	test1(&_sPl, &_sGr);

	calculate_netforce(&_sPl);

	
	if (PtInRect(&_rWrite[0], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_iswrite[1] == true)_iswrite[1] = false;
			_iswrite[0] = true;
		}
	}
	else if (PtInRect(&_rWrite[1], _ptMouse))
	{

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_iswrite[0] == true)	_iswrite[0] = false;
			_iswrite[1] = true;

		}
	}
	if (PtInRect(&_stbutton, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_squeence = 1;
			
		}
	}
	if (_iswrite[0])writenumber(&_speed, &_iswrite[0]);
	else if (_iswrite[1])writenumber(&_angle, &_iswrite[1]);

	if (!_iswrite[1])
	{
		if (_angle > 180)_angle = (int)_angle % 180;
	}
	if (_squeence == 1)
	{
		_sPl.myspeed.x = _speed*cos(_angle*PI / 180);
		_sPl.myspeed.y = -_speed*sin(_angle*PI / 180);
		
		_sec++;
		_msec = _sec % 60 * 100 / 60;
		_time = _sec/60 + (float)_msec / 100;
		if (_sPl.netspeed.y == 0)
		{
			_timestop[0] = _sec;
		}
		else if (_sPl.netspeed.y == 0 && _sPl.netspeed.x)_timestop[1] = _sec;
	}
	
	debug();
}



void P_Engin::render(void)
{

	if (_squeence == 0)
	{
		RECT rc;
		char str1[128];
		char str2[128];
		char str3[128];
		char str4[128];
		char str5[128];

		
		rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 500);
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		
		if (_iswrite[0]) Rectangle(getMemDC(), _rWrite[0].left, _rWrite[0].top, _rWrite[0].right, _rWrite[0].bottom);
		else FillRect(getMemDC(), &_rWrite[0], brush);


		if (_iswrite[1]) Rectangle(getMemDC(), _rWrite[1].left, _rWrite[1].top, _rWrite[1].right, _rWrite[1].bottom);
		else FillRect(getMemDC(), &_rWrite[1], brush);

		Rectangle(getMemDC(), _stbutton.left, _stbutton.top, _stbutton.right, _stbutton.bottom);


		//우리가 기존에 텍스트뿌리던방식
		//sprintf(str, "기존방식: 촬촬촬리~");
		//TextOut(getMemDC(), 100, 100, str, strlen(str));

		//여긴 새로운 방식 (근데 쓸일이 있을랑가 모르겠당 ㅋ)
		//전부다 이미지로 할꺼 아님?
		HFONT oldFont;
		HFONT font1;

		//출력폰트 예제 1
		font1 = CreateFont(60, 0, 0, 0, 600,0, 0, 0,
			HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
		oldFont = (HFONT)SelectObject(getMemDC(), font1);
		sprintf(str1, "속도");
		TextOut(getMemDC(), WINSIZEX/2-60, 100, str1, strlen(str1));
		sprintf(str2, "각도");
		TextOut(getMemDC(), WINSIZEX / 2 - 60, 300, str2, strlen(str2));
		sprintf(str5, "시작");
		TextOut(getMemDC(), 980-55, 480-30, str5, strlen(str5));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font1);


		//출력폰트 예제 1
		font1 = CreateFont(20, 0, 0, 0, 600, 0, 0, 0,
			HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
		oldFont = (HFONT)SelectObject(getMemDC(), font1);

		sprintf_s(str3, "%f", _speed);
		sprintf_s(str4, "%f", _angle);
		TextOut(getMemDC(), 600, 220, str3, strlen(str3) -5);
		TextOut(getMemDC(), 600, 400, str4, strlen(str4) - 5);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font1);

	
	}
	else
	{
		IMAGEMANAGER->loopRender("sky", getMemDC(), &RectMake(0, -900, 2000, 1500), _loofx/15, _loofy);
		IMAGEMANAGER->loopRender("ground", getMemDC(), &RectMake(0, WINSIZEY - 120, 1200, 128), _loofx, _loofy);
		int a ;
		a = _sec % 60;
		int i;
		i = a  * 100/60;
		char str[40];
		char str1[40];
		char str2[40];
		sprintf_s(str, "%f", _sPl.netspeed.y);
		sprintf_s(str1, "%d.%d", _loofy);
		sprintf_s(str2, "%.2lf",_time);
		TextOut(getMemDC(), 300, 100, str2, strlen(str2));
		TextOut(getMemDC(), 100, 100, str, sizeof(str));
		TextOut(getMemDC(), 200, 100, str1, sizeof(str1));

		//Rectangle(getMemDC(), _sGr.size.left, _sGr.size.top, _sGr.size.right, _sGr.size.bottom);

		//IMAGEMANAGER->render("ground",getMemDC(),0,WINSIZEY-120);
		
		Ellipse(getMemDC(), _sPl.size.left, _sPl.size.top, _sPl.size.right, _sPl.size.bottom);

		if (_squeence == 2)Rectangle(getMemDC(), _edbutton.left, _edbutton.top, _edbutton.right, _edbutton.bottom);
	}
	

}

void P_Engin::gra(sObject *obj)
{
	_gravity = (*obj).weight*GRAVITY;
}


void P_Engin:: calculate_netforce(sObject *obj)
{

	(*obj).netforce.x = (*obj).friction.x + (*obj).spring.x + (*obj).nomalforce.x;
	(*obj).netforce.y = (*obj).friction.y + (*obj).spring.y + _gravity + (*obj).nomalforce.y;


	(*obj).accel.x = (*obj).myaccel.x + (*obj).netforce.x / (*obj).weight;
	(*obj).accel.y = (*obj).myaccel.y + (*obj).netforce.y / (*obj).weight;

	(*obj).forcespeed.x += (*obj).accel.x/60 ;								//1초에60번 갱신되므로
	(*obj).forcespeed.y += (*obj).accel.y/60;


	(*obj).netspeed.x = (*obj).myspeed.x+ (*obj).reflecspeed.x + (*obj).forcespeed.x;
	(*obj).netspeed.y = (*obj).myspeed.y+ (*obj).reflecspeed.y + (*obj).forcespeed.y;
}





bool P_Engin::debug()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		return true;
	}
		
	
}



void P_Engin:: test1(sObject *obj1, sObject *obj2)
{
	RECT temp;
	if (IntersectRect(&temp, &(*obj1).size, &(*obj2).size))
	{
		(*obj1).nomalforce.y = -(*obj1).netforce.y;

		//(*obj2).hp = (*obj2).hp - (*obj1).netspeed.y*(*obj1).weight;

		//(*obj1).reflecspeed.y = -(*obj1).e*(*obj2).e*(*obj1).netspeed.y;
		if (_isbounce)
		{
			(*obj1).netspeed.y = 0;
			(*obj1).myspeed.y = 0;
			(*obj1).myspeed.x = 0;
			_squeence = 2;
		}
		(*obj1).forcespeed.y = 0;


		//(*obj1).netspeed.y = 0;
		//(*obj1).myspeed.y = 0;
		
	}
	else
	{
		(*obj1).nomalforce.y = 0;
	}
}


void P_Engin::writenumber(float *num,bool* out)
{

	for (int i = 0;i < 10;i++)
	{
		if (KEYMANAGER->isOnceKeyDown(i+'0'))
		{
			if ((*num) == 0)
			{
				(*num) = i;
			}
			else
			{
				(*num) = (*num) * 10 + i;
			}

		}
	}

	if (KEYMANAGER->isOnceKeyDown('.'))
	{
		_isfloat = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		(*out) = false;
	}
}