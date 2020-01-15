#include "stdafx.h"
#include "AliceIntro.h"


AliceIntro::AliceIntro()
{
}


AliceIntro::~AliceIntro()
{
}

HRESULT AliceIntro::init(void)
{
	_rButton[start] = RectMakeCenter(200, 450, 80, 100);
	_rButton[load] = RectMakeCenter(600, 450, 80, 100);
	_rButton[off] = RectMakeCenter(1000, 450, 80, 100);
	_rPlayer = RectMakeCenter(600, 500, 50, 80);
	_rFloor = RectMakeCenter(600, 550, 1200, 100);
	_iMotion = 0;
	_fGravity = 0;
	//fadeout
	_iFadelevel = 0;
	_iFadeTime = 0;

	//움직이는 단계
	_iMoveLevel = 0;
	return S_OK;
}
void AliceIntro::release(void)
{
	
}
void AliceIntro::update(void)
{
	RECT temp;
	if (_iFadelevel == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			OffsetRect(&_rPlayer, -4, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			OffsetRect(&_rPlayer, 4, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{

			_iMotion = 2;
		}

	}
	
	_fGravity += GRAVITY * 100;

	OffsetRect(&_rPlayer, 0, _fGravity);

	if (IntersectRect(&temp, &_rPlayer, &_rFloor))
	{
		_rPlayer.bottom = _rFloor.top;
		_rPlayer.top = _rPlayer.bottom - 80;
		_fGravity = 0;
		_iMotion = 1;
	}
	if (_iMotion == 2)
	{
		OffsetRect(&_rPlayer, 0, -7);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (IntersectRect(&temp, &_rPlayer, &_rButton[start]))
		{
			_iFadelevel = 1;
			
			if (_iMoveLevel == 2)
			{
				char temp[32];
				vector<string> vStr;
				vStr.push_back(itoa(0, temp, 10));

				//vStr.push_back(itoa(_rocket->getY(), temp, 10));

				TXTDATA->txtSave("save\\isSave.txt", vStr);
				SCENEMANAGER->changeScene("world");
			}
			

		}
		else if (IntersectRect(&temp, &_rPlayer, &_rButton[load]))
		{
			_iFadelevel = 1;
			
			if (_iMoveLevel == 2)
			{
				char temp[32];
				vector<string> vStr;
				vStr.push_back(itoa(1, temp, 10));

				//vStr.push_back(itoa(_rocket->getY(), temp, 10));

				TXTDATA->txtSave("save\\isSave.txt", vStr);
				SCENEMANAGER->changeScene("world");
			}
		}
	}

	if (IntersectRect(&temp, &_rPlayer, &_rButton[start]))
	{

		if (_iMoveLevel == 2)
		{
			char temp[32];
			vector<string> vStr;
			vStr.push_back(itoa(0, temp, 10));

			//vStr.push_back(itoa(_rocket->getY(), temp, 10));

			TXTDATA->txtSave("save\\isSave.txt", vStr);
			SCENEMANAGER->changeScene("world");
		}


	}
	else if (IntersectRect(&temp, &_rPlayer, &_rButton[load]))
	{

		if (_iMoveLevel == 2)
		{
			char temp[32];
			vector<string> vStr;
			vStr.push_back(itoa(1, temp, 10));

			//vStr.push_back(itoa(_rocket->getY(), temp, 10));

			TXTDATA->txtSave("save\\isSave.txt", vStr);
			SCENEMANAGER->changeScene("world");
		}
	}
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	if (PtInRect(&_rButton[start], _ptMouse))
	//	{
	//		char temp[32];
	//		vector<string> vStr;
	//		vStr.push_back(itoa(0, temp, 10));

	//		//vStr.push_back(itoa(_rocket->getY(), temp, 10));

	//		TXTDATA->txtSave("save\\isSave.txt", vStr);
	//		SCENEMANAGER->changeScene("world");

	//	}
	//	else if (PtInRect(&_rButton[load], _ptMouse))
	//	{
	//		char temp[32];
	//		vector<string> vStr;
	//		vStr.push_back(itoa(1, temp, 10));

	//		//vStr.push_back(itoa(_rocket->getY(), temp, 10));

	//		TXTDATA->txtSave("save\\isSave.txt", vStr);
	//		SCENEMANAGER->changeScene("world");
	//		
	//	}
	//}
	
}


void AliceIntro::render(void)
{
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _rButton[i].left, _rButton[i].top, _rButton[i].right, _rButton[i].bottom);

	}
	char str[64];
	sprintf_s(str, "%d", _bIsLoad);
	TextOut(getMemDC(), 60, 85, str, sizeof(str) - 3);
	Rectangle(getMemDC(), _rPlayer.left, _rPlayer.top, _rPlayer.right, _rPlayer.bottom);
	Rectangle(getMemDC(), _rFloor.left, _rFloor.top, _rFloor.right, _rFloor.bottom);
	fadeinout();

}




void AliceIntro::fadeinout()
{
	if (_iFadelevel == 1)
	{
		if (_iFadeTime<255)
		{
			_iFadeTime += 5;
		}
		else if (_iFadeTime >= 255)_iFadelevel = 2;
		IMAGEMANAGER->alphaRender("black", getMemDC(), _iFadeTime);
	}
	else if (_iFadelevel == 2)
	{
		if (_iFadeTime>0)_iFadeTime -= 5;
		else if (_iFadeTime <=0)_iFadelevel = 3;
		//if()movePlace();
		_iMoveLevel = 2;
		IMAGEMANAGER->alphaRender("black", getMemDC(), _iFadeTime);


	}
	//if (_iFadelevel == 3)_iMoveLevel = 2;
	//
};