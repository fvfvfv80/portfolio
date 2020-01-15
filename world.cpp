#include "stdafx.h"
#include "world.h"


world::world()
{

}


world::~world()
{
}


HRESULT world:: init(void)
{
	

	ZeroMemory(&_sAliceFrame, sizeof(_sAliceFrame));
	ZeroMemory(&_sStructure, sizeof(_sStructure));
	ZeroMemory(&_sMStructure, sizeof(_sMStructure));
	ZeroMemory(&_sMixMirror, sizeof(_sMixMirror));

	imageInit();

	_rFloor = RectMakeCenter(1000, 580, 2000, 150);										//바닥
	//_sDoor[0] = RectMakeCenter(100, _rFloor.top - 50, 70, 100);							//앨리스 문
	_sDoor[1].size = RectMakeCenter(400, _rFloor.top - 50, 70, 100);							//3층 복도
	_sDoor[2].size = RectMakeCenter(500, _rFloor.top - 50, 70, 100);							//3측 복도
	

	

	_rSavePoint[0] = RectMakeCenter(250, 410, 50, 50);									//3층 복도

	_iMirrorNum = 0;
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		_sMirror[i].isMake = false;
	}
	for (int i = 0; i < MAX_MMIRROR_NUM; i++)
	{
		_sMixMirror[i].isMake = false;
	}
	//_sMirror[0].isMake = true;
	//ON/OFF 체크
	_bIsMirror = false;


	//fadeout
	_iFadelevel = 2;
	_iFadeTime = 255;

	//움직이는 단계
	_iMoveLevel = 0;


	_fGravity = 0;
	//_iPlace = _sMap.kind==Stage1;
	_sMap.kind = Stage1;
	_sMap.isBGreen = false;
	_sMap.isBlue = false;
	_sMap.isGreen = false;
	_sMap.isPurple = false;
	_sMap.isRed = false;
	_sMap.isYellow = false;
	//앨리스 설정
	_sAlice.weight = 200;
	_sAlice.jumpPower = 10;
	_sAlice.motion = stand;
	_sAlice.width = 100;
	_sAlice.hight = 150;
	_sAlice.size = RectMakeCenter(100, 600, _sAlice.width, _sAlice.hight);
	_sAlice.isRight = true;
	_sAlice.canPull = false;
	_sAlice.speed = 4;

	_sAliceimage.stand = IMAGEMANAGER->findImage("aliceStand");
	_sAliceimage.jumping = IMAGEMANAGER->findImage("aliceJump");
	_sAliceimage.walking = IMAGEMANAGER->findImage("aliceWalk");
	_sAliceimage.BM = IMAGEMANAGER->findImage("BM");
	_sAliceimage.RM = IMAGEMANAGER->findImage("RM");
	_sAliceimage.GM = IMAGEMANAGER->findImage("GM");
	_sAliceimage.PM = IMAGEMANAGER->findImage("PM");
	_sAliceimage.BGM = IMAGEMANAGER->findImage("BGM");

	_sAliceimage.map = IMAGEMANAGER->findImage("BackGround");

	_sAliceimage.floor = IMAGEMANAGER->findImage("floor");
	setAliceFrame(stand, 3);
	setAliceFrame(jumping, 5);
	setAliceFrame(walking, 4);
	setStage1();

	//저장되어있는지 확인
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("save\\isSave.txt");
	_bIsLoad = atoi(vStr[0].c_str());
	
	//되어있으면
	if (_bIsLoad == true)
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save\\data.txt");
		_iPlace = atoi(vStr[0].c_str());
		_sAlice.size.left = atoi(vStr[1].c_str());
		_sAlice.size.right = _sAlice.size.left + _sAlice.width;
		_sAlice.size.top = atoi(vStr[2].c_str());
		_sAlice.size.bottom = _sAlice.size.top + _sAlice.hight;

	}

	_fLoofMapX = 0;
	_fLoofMapY = 0;
	_sMap.iscamera = false;
	return S_OK;
}
void world:: release(void)
{

}
void world:: update(void)
{

	if (_fLoofMapX < 0)
	{
		moveCamera(abs(_fLoofMapX), 0);
		_fLoofMapX = 0;
	}

	if (_fLoofMapY < 0)
	{
		
		moveCamera(0, abs(_fLoofMapY));
		_fLoofMapY = 0;
	}
	frame(_sAliceimage.stand, stand, 10);
	frame(_sAliceimage.jumping, jumping, 7);
	frame(_sAliceimage.jumping, falling, 7);
	frame(_sAliceimage.walking, walking, 7);
	//_fDegree = (_rFloor.top - _sAlice.size.bottom) / 50;
	_fGravity += GRAVITY*_sAlice.weight;// *_fDegree;
	
	//if (_sAlice.size.top + _sAlice.hight / 2>WINSIZEY / 2 - 100)
	//_fLoofMapY > 0&&
	
	///if (_fLoofMapY <=0)
	//if (_fLoofMapY <= 0)
	if (_sMap.iscamera == false && _fLoofMapY > 0 || (_sAlice.size.bottom>WINSIZEY - 95))moveCamera(0, -_fGravity);
	else OffsetRect(&_sAlice.size, 0, _fGravity);
//	else if (_fLoofMapY > 0 && _fGravity>80 * GRAVITY*_sAlice.weight) 
	
	//(_fLoofMapY>0)
	
	if (_iMoveLevel == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			/*	if (_bIsMirror == false)_bIsMirror = true;
			else _bIsMirror = false;*/

			openDoor();
		//	for (int i = 0;i<)
			for (int i = 0; i < MAX_MIRROR_NUM; i++)
			{
				EnterMirror(&_sMirror[i]);
			}
			for (int i = 0; i < MAX_MMIRROR_NUM; i++)
			{
				EnterMirror(&_sMixMirror[i]);
			}
			save(_sMap.kind == Floor3);

		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sAlice.size.left>0)
		{
			if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling && _sAlice.motion != falling)_sAlice.motion = walking;
			/*if (_sAlice.motion == Lgrab)
			{
				_sAlice.motion = pulling;
			}
			else if (_sAlice.motion == Rgrab)
			{
				_sAlice.motion = pushing;
			}*/
			if (_sAlice.motion == walking)_sAlice.speed = 5;
			_sAlice.isRight = false;
			if (_sAlice.size.left+_sAlice.width / 2>WINSIZEX / 2 || _fLoofMapX <= 0)OffsetRect(&_sAlice.size, -_sAlice.speed, 0);
			else  if (_fLoofMapX>0) moveCamera(_sAlice.speed, 0);
			//_sAlice.size.left -= 4;
			//_sAlice.size.right -= 4;
			

			
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			
		//	if (_sAlice.motion == pulling)_sAlice.isRight = true;
			if (_sAlice.motion != jumping/*&&_sAlice.motion != pushing&&_sAlice.motion != pulling*/)_sAlice.motion = stand;
			/*if (_sAlice.motion == pushing)_sAlice.motion = Rgrab;
			else if (_sAlice.motion == pulling)_sAlice.motion = Lgrab;*/
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sAlice.size.right<WINSIZEX)
		{
			if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling&& _sAlice.motion != falling)_sAlice.motion = walking;
			/*if (_sAlice.motion == Lgrab)
			{
				_sAlice.motion = pushing;
			}
			if (_sAlice.motion == Rgrab)
			{
				_sAlice.motion = pulling;
			}*/
			if (_sAlice.motion == walking)_sAlice.speed = 5;
			_sAlice.isRight = true;
			if (_sAlice.size.left+_sAlice.width/2<WINSIZEX / 2)OffsetRect(&_sAlice.size, _sAlice.speed, 0);
			else  moveCamera(-_sAlice.speed, 0);
			//_sAlice.size.left += 4;
			//_sAlice.size.right += 4;
		
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			//if (_sAlice.motion == pulling)_sAlice.isRight = false;
			if (_sAlice.motion != jumping/*&&_sAlice.motion != pushing&&_sAlice.motion != pulling*/)_sAlice.motion = stand;
		/*	if (_sAlice.motion == pushing)_sAlice.motion = Lgrab;
			else if (_sAlice.motion == pulling)_sAlice.motion = Rgrab;*/
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_sAlice.motion != falling)_sAlice.motion = jumping;
			_sAlice.speed = 5;
			if (_sAlice.jumpPower<12 && _sAlice.motion != falling)_sAlice.jumpPower += 1.0f;
			
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			//if (_sAlice.jumpPower>=10)_sAlice.jumpPower -= 0.2f;
		}
	/*	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_sAlice.size.top += 4;
			_sAlice.size.bottom += 4;
		}*/
	}
	

	if (_sAlice.motion == jumping || _sAlice.motion == falling)
	{
		
		if (_sAlice.size.top + _sAlice.hight / 2 < WINSIZEY / 2)
		{
			moveCamera(0, +_sAlice.jumpPower);
			_sMap.iscamera = false;
		}
		else
		{
			_sMap.iscamera = TRUE;
			OffsetRect(&_sAlice.size, 0, -_sAlice.jumpPower);
		}
	}
	
	updateStage1();


	movePlace();

	RECT temp;
	if(IntersectRect(&temp, &_sAlice.size, &_rFloor))
	{
		_sAlice.size.bottom = _rFloor.top ;
		_sAlice.size.top = _sAlice.size.bottom - _sAlice.hight;
		_fGravity = 0;
		_sAlice.jumpPower = 5;
		if (_sAlice.motion == jumping || _sAlice.motion == falling)_sAlice.motion = stand;
	}
	if (IntersectRect(&temp, &_sDoor[0].size, &_sAlice.size))
	{

	}

	AliceInside();
	
	mixMirror();
	//pushNPull();
	//pushNPull(&_sMirror[1]);
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		pushNPull(i);
		rectCrash(&_sMirror[i].size);
	}
	//pushNPull(0);
	//pushNPull(1);
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		if (_sMirror[i].isCanPush == true)
		{
			_sAlice.canPull = true;
			break;
		}
		else _sAlice.canPull = false;
	}
	reset();
}
void world:: render(void)
{
	
	IMAGEMANAGER->loopRender("BackGround", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _fLoofMapX, 0);
	IMAGEMANAGER->render("floor", getMemDC(), _rFloor.left, _rFloor.top);
	


	//char motion[64];
	//if (_sAlice.motion == stand)sprintf_s(motion, "stand");
	//else if (_sAlice.motion == walking)sprintf_s(motion, "walking");
	//else if (_sAlice.motion == jumping)sprintf_s(motion, "jumping");
	//else if (_sAlice.motion == runing)sprintf_s(motion, "runing");
	//else if (_sAlice.motion == pulling)sprintf_s(motion, "pulling");
	//else if (_sAlice.motion == pushing)sprintf_s(motion, "pushing");
	//else if (_sAlice.motion == Lgrab)sprintf_s(motion, "Lgrab");
	//else if (_sAlice.motion == Rgrab)sprintf_s(motion, "Rgrab");
	//else if (_sAlice.motion == falling)sprintf_s(motion, "falling");

	//char jumppower[10];

	//char str[10];
	//sprintf_s(str, "%d",_iFadelevel);



	//char roomname[128];
	//
	//if (_sMap.kind==Stage1)sprintf_s(roomname, "Stage1");
	//else if (_sMap.kind==Floor3)sprintf_s(roomname, "Floor3");

	//char loofx[128];
	//sprintf_s(loofx, "%f", _fLoofMapX);
	//char loofy[128];
	//sprintf_s(loofy, "%f", _fLoofMapY);
	////else if (_iPlace == jumping)sprintf_s(motion, "jumping");
	////else if (_iPlace == runing)sprintf_s(motion, "runing");
	////else if (_sAlice.motion == walking)sprintf_s(str, "walking");

	//sprintf_s(jumppower, "%f", _sAlice.jumpPower);
	//TextOut(getMemDC(), 0, 85, "motion:", sizeof("motion:")-2);
	//TextOut(getMemDC(), 60, 85, motion, sizeof(motion) - 3);
	//TextOut(getMemDC(), 0, 100, "jumppower:", sizeof("jumppower:") - 2);
	//TextOut(getMemDC(), 80, 100, jumppower, sizeof(jumppower) - 3);
	//TextOut(getMemDC(), 0, 120, "roomname:", sizeof("roomname:") - 2);
	//TextOut(getMemDC(), 100, 120, roomname, sizeof(roomname) - 3);
	//TextOut(getMemDC(), 0, 140, "loofX:", sizeof("loofX:") - 2);
	//TextOut(getMemDC(), 100, 140, loofx, sizeof(loofx) - 3);
	//TextOut(getMemDC(), 0, 160, "loofY:", sizeof("loofY:") - 2);
	//TextOut(getMemDC(), 100, 160, loofy, sizeof(loofy) - 3);
	//TextOut(getMemDC(), 450, 100, "test:", sizeof("test:") - 2);
	//TextOut(getMemDC(), 500, 100, str, sizeof(str) - 3);

	//
	//TextOut(getMemDC(), 0, 160, "loofY:", sizeof("loofY:") - 2);
	//TextOut(getMemDC(), 100, 160, loofy, sizeof(loofy) - 3);
	//TextOut(getMemDC(), 450, 100, "test:", sizeof("test:") - 2);
	//TextOut(getMemDC(), 500, 100, str, sizeof(str) - 3);


	/*if (_bIschange == true)
	{
		for (int i = 0; i < MAX_STRUCTURE1_NUM; i++)
		{
			Rectangle(getMemDC(), _rStruc1[i].left, _rStruc1[i].top, _rStruc1[i].right, _rStruc1[i].bottom);
		}
	}
	else 
	{
		for (int i = 0; i < MAX_STRUCTURE2_NUM; i++)
		{
			Rectangle(getMemDC(), _rStruc2[i].left, _rStruc2[i].top, _rStruc2[i].right, _rStruc2[i].bottom);
		}
	}*/

	
		
	
	if (_sMap.kind==Floor3)
	{
		Rectangle(getMemDC(), _sDoor[0].size.left, _sDoor[0].size.top, _sDoor[0].size.right, _sDoor[0].size.bottom);
		Rectangle(getMemDC(), _sDoor[1].size.left, _sDoor[1].size.top, _sDoor[1].size.right, _sDoor[1].size.bottom);
		Rectangle(getMemDC(), _sDoor[2].size.left, _sDoor[2].size.top, _sDoor[2].size.right, _sDoor[2].size.bottom);
		Ellipse(getMemDC(), _rSavePoint[0].left, _rSavePoint[0].top, _rSavePoint[0].right, _rSavePoint[0].bottom);
	}



	//Rectangle(getMemDC(), _rFloor.left, _rFloor.top, _rFloor.right, _rFloor.bottom);

	

	drawStage1();
	
	if (_sAlice.canPull == true)
	{
		//Ellipse(getMemDC(), _sAlice.size.left, _sAlice.size.top, _sAlice.size.right, _sAlice.size.bottom);
			
	}
	else
	{
		//Rectangle(getMemDC(), _sAlice.size.left, _sAlice.size.top, _sAlice.size.right, _sAlice.size.bottom);
			
	}
	if (_sAlice.motion == pushing || _sAlice.motion == pulling || _sAlice.motion == Rgrab|| _sAlice.motion == Lgrab)Rectangle(getMemDC(), _sAlice.size.left, _sAlice.size.top, _sAlice.size.right, _sAlice.size.bottom);
	
	if (_sAlice.motion == stand)
	{
		if (_sAlice.isRight)IMAGEMANAGER->frameRender("aliceStand", getMemDC(), _sAlice.size.left - 20, _sAlice.size.top);
		else IMAGEMANAGER->frameRender("aliceStand", getMemDC(), _sAlice.size.left , _sAlice.size.top);
	}
	//IMAGEMANAGER->render("test", getMemDC(), _sAlice.size.left, _sAlice.size.top);
	else if (_sAlice.motion == jumping || _sAlice.motion == falling)IMAGEMANAGER->frameRender("aliceJump", getMemDC(), _sAlice.size.left, _sAlice.size.top - 30);
	else if (_sAlice.motion == walking)IMAGEMANAGER->frameRender("aliceWalk", getMemDC(), _sAlice.size.left-10, _sAlice.size.top );
	//if (_sAlice.motion == stand)_sAliceimage.stand->frameRender(getMemDC(), _sAlice.size.left, _sAlice.size.top);
	//_player[0]->alphaRender(backDC, _pr.pl.left - 10, _pr.pl.top - 10, _pr.see);
	//IMAGEMANAGER->alphaRender("black",getMemDC(),0,0,100);
	fadeinout();		
	
	for (int i = 0; i < 6; i++)
	{
		if (_sStructure[i].color == red)
		{
			TextOut(getMemDC(), _sStructure[i].size[0].left + _sStructure[i].width[0] / 2-5, _sStructure[i].size[0].top + _sStructure[i].height[0] / 2-6, "R", sizeof("R")-1);
		}
		else if (_sStructure[i].color == blue)
		{
			TextOut(getMemDC(), _sStructure[i].size[0].left + _sStructure[i].width[0] / 2 - 5, _sStructure[i].size[0].top + _sStructure[i].height[0] / 2 - 6, "B", sizeof("B") - 1);
		}
		else if (_sStructure[i].color == green)
		{
			TextOut(getMemDC(), _sStructure[i].size[0].left + _sStructure[i].width[0] / 2 - 5, _sStructure[i].size[0].top + _sStructure[i].height[0] / 2 - 6, "G", sizeof("G") - 1);
		}
		else if (_sStructure[i].color == purple)
		{
			TextOut(getMemDC(), _sStructure[i].size[0].left + _sStructure[i].width[0] / 2 - 5, _sStructure[i].size[0].top + _sStructure[i].height[0] / 2 - 6, "P", sizeof("P") - 1);
		}
		else if (_sStructure[i].color == bgreen)
		{
			TextOut(getMemDC(), _sStructure[i].size[0].left + _sStructure[i].width[0] / 2 - 10, _sStructure[i].size[0].top + _sStructure[i].height[0] / 2 - 6, "BG", sizeof("BG") - 1);
		}
	}
	//fadeinout
}



















//앨리스 방 셋팅
void world::setStage1(void)																
{

	//_sDoor[0].size = RectMakeCenter(1000, _rFloor.top - 50, 70, 100);							//앨리스 문
	//_sDoor[0].islock = false;



	/*_sStructure[0].height[0] = 100;
	_sStructure[0].width[0] = 40;
	_sStructure[0].size[0] = RectMakeCenter(600, _rFloor.top - _sStructure[0].height[0] / 2, _sStructure[0].width[0], _sStructure[0].height[0]);
	_sStructure[0].color = red;
	_sStructure[0].height[1] = 40;
	_sStructure[0].width[1] = 100;
	_sStructure[0].size[1] = RectMakeCenter(_sStructure[0].size[0].right + _sStructure[0].width[1]/2, _sStructure[0].size[0].top + _sStructure[0].height[1]/2, _sStructure[0].width[1], _sStructure[0].height[1]);*/

	setStructure(0, 40, 40, 0, 0, white, PointMake(250, _rFloor.top), leftUp, true);

	setStructure(1, 150, 30, 30, 100, red, PointMake(500, _rFloor.top-100), leftDown , true);

	setStructure(2, 30, 100, 200, 30, blue, PointMake(_sStructure[1].size[0].right-22 , _sStructure[1].size[0].top), leftUp, false);

	setStructure(3, 250, 30, 30, 260, purple, PointMake(900, _sStructure[2].size[0].top-220),leftDown, true);

	setStructure(4, 160, 30, 0, 0, white, PointMake(_sStructure[3].size[1].right+80, _sStructure[2].size[0].top+30), rightUp, false);

	setStructure(5, 30, 140, 50, 50, bgreen, PointMake(1300, _rFloor.top), rightDown, false);



	/*_sStructure[1].height[0] = 100;
	_sStructure[1].width[0] = 40;
	_sStructure[1].size[0] = RectMakeCenter(600, _rFloor.top - _sStructure[1].height[0] / 2, _sStructure[1].width[0], _sStructure[1].height[0]);
	_sStructure[1].color = purple;
	_sStructure[1].height[1] = 40;
	_sStructure[1].width[1] = 100;
	_sStructure[1].size[1] = RectMakeCenter(_sStructure[1].size[0].right + _sStructure[1].width[1] / 2, _sStructure[1].size[0].top + _sStructure[1].height[1] / 2, _sStructure[1].width[1], _sStructure[1].height[1]);*/


	//_sMirror[0].color = blue;
	//_sMirror[0].size = RectMakeCenter(800, _rFloor.top - 50, 50, 80);

	//_sMirror[1].color = red;
	//_sMirror[1].size = RectMakeCenter(500, _rFloor.top - 50, 50, 80);
	

	setMirror(true,red, 300, _rFloor.top - 50, 40, 60, turnleft);
	setMirror(true,blue, 500, _rFloor.top - 50, 50, 60, turnleft);
	setMirror(true, blue, _sStructure[4].size[0].left+100, _sStructure[4].size[0].top - 30, 50, 60, turnleft);
	setMirror(true, green, 700, _rFloor.top - 50, 60, 80, turnleft);
	//setMirror(red, 500, _rFloor.top - 50, 50, 80, turnleft);
	//_sStructure[0].width = 250;
	//_sStructure[0].height = 100;
															//침대
	//_sStructure[0].kind = bed;
	//_sStructure[0].size2 = RectMakeCenter(100, _rFloor.top - _sStructure[0].height/2, _sStructure[0].width, _sStructure[0].height);
	
	//_sStructure[0].weight = 150;

	//_sMirror[0].size = RectMakeCenter(100, _rFloor.top - 50, 40, 60);


	//_sMStructure[0].height = 100;
	//_sMStructure[0].width = 250;
	//_sMStructure[0].weight = 150;
	//_sMStructure[0].kind = bed;

	//_sMStructure[0].size2 = RectMakeCenter(WINSIZEX - 200, _rFloor.top -50 , _sMStructure[0].width, _sMStructure[0].height);

	//_sMDoor[0].islock = false;
	//_sMDoor[0].size = RectMakeCenter(WINSIZEX-1000, _rFloor.top - 100, 120, 200);
}


//앨리스방 업데이트
void world:: updateStage1(void)
{
	if (_sMap.kind==Stage1)
	{
		//rectPush(&_sStructure[0]);
		//rectCrash( &_sStructure[0].size2, &_sAlice.size);
		//rectPull(&_sStructure[0]);
		////if (_sMap.isMirror != true)
		//{
		//	pushNPull(&_sStructure[0]);
			//playerCrash(&_sStructure[0].size2);
			//doorLock(&_sDoor[0], &_sStructure[0].size2);
		//	structureGravity(&_sStructure[0]);
		//	rectCrash(&_rFloor, &_sStructure[0]);
		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				playerCrash(&_sStructure[j].size[i]);
			}
		}
		for (int i = 0; i < MAX_MIRROR_NUM; i++)
		{
			//pushNPull(_sMirror[i]);
			
			//pushNPull(&_sMirror[i].size);
		}
		

		/*for (_viMirror = _vMirror.begin(); _viMirror != _vMirror.end(); ++_viMirror)
		{
			pushNPull(&_viMirror->size);
		}*/
		//}
		//else
		//{
			//doorLock(&_sDoor[0], &_sMStructure[0].size2);
		//	structureGravity(&_sMStructure[0]);
		//	rectCrash(&_rFloor, &_sMStructure[0]);
			//pushNPull(&_sMStructure[0]);
			//playerCrash(&_sMStructure[0].size2);
		//}
		
	}
	
}


//앨리스방 그리기
void world::drawStage1(void)
{
	if (_sMap.kind==Stage1)
	{
		

		

		//if (_sMap.isMirror == false)
		//{
			
			Rectangle(getMemDC(), _sDoor[0].size.left, _sDoor[0].size.top, _sDoor[0].size.right, _sDoor[0].size.bottom);
			for (int j = 0; j < MAX_STRUCTURE_NUM; j++)
			{

				for (int i = 0; i <2 ; i++)
				{ 
					if (i == 0)
					{
						if (_sStructure[j].color == red)
						{
							//if (_sStructure[j].)
						}
						else if (_sStructure[j].color == blue)
						{
						}
						else if (_sStructure[j].color == green)
						{
						}
					}
					else if (i == 1)
					{
						if (_sStructure[j].color == red)
						{
							//if (_sStructure[j].)
						}
						else if (_sStructure[j].color == blue)
						{
						}
						else if (_sStructure[j].color == green)
						{
						}
					}
				
					Rectangle(getMemDC(), _sStructure[j].size[i].left, _sStructure[j].size[i].top, _sStructure[j].size[i].right, _sStructure[j].size[i].bottom);
					FillRect(getMemDC(), &_sStructure[j].size[i], _sStructure[j].brush);
				}
			}
			
			//Rectangle(getMemDC(), _sMirror[0].size.left, _sMirror[0].size.top, _sMirror[0].size.right, _sMirror[0].size.bottom);
			/*for (_viMirror = _vMirror.begin(); _viMirror != _vMirror.end(); ++_viMirror)
			{
				Rectangle(getMemDC(), _viMirror->size.left, _viMirror->size.top, _viMirror->size.right, _viMirror->size.bottom);
			}*/
		//}
		//else
		//{
			//Rectangle(getMemDC(), _sMDoor[0].size.left, _sMDoor[0].size.top, _sMDoor[0].size.right, _sMDoor[0].size.bottom);
			//Rectangle(getMemDC(), _sMStructure[0].size2.left, _sMStructure[0].size2.top, _sMStructure[0].size2.right, _sMStructure[0].size2.bottom);
		//}
			for (int i = 0; i < MAX_MIRROR_NUM; i++)
			{
				if (_sMirror[i].color == red)IMAGEMANAGER->render("RM", getMemDC(), _sMirror[i].size.left, _sMirror[i].size.top);
				else if (_sMirror[i].color == green)IMAGEMANAGER->render("GM", getMemDC(), _sMirror[i].size.left, _sMirror[i].size.top);
				else if (_sMirror[i].color == blue)IMAGEMANAGER->render("BM", getMemDC(), _sMirror[i].size.left, _sMirror[i].size.top);
				//if (_sMirror[i].color == red || _sMirror[i].color == green || _sMirror[i].color == blue)Rectangle(getMemDC(), _sMirror[i].size.left, _sMirror[i].size.top, _sMirror[i].size.right, _sMirror[i].size.bottom);
				
			}
		
			for (int i = 0; i < MAX_MMIRROR_NUM; i++)
			{
				
				Rectangle(getMemDC(), _sMixMirror[i].size.left, _sMixMirror[i].size.top, _sMixMirror[i].size.right, _sMixMirror[i].size.bottom);
				//if (_sMixMirror[i].color == purple)IMAGEMANAGER->render("PM", getMemDC(), _sMixMirror[i].size.left, _sMixMirror[i].size.top);
				//else if (_sMixMirror[i].color == bgreen)IMAGEMANAGER->render("BGM", getMemDC(), _sMixMirror[i].size.left, _sMixMirror[i].size.top);
			}
			//Rectangle(getMemDC(), _sMirror[2].size.left, _sMirror[2].size.top, _sMirror[2].size.right, _sMirror[2].size.bottom);
			//Rectangle(getMemDC(), _sMirror[1].size.left, _sMirror[1].size.top, _sMirror[1].size.right, _sMirror[1].size.bottom);
			//Rectangle(getMemDC(), _sMirror[0].size.left, _sMirror[0].size.top, _sMirror[0].size.right, _sMirror[0].size.bottom);
			//Rectangle(getMemDC(), _sMirror[3].size.left, _sMirror[3].size.top, _sMirror[3].size.right, _sMirror[3].size.bottom);
	}
}

void world::imageInit(void)
{
	IMAGEMANAGER->addImage("black", "image\\black.bmp", 1200, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceStand", "image\\aliceStand.bmp", 195, 194, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceJump", "image\\aliceJump.bmp", 350, 260, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceWalk", "image\\aliceWalk.bmp", 252, 196, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceWalk", "image\\aliceWalk.bmp", 252, 196, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RM", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BM", "image\\blueMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GM", "image\\greenMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GM", "image\\purpleMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BGM", "image\\BGMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BBG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BBS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BKG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BKS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GLG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GLS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GPG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GPS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RKG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RKS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RQG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RQS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackGround", "image\\BackGround.bmp", 1500, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor", "image\\floor.bmp", 1200, 100, false, RGB(255, 0, 255));
}
	




//문을연다
void world:: openDoor()
{

	RECT temp;

	if (_sMap.kind==Stage1)
	{

		/*if (IntersectRect(&temp, &_sAlice.size, &_sDoor[0].size) && _sDoor[0].islock == false )
		{
			_iMoveLevel = 1;
			_iFadelevel = 1;
			
		}
		else if (IntersectRect(&temp, &_sAlice.size, &_sMirror[0].size))
		{
			_iMoveLevel = 2;
		}*/
	}
	else if (_sMap.kind == Floor3)
	{

		if (IntersectRect(&temp, &_sAlice.size, &_sDoor[0].size) && _sDoor[0].islock == false)
		{
			_iMoveLevel = 1;
			_iFadelevel = 1;

		}
	}

}

void world::doorLock(sDoor *door,RECT *rc)
{
	if ((*door).size.left>(*rc).left &&
		(*door).size.right<(*rc).right
		)
	{
		if ((*door).islock == false)(*door).islock = true;
	}
	else
	{
		
		(*door).islock = false;
	}

	
}

//이동
void world::movePlace()
{

	if (_iMoveLevel == 2)
	{
		RECT temp;
	
		if (_sMap.kind==Stage1)
		{
			if (IntersectRect(&temp, &_sAlice.size, &_sDoor[0].size)&&_sDoor[0].islock==false)
			{
				_sMap.kind = Floor3;
			}
			//for (int i = 0; i < MAX_MIRROR_NUM; i++)
			//{
				
					/*for (int i = 0; i < MAX_MIRROR_NUM; i++)
					{
					turnStructure(_sMirror[i].color);
					}*/
				
					
					//_viMirror->size
					//EnterMirror(&_sMirror[0]);
					/*if (_sMap.isMirror == false)_sMap.isMirror = true;
					else _sMap.isMirror = false;
					_sMirror[0].size = RectMakeCenter(WINSIZEX - (_sMirror[0].size .left+ (_sMirror[0].size.right - _sMirror[0].size.left) / 2), _rFloor.top - 50, 40, 60);
					_sAlice.size = RectMakeCenter(WINSIZEX - (_sAlice.size.left + (_sAlice.size.right - _sAlice.size.left)/2), 600, _sAlice.width, _sAlice.hight);*/
				
			//}
 			//if (IntersectRect(&temp, &_sAlice.size, &_sMirror[1].size))turnStructure(_sMirror[1].color);
 			
		//	for (_viMirror = _vMirror.begin(); _viMirror != _vMirror.end(); ++_viMirror)
		//	{
				/*if (IntersectRect(&temp, &_sAlice.size, &_vMirror[0].size))
				{
					turnStructure(_vMirror[0].color);
				}*/
			//}
			
		}
		else if (_sMap.kind==Floor3)
		{

			if (IntersectRect(&temp, &_sAlice.size, &_sDoor[0].size) && _sDoor[0].islock == false)
			{
				
				_sMap.kind = Stage1;
			}

		}

		_iMoveLevel = 0;
	
	}
}


//저장
void world::save(int place)
{
	RECT temp;
	
	if (_iPlace == place)
		{
			if (IntersectRect(&temp, &_sAlice.size, &_rSavePoint[0]))
			{

				char temp[32];
				vector<string> vStr;
				vStr.push_back(itoa(_iPlace, temp, 10));
				vStr.push_back(itoa(_sAlice.size.left, temp, 10));
				vStr.push_back(itoa(_sAlice.size.top, temp, 10));
				//vStr.push_back(itoa(_rocket->getY(), temp, 10));

				TXTDATA->txtSave("save\\data.txt", vStr);
				//save();
			}
		}
		
	
}


//충돌체크1
void world::crashCheck(RECT *rc)
{
	RECT temp;
	int middle;
	middle = (*rc).top + ((*rc).bottom - (*rc).top) / 2;
	if (IntersectRect(&temp, rc, &_sAlice.size))
	{
		if ((*rc).left <= _sAlice.size.right &&
			(*rc).left + 5 > _sAlice.size.right)
		{
			_sAlice.size.right = (*rc).left - 1;
			_sAlice.size.left = _sAlice.size.right - _sAlice.width;
		}
		else if ((*rc).right >= _sAlice.size.left &&
			(*rc).right - 5 < _sAlice.size.left)
		{
			_sAlice.size.left = (*rc).right + 1;
			_sAlice.size.right = _sAlice.size.left + _sAlice.width;
		}
		else if ((*rc).top <= _sAlice.size.bottom)// &&(*rc).bottom  < alice.size.bottom)
		{
			_sAlice.size.bottom = (*rc).top ;
			_sAlice.size.top = _sAlice.size.bottom - _sAlice.hight;
			_fGravity = 0;
			_sAlice.jumpPower = 15;
			if (_sAlice.motion == jumping || _sAlice.motion == falling)_sAlice.motion = stand;
		}
	}
}

//충돌체크2 처음게 당하는거 뒤에게 주
void world::rectCrash(RECT *rc)
{

	RECT temp;
	RECT uprect;
	RECT downrect;
	RECT leftrect;
	RECT rightrect;
	//RECT 
	int middlex;
	int middley;
	int rcwidth;
	int rcheight;
	int mWidth;
	int mHeight;
	
	for (int i = 0; i < MAX_STRUCTURE_NUM; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			middlex = _sStructure[i].size[j].left + (_sStructure[i].size[j].right - _sStructure[i].size[j].left) / 2;
			middley = _sStructure[i].size[j].top + (_sStructure[i].size[j].bottom - _sStructure[i].size[j].top) / 2;
			rcwidth = _sStructure[i].size[j].right - _sStructure[i].size[j].left - 3;
			rcheight = _sStructure[i].size[j].bottom - _sStructure[i].size[j].top - 20;
			uprect = RectMakeCenter(middlex, _sStructure[i].size[j].top + 5, rcwidth, 10);
			downrect = RectMakeCenter(middlex, _sStructure[i].size[j].bottom - 5, rcwidth, 10);
			leftrect = RectMakeCenter(_sStructure[i].size[j].left + 5, middley, 10, rcheight);
			rightrect = RectMakeCenter(_sStructure[i].size[j].right - 5, middley, 10, rcheight);
			mWidth = (*rc).right - (*rc).left;
			mHeight = (*rc).bottom - (*rc).top;
			if (IntersectRect(&temp, rc, &(*rc)))
			{
				/*if (_sStructure[i].size[j].left <= (*rc).right &&
				_sStructure[i].size[j].left + 10 > (*rc).right)*/
				if (IntersectRect(&temp, &(*rc), &leftrect))
				{
					(*rc).right = _sStructure[i].size[j].left;
					(*rc).left = (*rc).right - mWidth;
				}
				if (IntersectRect(&temp, &(*rc), &rightrect))
				{
					(*rc).left = _sStructure[i].size[j].right;
					(*rc).right = (*rc).left + mWidth;
				}

				if (IntersectRect(&temp, &uprect, &(*rc)))
				{
					/*	*/
					if (uprect.top <= (*rc).bottom&&
						uprect.bottom >= (*rc).bottom)// &&_sStructure[i].size[j].bottom  < (*rc)lice.size.bottom)
					{
						(*rc).bottom = uprect.top;
						(*rc).top = (*rc).bottom - mHeight;
						//	_fGr(*rc)vity = 0;
						//	_s(*rc)lice.jumpPower = 5;
						//	_sM(*rc)p.isc(*rc)mer(*rc) = true;
						//	if (_s(*rc)lice.motion == jumping || _s(*rc)lice.motion == f(*rc)lling)_s(*rc)lice.motion = st(*rc)nd;
					}
				
				}
			
				if (IntersectRect(&temp, &downrect, &(*rc)))
				{
					if (downrect.bottom >= (*rc).top&&
						downrect.top <= (*rc).top)// &&_sStructure[i].size[j].bottom  < (*rc)lice.size.bottom)
					{
						(*rc).top = downrect.bottom;
						(*rc).bottom = (*rc).top + mHeight;
						//	_s(*rc)lice.jumpPower = _s(*rc)lice.jumpPower - 5;
						//	if (_s(*rc)lice.motion == jumping)_s(*rc)lice.motion = f(*rc)lling;
					}
				}
			}
		}
	}

	//RECT temp;
	//int rcwidth;
	//int rcheight;
	//rcwidth = ((*struc).size2.right - (*struc).size2.left);
	//rcheight = ((*struc).size2.bottom - (*struc).size2.top);
	//if (IntersectRect(&temp, rc, &(*struc).size2))
	//{
	//	if ((*rc).left <= (*struc).size2.right &&
	//		(*rc).left + 5 > (*struc).size2.right)
	//	{
	//		(*struc).size2.right = (*rc).left-2 ;
	//		(*struc).size2.left = (*struc).size2.right - rcwidth;
	//	}
	//	else if ((*rc).right >= (*struc).size2.left &&
	//		(*rc).right - 5 < (*struc).size2.left)
	//	{
	//		(*struc).size2.left = (*rc).right +2;
	//		(*struc).size2.right = (*struc).size2.left + rcwidth;
	//	}
	//	else if ((*rc).top <= (*struc).size2.bottom)// &&(*rc).bottom  < alice.size.bottom)
	//	{
	//		(*struc).size2.bottom = (*rc).top ;
	//		(*struc).size2.top = (*struc).size2.bottom - rcheight;

	//		(*struc).gravity = 0;
	//		/*if ((*struc).size2 == _sAlice)
	//		{
	//			_fGravity = 0;
	//			_sAlice.jumpPower = 5;
	//			if (_sAlice.motion == jumping)_sAlice.motion = stand;
	//		}*/
	//		
	//	}
	//}
	//
}

//충돌체크3
void world:: playerCrash( RECT *rc)
{
	RECT temp;
	RECT uprect;
	RECT downrect;
	RECT leftrect;
	RECT rightrect;
	//RECT 
	int middlex;
	int middley;

	int rcwidth;
	int rcheight;
	middlex = (*rc).left + ((*rc).right - (*rc).left) / 2;
	middley = (*rc).top + ((*rc).bottom - (*rc).top) / 2;
	rcwidth = (*rc).right - (*rc).left-3;
	rcheight = (*rc).bottom - (*rc).top - 20;
	uprect = RectMakeCenter(middlex, (*rc).top + 5, rcwidth, 10);
	downrect = RectMakeCenter(middlex, (*rc).bottom - 5, rcwidth, 10);
	leftrect = RectMakeCenter((*rc).left + 5, middley, 10, rcheight);
	rightrect = RectMakeCenter((*rc).right - 5, middley, 10, rcheight);
	if (IntersectRect(&temp, rc, &_sAlice.size))
	{
		/*if ((*rc).left <= _sAlice.size.right &&
			(*rc).left + 10 > _sAlice.size.right)*/
		if (IntersectRect(&temp,&_sAlice.size,&leftrect))
		{
			_sAlice.size.right = (*rc).left - 1;
			_sAlice.size.left = _sAlice.size.right - _sAlice.width;
		}
		if (IntersectRect(&temp, &_sAlice.size, &rightrect))
		{
			_sAlice.size.left = (*rc).right + 1;
			_sAlice.size.right = _sAlice.size.left + _sAlice.width;
		}

		if (IntersectRect(&temp, &uprect, &_sAlice.size))
		{
			if (uprect.top <= _sAlice.size.bottom&&
				uprect.bottom >= _sAlice.size.bottom)// &&(*rc).bottom  < alice.size.bottom)
			{
				_sAlice.size.bottom = uprect.top;
				_sAlice.size.top = _sAlice.size.bottom - _sAlice.hight;
				_fGravity = 0;
				_sAlice.jumpPower = 5;
				_sMap.iscamera = true;
				if (_sAlice.motion == jumping || _sAlice.motion == falling)_sAlice.motion = stand;
			}
			else
			{
				_sMap.iscamera = false;
			}
		}
		else
		{
			_sMap.iscamera = false;
		}

		if (IntersectRect(&temp, &downrect, &_sAlice.size))
		{
			if (downrect.bottom >= _sAlice.size.top&&
				downrect.top <= _sAlice.size.top)// &&(*rc).bottom  < alice.size.bottom)
			{
				_sAlice.size.top = downrect.bottom;
				_sAlice.size.bottom = _sAlice.size.top + _sAlice.hight;
				_sAlice.jumpPower = _sAlice.jumpPower - 5;
				if (_sAlice.motion == jumping)_sAlice.motion = falling;
			}
		}
	}
	
}




void world::pushNPull(int num)
{
	RECT temp;
	RECT leftrect;
	RECT rightrect;
	RECT leftalice;
	RECT rightalice;
	int middleAlice;
	int middley;
	int width;
	int height;
	middleAlice = _sAlice.size.top + (_sAlice.size.bottom - _sAlice.size.top) / 2;
	middley = _sMirror[num].size.top + (_sMirror[num].size.bottom - _sMirror[num].size.top) / 2;
	width = _sMirror[num].size.right - _sMirror[num].size.left;
	height = _sMirror[num].size.bottom - _sMirror[num].size.top;

	leftrect = RectMakeCenter(_sMirror[num].size.left-2, middley,15, 100);
	rightrect = RectMakeCenter(_sMirror[num].size.right-2, middley,15, 100);
	leftalice = RectMakeCenter(_sAlice.size.left, middleAlice, 15, _sAlice.hight);
	rightalice = RectMakeCenter(_sAlice.size.right, middleAlice, 15, _sAlice.hight);


	Rectangle(getMemDC(), rightalice.left, rightalice.top, rightalice.right, rightalice.bottom);
	if (IntersectRect(&temp, &rightalice, &leftrect))
	{
		//_sAlice.canPull = true;
		if (_sAlice.isRight)_sMirror[num].isCanPush = true;
		if (KEYMANAGER->isStayKeyDown('E'))
		{
			if (_sAlice.motion != pulling&&_sAlice.motion != pushing&&_sAlice.motion != jumping&&_sAlice.motion !=Rgrab)_sAlice.motion = Lgrab;
			_sAlice.speed = 2;
			//_sAlice.canPull = false;
			_sMirror[num].isCanPush = false;
			_sMirror[num].size.left = _sAlice.size.right;
			_sMirror[num].size.right = _sMirror[num].size.left + width;
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (_sAlice.motion != jumping)	_sAlice.motion = pulling;
				_sMirror[num].size.left = _sAlice.size.right;
				_sMirror[num].size.right = _sMirror[num].size.left + width;
				//(*sMirror).size.right = _sAlice.size.left;
				//(*sMirror).size.left = (*sMirror).size.right - rcwidth;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_sAlice.motion != jumping)_sAlice.motion = pushing;
			}
		}
		if (KEYMANAGER->isOnceKeyUp('E'))
		{
			_sAlice.motion = stand;
			_sAlice.speed = 5;
			_sAlice.isRight = true;
		}

	}
	else if (IntersectRect(&temp, &leftalice, &rightrect))
	{
		bool istrue;
		//if (_sAlice.motion == pulling&&_sAlice.isRight == true)istrue = true;
		///else if (_sAlice.motion == pushing&&_sAlice.isRight == false)istrue = true;
		//else istrue = false;
		//if (istrue)
		//{
			//_sAlice.canPull = true;
			if (!_sAlice.isRight)	_sMirror[num].isCanPush = true;
			if (KEYMANAGER->isStayKeyDown('E'))
			{
				if (_sAlice.motion != pulling&&_sAlice.motion != pushing&&_sAlice.motion != jumping)_sAlice.motion = Rgrab;
				_sAlice.speed = 2;
				_sMirror[num].isCanPush = false;
				//_sAlice.canPull = false;
				_sMirror[num].size.right = _sAlice.size.left;
				_sMirror[num].size.left = _sMirror[num].size.right - width;
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					if (_sAlice.motion != jumping)_sAlice.motion = pushing;
				}
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					if (_sAlice.motion != jumping)_sAlice.motion = pulling;
					_sMirror[num].size.right = _sAlice.size.left;
					_sMirror[num].size.left = _sMirror[num].size.right - width;
				}
			}
			if (KEYMANAGER->isOnceKeyUp('E'))
			{
				if (_sAlice.motion != jumping)_sAlice.motion = stand;
				_sAlice.speed = 5;
				_sAlice.isRight = false;
			}
		}
		else if (!IntersectRect(&temp, &rightalice, &rightrect) && !IntersectRect(&temp, &leftalice, &leftrect))
		{
			_sMirror[num].isCanPush = false;
			//_sAlice.canPull = false;
		}
	//}
		

	//RECT temp;
	//
	//int middley;
	//
	//int rcwidth;
	//rcwidth = _sMirror[num].size.right - _sMirror[num].size.left;
	//leftRect = RectMakeCenter(_sMirror[num].size.left, middley, 10, _sMirror[num].size.bottom - _sMirror[num].size.top);
	///*if (_sMirror[num].size.left + 10 >= _sAlice.size.right &&
	//	_sMirror[num].size.left - 5 <= _sAlice.size.right&&
	//	_sAlice.isRight == true)*/
	//if (IntersectRect(&temp,&_sAlice.size,&leftRect))
	//{
	//	if (_sAlice.motion != jumping)_sAlice.canPull = true;

	//	if (KEYMANAGER->isOnceKeyDown('E') && _sAlice.motion != jumping)
	//	{

	//		if (_sAlice.motion != Lgrab&& _sAlice.motion != pushing && _sAlice.motion != pulling)_sAlice.motion = Lgrab;
	//		else if (_sAlice.motion == Lgrab || _sAlice.motion == pushing || _sAlice.motion == pulling) _sAlice.motion = stand;
	//		_sAlice.canPull = false;
	//		_sAlice.speed = 2;

	//		_sMirror[num].size.left = _sAlice.size.right;
	//		_sMirror[num].size.right = _sMirror[num].size.left + rcwidth;
	//	}

	//}
	//else if (_sMirror[num].size.right - 10 <= _sAlice.size.left &&
	//	_sMirror[num].size.right + 5 >= _sAlice.size.left&&
	//	_sAlice.isRight == false)
	//{
	//	if (_sAlice.motion != jumping)_sAlice.canPull = true;

	//	if (KEYMANAGER->isOnceKeyDown('E') && _sAlice.motion != jumping)
	//	{

	//		if (_sAlice.motion != Rgrab&& _sAlice.motion != pushing && _sAlice.motion != pulling)_sAlice.motion = Rgrab;
	//		else  if (_sAlice.motion == Lgrab || _sAlice.motion == pushing || _sAlice.motion == pulling) _sAlice.motion = stand;
	//		_sAlice.canPull = false;
	//		_sAlice.speed = 2;

	//		_sMirror[num].size.right = _sAlice.size.left;
	//		_sMirror[num].size.left = _sMirror[num].size.right - rcwidth;
	//	}
	//}
	//else _sAlice.canPull = false;

	//if (_sAlice.motion == Lgrab || _sAlice.motion == Rgrab || _sAlice.motion == pushing || _sAlice.motion == pulling)_sAlice.canPull = false;


	//if (_sAlice.isRight)
	//{
	//	if (_sAlice.motion == pushing)
	//	{
	//		_sMirror[num].size.left = _sAlice.size.right;
	//		_sMirror[num].size.right = _sMirror[num].size.left + rcwidth;
	//	}
	//	else if (_sAlice.motion == pulling)
	//	{
	//		_sMirror[num].size.right = _sAlice.size.left;
	//		_sMirror[num].size.left = _sMirror[num].size.right - rcwidth;

	//	}
	//}
	//else
	//{
	//	if (_sAlice.motion == pulling)
	//	{
	//		_sMirror[num].size.left = _sAlice.size.right;
	//		_sMirror[num].size.right = _sMirror[num].size.left + rcwidth;
	//	}
	//	else if (_sAlice.motion == pushing)
	//	{
	//		_sMirror[num].size.right = _sAlice.size.left;
	//		_sMirror[num].size.left = _sMirror[num].size.right - rcwidth;

	//	}
	//}


}

//void world::pushNPull(sStructure *sFurniture)
//{
//	int rcwidth;
//	rcwidth = (*sMirror).size.right - (*sMirror).size.left;
//	if ((*sMirror).size.left+100 >= _sAlice.size.right &&
//		(*sMirror).size.left - 100 <= _sAlice.size.right&&
//		_sAlice.isRight==true)
//	{
//		if (_sAlice.motion != jumping)_sAlice.canPull = true;
//	
//			if (KEYMANAGER->isStayKeyDown('E') && _sAlice.motion != jumping)
//			{
//
//				if (_sAlice.motion != Lgrab&& _sAlice.motion != pushing && _sAlice.motion != pulling)_sAlice.motion = Lgrab;
//				//else if (_sAlice.motion == Lgrab|| _sAlice.motion == pushing || _sAlice.motion == pulling) _sAlice.motion = stand;
//				_sAlice.canPull = false;
//				_sAlice.speed = 2;
//				if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sAlice.size.left > 0)
//				{
//					//if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling)_sAlice.motion = walking;
//
//					_sAlice.motion = pulling;
//
//					(*sMirror).size.left = _sAlice.size.right;
//					(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//					/*	if (_sAlice.motion == walking)_sAlice.speed = 4;
//						_sAlice.isRight = false;
//						OffsetRect(&_sAlice.size, -_sAlice.speed, 0);*/
//					//_sAlice.size.left -= 4;
//					//_sAlice.size.right -= 4;
//
//
//
//				}
//				if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sAlice.size.right < WINSIZEX)
//				{
//					//if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling)_sAlice.motion = walking;
//					if (_sAlice.motion == Lgrab)
//					{
//						_sAlice.motion = pushing;
//					}
//
//					//if (_sAlice.motion == walking)_sAlice.speed = 4;
//					//_sAlice.isRight = true;
//					//OffsetRect(&_sAlice.size, _sAlice.speed, 0);
//					//_sAlice.size.left += 4;
//					//_sAlice.size.right += 4;
//
//				}
//				if (_sAlice.isRight)
//				{
//					if (_sAlice.motion == pulling)
//					{
//						(*sMirror).size.right = _sAlice.size.left;
//						(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//
//					}
//				}
//				else
//				{
//					if (_sAlice.motion == pulling)
//					{
//						(*sMirror).size.left = _sAlice.size.right;
//						(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//					}
//					
//				}
//			}
//		
//		
//	}
//	else if ((*sMirror).size.right-100 <= _sAlice.size.left &&
//		(*sMirror).size.right + 100 >= _sAlice.size.left&&
//		_sAlice.isRight == false)
//	{
//		if (_sAlice.motion != jumping)_sAlice.canPull = true;
//	
//			if (KEYMANAGER->isStayKeyDown('E') && _sAlice.motion != jumping)
//			{
//
//				if (_sAlice.motion != Rgrab&& _sAlice.motion != pushing && _sAlice.motion != pulling)_sAlice.motion = Rgrab;
//				//else  if (_sAlice.motion == Lgrab || _sAlice.motion == pushing || _sAlice.motion == pulling) _sAlice.motion = stand;
//				_sAlice.canPull = false;
//				_sAlice.speed = 2;
//				//_sAlice.motion = pulling;
//				if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sAlice.size.right < WINSIZEX)
//				{
//					//if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling)_sAlice.motion = walking;
//
//					_sAlice.motion = pulling;
//					(*sMirror).size.right = _sAlice.size.left + 10;
//					(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//					//if (_sAlice.motion == walking)_sAlice.speed = 4;
//					//_sAlice.isRight = true;
//					//OffsetRect(&_sAlice.size, _sAlice.speed, 0);
//					//_sAlice.size.left += 4;
//					//_sAlice.size.right += 4;
//
//				}
//				if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sAlice.size.left > 0)
//				{
//					//if (_sAlice.motion != jumping&&_sAlice.motion != Lgrab&&_sAlice.motion != Rgrab&&_sAlice.motion != pushing&&_sAlice.motion != pulling)_sAlice.motion = walking;
//
//					_sAlice.motion = pushing;
//
//
//					/*	if (_sAlice.motion == walking)_sAlice.speed = 4;
//					_sAlice.isRight = false;
//					OffsetRect(&_sAlice.size, -_sAlice.speed, 0);*/
//					//_sAlice.size.left -= 4;
//					//_sAlice.size.right -= 4;
//
//
//
//				}
//
//
//
//				if (_sAlice.isRight)
//				{
//					if (_sAlice.motion == pulling)
//					{
//						(*sMirror).size.right = _sAlice.size.left;
//						(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//
//					}
//
//					
//				}
//				else
//				{
//					if (_sAlice.motion == pulling)
//					{
//						(*sMirror).size.left = _sAlice.size.right;
//						(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//					}
//					
//				}
//			}
//		
//	}
//	else
//	{
//		_sAlice.canPull = false;
//		if (_sAlice.motion == Lgrab || _sAlice.motion == pushing || _sAlice.motion == pulling || _sAlice.motion == Rgrab) _sAlice.motion = stand;
//	}
//
//	//if (_sAlice.motion == Lgrab || _sAlice.motion == Rgrab || _sAlice.motion == pushing || _sAlice.motion == pulling)_sAlice.canPull = false;
//	
//
//	/*if (_sAlice.isRight)
//	{
//		if (_sAlice.motion == pushing)
//		{
//			(*sMirror).size.left = _sAlice.size.right;
//			(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//		}
//		else if (_sAlice.motion == pulling)
//		{
//			(*sMirror).size.right = _sAlice.size.left;
//			(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//
//		}
//	}
//	else
//	{
//		if (_sAlice.motion == pulling)
//		{
//			(*sMirror).size.left = _sAlice.size.right;
//			(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//		}
//		else if (_sAlice.motion == pushing)
//		{
//			(*sMirror).size.right = _sAlice.size.left;
//			(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//
//		}
//	}
//	*/
//	if (KEYMANAGER->isOnceKeyUp('E'))
//	{
//		if (_sAlice.motion == Lgrab || _sAlice.motion == pushing || _sAlice.motion == pulling || _sAlice.motion == Rgrab) _sAlice.motion = stand;
//	}
//}



void world:: fadeinout()
{
	if (_iFadelevel == 1)
	{
		if (_iFadeTime<255)
		{
			_iFadeTime+=5;
		}
		else if (_iFadeTime >= 255)_iFadelevel = 2;
		IMAGEMANAGER->alphaRender("black", getMemDC(), _iFadeTime);
	}
	else if (_iFadelevel==2)
	{
		if (_iFadeTime>0)_iFadeTime-=5;
		else if (_iFadeTime <=0)_iFadelevel =  0;
		//if()movePlace();
		if (_iMoveLevel==1)_iMoveLevel = 2;
		IMAGEMANAGER->alphaRender("black", getMemDC(), _iFadeTime);
		

	}
	//
};


void world::frame(image *image, int motion, int maxcount)
{
	if (_sAlice.motion == motion)
	{
		
		if (_sAlice.isRight == false)
		{
			image->setFrameY(0);
			_sAliceFrame[motion].time++;
			if (_sAliceFrame[motion].time%maxcount == 0)
			{
				/*_kImage.walk->setFrameX(_kImage.walk->getFrameX() + 1);
				_currentFrameX++;
				if (_currentFrameX > _kImage.walk->getFrameX()) _currentFrameX = 0;*/
				_sAliceFrame[motion].index++;

				if (_sAliceFrame[motion].index >image->getMaxFrameX())
				{
					_sAliceFrame[motion].index = 0;
				}
				image->setFrameX(_sAliceFrame[motion].index);
			}
		}
		else
		{
			image->setFrameY(1);
			_sAliceFrame[motion].time++;
			if (_sAliceFrame[motion].time%maxcount == 0)
			{
				/*_kImage.walk->setFrameX(_kImage.walk->getFrameX() + 1);
				_currentFrameX++;
				if (_currentFrameX > _kImage.walk->getFrameX()) _currentFrameX = 0;*/
				_sAliceFrame[motion].index--;

				if (_sAliceFrame[motion].index < 0)
				{
					_sAliceFrame[motion].index = image->getMaxFrameX();
				}
				image->setFrameX(_sAliceFrame[motion].index);
			}
		}


	}
	else
	{
		if (_sAlice.isRight)
		{
			if (_sAlice.motion != falling)_sAliceFrame[motion].index = 0;
		}
		else
		{

			if (_sAlice.motion != falling)_sAliceFrame[motion].index = image->getMaxFrameX();
		}
		_sAliceFrame[motion].time = 0;
	}
}


void world:: setAliceFrame(int motion,int index)
{
	_sAliceFrame[motion].index = index;
}


void world::structureGravity(sMirror *furniture)
{
//	(*furniture).gravity += (*furniture).weight*GRAVITY;
	//OffsetRect(&(*furniture).size2, 0, (*furniture).gravity);
}


void world::AliceInside()
{

		_sAlice.width = 50;
		_sAlice.hight = 100;
	
	_sAlice.size.right = _sAlice.size.left + _sAlice.width;
	_sAlice.size.bottom = _sAlice.size.top + _sAlice.hight;
}
void world:: EnterMirror(sMirror  *mirror)
{
	RECT temp;
	if (IntersectRect(&temp, &(*mirror).size, &_sAlice.size))
	{
		if ((*mirror).color == red)
		{
			if (_sMap.isRed !=true )_sMap.isRed = true;
			else _sMap.isRed = false;
		}
		else if ((*mirror).color == blue)
		{
			if (_sMap.isBlue != true)_sMap.isBlue = true;
			else _sMap.isBlue = false;
		}
		else if ((*mirror).color == green)
		{
			if (_sMap.isGreen != true)_sMap.isGreen = true;
			else _sMap.isGreen = false;
		}
		else if ((*mirror).color == purple)
		{
			if (_sMap.isPurple != true)_sMap.isPurple = true;
			else _sMap.isPurple = false;
		}
		else if ((*mirror).color == yellow)
		{
			if (_sMap.isYellow != true)_sMap.isYellow = true;
			else _sMap.isYellow = false;
		}
		else if ((*mirror).color == bgreen)
		{
			if (_sMap.isBGreen != true)_sMap.isBGreen = true;
			else _sMap.isBGreen = false;
		}
	/*	else if ((*mirror).color == blue)
		{
			if (_sMap.isBlue != true)_sMap.isBlue = true;
			else _sMap.isBlue = false;
		}*/
		int mColor;
		mColor = (*mirror).color;
		bool mix;
		mix = (*mirror).mixLv;
		turnStructure(mColor, mix);
	}
}

void world::turnStructure(int color,bool mix)
{
	if (mix != true)
	{
		for (int i = 0; i < MAX_STRUCTURE_NUM; i++)
		{
			if (color == red)
			{
 				if (_sStructure[i].color == red)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}


				}
			}

			if (color == blue)
			{
				if (_sStructure[i].color == blue)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
			if (color == green)
			{
				if (_sStructure[i].color == green)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
			if (color == purple)
			{
				if (_sStructure[i].color == purple)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
			if (color == yellow)
			{
				if (_sStructure[i].color == yellow)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
			if (color == bgreen)
			{
				if (_sStructure[i].color == bgreen)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
			if (color == black)
			{
				if (_sStructure[i].color == black)
				{
					if (_sStructure[i].size[0].left == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].right;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].left;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].left == _sStructure[i].size[1].left)
					{
						_sStructure[i].size[1].right = _sStructure[i].size[0].right;
						_sStructure[i].size[1].left = _sStructure[i].size[1].right - _sStructure[i].width[1];
					}
					else if (_sStructure[i].size[0].right == _sStructure[i].size[1].right)
					{
						_sStructure[i].size[1].left = _sStructure[i].size[0].left;
						_sStructure[i].size[1].right = _sStructure[i].size[1].left + _sStructure[i].width[1];
					}
				}
			}
		}
	}
	
	
	
}

void world::setStructure(int num, int width1, int height1, int width2, int height2, int color, POINT pt1, int shape, bool isinside)
{

	_sStructure[num].height[0] = height1;
	_sStructure[num].width[0] = width1;
	_sStructure[num].size[0] = RectMakeCenter(pt1.x, pt1.y- _sStructure[num].height[0] / 2, _sStructure[num].width[0], _sStructure[num].height[0]);
	_sStructure[num].color = color;

	_sStructure[num].height[1] = height2;
	_sStructure[num].width[1] = width2;
	if (color == red)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(220, 0, 0));
	}
	else if (color == blue)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(0, 0, 220));
	}
	else if (color == purple)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(220, 0, 220));
	}
	else if (color == green)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(0, 220, 0));
	}
	else if (color == bgreen)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(0, 220, 220));
	}
	else if (color == white)
	{
		_sStructure[num].brush = CreateSolidBrush(RGB(125, 125, 120));
	}
	if (isinside == false)
	{
		if (shape == rightUp)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].right + _sStructure[num].width[1] / 2, _sStructure[num].size[0].top + _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == rightDown)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].right + _sStructure[num].width[1] / 2, _sStructure[num].size[0].bottom - _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == leftUp)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].left - _sStructure[num].width[1] / 2, _sStructure[num].size[0].top + _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == leftDown)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].left - _sStructure[num].width[1] / 2, _sStructure[num].size[0].bottom - _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
	}
	else
	{
		if (shape == leftUp)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].left + _sStructure[num].width[1] / 2, _sStructure[num].size[0].top - _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == leftDown)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].left + _sStructure[num].width[1] / 2, _sStructure[num].size[0].bottom + _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == rightUp)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].right - _sStructure[num].width[1] / 2, _sStructure[num].size[0].top - _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
		else if (shape == rightDown)
		{
			_sStructure[num].size[1] = RectMakeCenter(_sStructure[num].size[0].right - _sStructure[num].width[1] / 2, _sStructure[num].size[0].bottom + _sStructure[num].height[1] / 2, _sStructure[num].width[1], _sStructure[num].height[1]);
		}
	}
	
}



void world::moveCamera(int speedX, int speedY)
{
	for (int i = 0; i < MAX_STRUCTURE_NUM; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			OffsetRect(&_sStructure[i].size[j], speedX, speedY);
		}
	}
	/*for (_viMirror = _vMirror.begin(); _viMirror != _vMirror.end(); ++_viMirror)
	{
		OffsetRect(&_viMirror->size, speedX, speedY);
	}*/
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		OffsetRect(&_sMirror[i].size, speedX, speedY);
	}
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		OffsetRect(&_sMixMirror[i].size, speedX, speedY);
	}
	for (int i = 0; i < MAX_DOOR_NUM; i++)
	{
		OffsetRect(&_sDoor[i].size, speedX, speedY);
	}
	_fLoofMapX -= speedX;
	_fLoofMapY += speedY;
	if (speedY != 0)OffsetRect(&_rFloor, speedX, speedY);
}



void world::mixMirror()
{
	RECT temp;
	int rcwidth;
	int height;
	int color;
	int type;
	for (int i = 0; i < MAX_MIRROR_NUM; i++)
	{
		for (int j = 0; j < MAX_MIRROR_NUM; j++)
		{
			if (i != j)
			{
				if (IntersectRect(&temp, &_sMirror[i].size, &_sMirror[j].size))
				{
					if (_sMirror[i].size.left < _sMirror[j].size.left||_sMirror[i].mixLv ==0)//i가왼쪽에 있을경우
				
					{
						rcwidth = _sMirror[i].size.right - _sMirror[j].size.left;
						if (_sMirror[i].size.top <= _sMirror[j].size.top)height = _sMirror[j].size.bottom - _sMirror[j].size.top;
						else if (_sMirror[i].size.top > _sMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;


					}
					else if (_sMirror[i].size.left >= _sMirror[j].size.left&&_sMirror[i].mixLv)
					{
						rcwidth = _sMirror[j].size.right - _sMirror[i].size.left;
						if (_sMirror[i].size.top <= _sMirror[j].size.top)height = _sMirror[j].size.bottom - _sMirror[j].size.top;
						else if (_sMirror[i].size.top > _sMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;
					}
					if (_sMirror[i].mixLv == 0 && _sMirror[j].mixLv == 0)
					{

						if (_sMirror[i].color == red && _sMirror[j].color == blue || _sMirror[i].color == blue && _sMirror[j].color == red)color = purple;
						else if (_sMirror[i].color == red && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == red)color = yellow;
						else if (_sMirror[i].color == blue && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == blue)color = bgreen;
						else if (_sMirror[i].color == purple && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == purple)color = white;
						else if (_sMirror[i].color == bgreen && _sMirror[j].color == red || _sMirror[i].color == red && _sMirror[j].color == bgreen)color = white;
						else if (_sMirror[i].color == yellow && _sMirror[j].color == blue || _sMirror[i].color == blue && _sMirror[j].color == yellow)color = white;
						else color = black;
						if (_sMirror[i].type == turnleft&&_sMirror[j].type == turnleft)type = turnleft;
						else if (_sMirror[i].type == turnup&&_sMirror[j].type == turnup)type = turnup;
						else type = both;
						if (_sMirror[i].size.left < _sMirror[j].size.left&&_sMirror[i].mixLv == 0)//i가왼쪽에 있을경우
						{
							setMirror(false, color, _sMirror[j].size.left + rcwidth / 2, _sMirror[j].size.top + height / 2, 20, height, type);
						}
						else if (_sMirror[i].size.left >= _sMirror[j].size.left&&_sMirror[i].mixLv)
						{
							setMirror(false, color, _sMirror[i].size.left + rcwidth / 2, _sMirror[i].size.top + height / 2, 20, height, type);
						}
						_sMirror[i].mixLv = 1;
						_sMirror[j].mixLv = 1;

					}
					for (int k = 0; k < MAX_MMIRROR_NUM; k++)
					{

						if ((IntersectRect(&temp, &_sMixMirror[k].size, &_sMirror[j].size)) && (IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[k].size)))
						{

							if (_sMirror[i].size.left <= _sMirror[j].size.left&&_sMirror[i].size.right <= _sMirror[j].size.right)
							{
								_sMixMirror[k].size.left = _sMirror[j].size.left;
								_sMixMirror[k].size.right = _sMixMirror[k].size.left + _sMirror[i].size.right - _sMirror[j].size.left;
							}
							else if (_sMirror[i].size.left >= _sMirror[j].size.left&&_sMirror[i].size.right >= _sMirror[j].size.right)
							{
								_sMixMirror[k].size.left = _sMirror[i].size.left;
								_sMixMirror[k].size.right = _sMixMirror[k].size.left + _sMirror[j].size.right - _sMirror[i].size.left;
							}
						}
					}
					
				}
				else if (!IntersectRect(&temp, &_sMirror[i].size, &_sMirror[j].size))
				{
					if (_sMirror[i].mixLv == 1 && _sMirror[j].mixLv == 1)
					{
						_sMirror[i].mixLv = 0;
						_sMirror[j].mixLv = 0;
						for (int k = 0; k < MAX_MMIRROR_NUM; k++)
						{
							if (!(IntersectRect(&temp, &_sMixMirror[k].size, &_sMirror[j].size)) || !(IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[k].size)))
							{
								eraseMirror(true, k);
							}
						}
					}
					
				}
			
				
			}
		
			

			
		}

	}


	//for (int i = 0; i < MAX_MIRROR_NUM; i++)
	//{
	//	for (int j = 0; j < MAX_MMIRROR_NUM; j++)
	//	{
	//		if (i != j)
	//		{

	//			if (IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[j].size))
	//			{
	//				if (_sMirror[i].mixLv == 0)
	//				{
	//					if (_sMirror[i].size.left < _sMixMirror[j].size.left&&_sMirror[i].mixLv == 0)//i가왼쪽에 있을경우
	//					{
	//						rcwidth = _sMirror[i].size.right - _sMixMirror[j].size.left;
	//						if (_sMirror[i].size.top <= _sMixMirror[j].size.top)height = _sMixMirror[j].size.bottom - _sMixMirror[j].size.top;
	//						else if (_sMirror[i].size.top > _sMixMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;


	//					}
	//					else if (_sMirror[i].size.left >= _sMixMirror[j].size.left&&_sMirror[i].mixLv)
	//					{
	//						rcwidth = _sMixMirror[j].size.right - _sMirror[i].size.left;
	//						if (_sMirror[i].size.top <= _sMixMirror[j].size.top)height = _sMixMirror[j].size.bottom - _sMixMirror[j].size.top;
	//						else if (_sMirror[i].size.top > _sMixMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;
	//					}
	//					if (_sMirror[i].mixLv == 0 && _sMixMirror[j].mixLv == 0)
	//					{

	//						if (_sMirror[i].color == red && _sMixMirror[j].color == blue || _sMirror[i].color == blue && _sMixMirror[j].color == red)color = purple;
	//						else if (_sMirror[i].color == red && _sMixMirror[j].color == green || _sMirror[i].color == green && _sMixMirror[j].color == red)color = yellow;
	//						else if (_sMirror[i].color == blue && _sMixMirror[j].color == green || _sMirror[i].color == green && _sMixMirror[j].color == blue)color = bgreen;
	//						else if (_sMirror[i].color == purple && _sMixMirror[j].color == green || _sMirror[i].color == green && _sMixMirror[j].color == purple)color = white;
	//						else if (_sMirror[i].color == bgreen && _sMixMirror[j].color == red || _sMirror[i].color == red && _sMixMirror[j].color == bgreen)color = white;
	//						else if (_sMirror[i].color == yellow && _sMixMirror[j].color == blue || _sMirror[i].color == blue && _sMixMirror[j].color == yellow)color = white;
	//						else color = black;
	//						if (_sMirror[i].type == turnleft&&_sMixMirror[j].type == turnleft)type = turnleft;
	//						else if (_sMirror[i].type == turnup&&_sMixMirror[j].type == turnup)type = turnup;
	//						else type = both;
	//						if (_sMirror[i].size.left < _sMixMirror[j].size.left&&_sMirror[i].mixLv == 0)//i가왼쪽에 있을경우
	//						{
	//							setMirror(false, color, _sMixMirror[j].size.left + rcwidth / 2, _sMixMirror[j].size.top + height / 2, 20, height, type);
	//						}
	//						else if (_sMirror[i].size.left >= _sMixMirror[j].size.left&&_sMirror[i].mixLv)
	//						{
	//							setMirror(false, color, _sMirror[i].size.left + rcwidth / 2, _sMirror[i].size.top + height / 2, 20, height, type);
	//						}
	//						_sMirror[i].mixLv = 1;
	//						_sMixMirror[j].mixLv = 1;

	//					}
	//					for (int k = 0; k < MAX_MMIRROR_NUM; k++)
	//					{

	//						if ((IntersectRect(&temp, &_sMixMirror[k].size, &_sMixMirror[j].size)) && (IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[k].size)))
	//						{

	//							if (_sMirror[i].size.left <= _sMixMirror[j].size.left&&_sMirror[i].size.right <= _sMixMirror[j].size.right)
	//							{
	//								_sMixMirror[k].size.left = _sMixMirror[j].size.left;
	//								_sMixMirror[k].size.right = _sMixMirror[k].size.left + _sMirror[i].size.right - _sMixMirror[j].size.left;
	//							}
	//							else if (_sMirror[i].size.left >= _sMixMirror[j].size.left&&_sMirror[i].size.right >= _sMixMirror[j].size.right)
	//							{
	//								_sMixMirror[k].size.left = _sMirror[i].size.left;
	//								_sMixMirror[k].size.right = _sMixMirror[k].size.left + _sMixMirror[j].size.right - _sMirror[i].size.left;
	//							}
	//						}
	//					}
	//				}
	//			}
	//			else if (!IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[j].size))
	//			{
	//				if (_sMirror[i].mixLv == 1)
	//				{
	//					if (_sMirror[i].mixLv == 1 && _sMixMirror[j].mixLv == 1)
	//					{
	//						_sMirror[i].mixLv = 0;
	//						_sMixMirror[j].mixLv = 0;
	//						for (int k = 0; k < MAX_MMIRROR_NUM; k++)
	//						{
	//							if (!(IntersectRect(&temp, &_sMixMirror[k].size, &_sMixMirror[j].size)) || !(IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[k].size)))
	//							{
	//								eraseMirror(true, k);
	//							}
	//						}
	//					}
	//				}

	//			}
	//		}

	//	}
	//}
}
/*if (_sMirror[i].size.left < _sMirror[j].size.left)
{
width = _sMirror[i].size.right - _sMirror[j].size.left;
if (_sMirror[i].size.top <= _sMirror[j].size.top)height = _sMirror[j].size.bottom - _sMirror[j].size.top;
else if (_sMirror[i].size.top > _sMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;


}
else if (_sMirror[i].size.left >= _sMirror[j].size.left)
{
width = _sMirror[j].size.right - _sMirror[i].size.left;
if (_sMirror[i].size.top <= _sMirror[j].size.top)height = _sMirror[j].size.bottom - _sMirror[j].size.top;
else if (_sMirror[i].size.top > _sMirror[j].size.top)height = _sMirror[i].size.bottom - _sMirror[i].size.top;
}
if (_sMirror[i].mixLv == 0 && _sMirror[j].mixLv == 0)
{

if (_sMirror[i].color == red && _sMirror[j].color == blue || _sMirror[i].color == blue && _sMirror[j].color == red)color = purple;
else if (_sMirror[i].color == red && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == red)color = yellow;
else if (_sMirror[i].color == blue && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == blue)color = bgreen;
else if (_sMirror[i].color == purple && _sMirror[j].color == green || _sMirror[i].color == green && _sMirror[j].color == purple)color = white;
else if (_sMirror[i].color == bgreen && _sMirror[j].color == red || _sMirror[i].color == red && _sMirror[j].color == bgreen)color = white;
else if (_sMirror[i].color == yellow && _sMirror[j].color == blue || _sMirror[i].color == blue && _sMirror[j].color == yellow)color = white;
else color = black;
if (_sMirror[i].type == turnleft&&_sMirror[j].type == turnleft)type = turnleft;
else if (_sMirror[i].type == turnup&&_sMirror[j].type == turnup)type = turnup;
else type = both;
setMirror(false,color, _sMirror[j].size.left+width/2, _sMirror[j].size.top+height/2, width, height, type);
_sMirror[i].mixLv = 1;
_sMirror[j].mixLv = 1;

}
for (int k = 0; k < MAX_MMIRROR_NUM; k++)
{
if (k != j)
{
if ((IntersectRect(&temp, &_sMixMirror[k].size, &_sMirror[j].size)) && (IntersectRect(&temp, &_sMirror[i].size, &_sMixMirror[k].size)))
{
if (_sMixMirror[k].color == purple || _sMixMirror[k].color == yellow || _sMixMirror[k].color == bgreen || _sMixMirror[k].color == white || _sMixMirror[k].color == black)
{
if (_sMirror[i].size.left < _sMirror[j].size.left)
{
_sMixMirror[k].size.left = _sMirror[j].size.left;
_sMixMirror[k].size.right = _sMixMirror[k].size.left + width;
}
else if (_sMirror[i].size.left >= _sMirror[j].size.left)
{
_sMixMirror[k].size.left = _sMirror[i].size.left;
_sMixMirror[k].size.right = _sMixMirror[k].size.left + width;
}

}
_sMirror[i].mixLv = 1;
_sMirror[j].mixLv = 1;
}
}

}


;*/
void world::setMirror(bool what,int color, int ptx, int pty, int width, int height, int type)
{

	if (what==true)
	{
		for (int i = 0; i < MAX_MIRROR_NUM; i++)
		{

			if (_sMirror[i].isMake == false)
			{
				_sMirror[i].color = color;
				_sMirror[i].size = RectMakeCenter(ptx, pty, width, height);
				_sMirror[i].type = type;
				_sMirror[i].isMake = true;
				_sMirror[i].mixLv = 0;
				_sMirror[i].isCanPush = false;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_MMIRROR_NUM; i++)
		{

			if (_sMixMirror[i].isMake == false)
			{
				_sMixMirror[i].color = color;
				_sMixMirror[i].size = RectMakeCenter(ptx, pty, width, height);
				_sMixMirror[i].type = type;
				_sMixMirror[i].isMake = true;
				_sMixMirror[i].mixLv = 0;
				_sMixMirror[i].isCanPush = false;
				break;
			}
		}
	}
	//_sMirror[_iMirrorNum];
	
	
	//_iMirrorNum ++;
//	_vMirror.push_back(mirror);
}


void world:: eraseMirror(bool mixLvmirror,int num)
{
	if (mixLvmirror == false)
	{
		ZeroMemory(&_sMirror[num], sizeof(_sMirror[num]));

		_sMirror[num].isMake = false;
	}
	else
	{
		ZeroMemory(&_sMixMirror[num], sizeof(_sMixMirror[num]));

		_sMixMirror[num].isMake = false;
	}
	
		
	
	
}

void world::reset()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		ZeroMemory(&_sAliceFrame, sizeof(_sAliceFrame));
		ZeroMemory(&_sStructure, sizeof(_sStructure));
		ZeroMemory(&_sMStructure, sizeof(_sMStructure));
		ZeroMemory(&_sMixMirror, sizeof(_sMixMirror));
		//for (int i = 0; i < MAX_STRUCTURE1_NUM; i++)
		//{
		//	_rStruc1[i] = RectMakeCenter(100+200 * (i % 5),200+ 200 * (i / 5), 100, 100);
		//}
		//for (int i = 0; i < MAX_STRUCTURE2_NUM; i++)
		//{
		//	_rStruc2[i] = RectMakeCenter(200+200 * (i % 5),200+ 200 * (i / 5), 100, 100);
		//}



		_rFloor = RectMakeCenter(1000, 580, 2000, 150);										//바닥
		//_sDoor[0] = RectMakeCenter(100, _rFloor.top - 50, 70, 100);							//앨리스 문
		_sDoor[1].size = RectMakeCenter(400, _rFloor.top - 50, 70, 100);							//3층 복도
		_sDoor[2].size = RectMakeCenter(500, _rFloor.top - 50, 70, 100);							//3측 복도




		_rSavePoint[0] = RectMakeCenter(250, 410, 50, 50);									//3층 복도

		_iMirrorNum = 0;
		for (int i = 0; i < MAX_MIRROR_NUM; i++)
		{
			_sMirror[i].isMake = false;
		}
		for (int i = 0; i < MAX_MMIRROR_NUM; i++)
		{
			_sMixMirror[i].isMake = false;
		}
		//_sMirror[0].isMake = true;
		//ON/OFF 체크
		_bIsMirror = false;


		//fadeout
		_iFadelevel = 2;
		_iFadeTime = 255;

		//움직이는 단계
		_iMoveLevel = 0;


		_fGravity = 0;
		//_iPlace = _sMap.kind==Stage1;
		_sMap.kind = Stage1;
		_sMap.isBGreen = false;
		_sMap.isBlue = false;
		_sMap.isGreen = false;
		_sMap.isPurple = false;
		_sMap.isRed = false;
		_sMap.isYellow = false;
		//앨리스 설정
		_sAlice.weight = 200;
		_sAlice.jumpPower = 10;
		_sAlice.motion = stand;
		_sAlice.width = 100;
		_sAlice.hight = 150;
		_sAlice.size = RectMakeCenter(100, 600, _sAlice.width, _sAlice.hight);
		_sAlice.isRight = true;
		_sAlice.canPull = false;
		_sAlice.speed = 4;

		_sAliceimage.stand = IMAGEMANAGER->findImage("aliceStand");
		_sAliceimage.jumping = IMAGEMANAGER->findImage("aliceJump");

		setAliceFrame(stand, 5);
		setAliceFrame(jumping, 5);
		setStage1();
		_fLoofMapX = 0;
		_fLoofMapY = 0;
		_sMap.iscamera = false;
	}
}
//void world::rectPush(sFurniture *sFurniture)
//{
//	RECT temp;
//	if (IntersectRect(&temp, &(*sMirror).size, &_sAlice.size))
//	{
//		(*sFurniture).ispush = true;
//		if ((*sMirror).size.left <= _sAlice.size.right &&
//			(*sMirror).size.left + 5 > _sAlice.size.right && (*sMirror).size.right<WINSIZEX)
//		{
//			if (_sAlice.motion != jumping)
//			{
//				_sAlice.motion = pushing;
//				(*sMirror).size.left += (*sFurniture).weight / 150;
//				(*sMirror).size.right += (*sFurniture).weight / 150;
//			}
//
//		}
//		else if ((*sMirror).size.right >= _sAlice.size.left &&
//			(*sMirror).size.right - 5 < _sAlice.size.left && (*sMirror).size.left>0)
//		{
//			if (_sAlice.motion != jumping)
//			{
//				_sAlice.motion = pushing;
//				(*sMirror).size.left -= (*sFurniture).weight / 150;
//				(*sMirror).size.right -= (*sFurniture).weight / 150;
//			}
//		}
//	}
//	else
//	{
//		(*sFurniture).ispush = false;
//	}
//}


//void world::rectPull(sFurniture *sFurniture)
//{
//	RECT temp;
//	RECT pullRange;
//	//pullRange=RectMakeCenter(
//	int rcwidth;
//	rcwidth = (*sMirror).size.right - (*sMirror).size.left;
//	///if (IntersectRect(&temp, &(*sMirror).size, &_sAlice.size))
//	//{
//	if ((*sMirror).size.left >= _sAlice.size.right &&
//		(*sMirror).size.left - 5 <= _sAlice.size.right)
//	{
//		if (_sAlice.motion != jumping)_sAlice.canPull = true;
//		if (KEYMANAGER->isStayKeyDown('E') && _sAlice.motion != jumping)
//		{
//
//			if (_sAlice.isPull == false)_sAlice.isPull = true;
//			else _sAlice.isPull = false;
//			/*_sAlice.motion = pulling;
//			(*sMirror).size.left = _sAlice.size.right;
//			(*sMirror).size.right = (*sMirror).size.left + rcwidth;*/
//		}
//		if (KEYMANAGER->isOnceKeyUp('E') && _sAlice.motion == pulling)
//		{
//
//			//_sAlice.motion = stand;
//		}
//		//_sAlice.size.right = (*sMirror).size.left - 1;
//		//_sAlice.size.left = _sAlice.size.right - _sAlice.width;
//	}
//	else if ((*sMirror).size.right <= _sAlice.size.left &&
//		(*sMirror).size.right + 5 >= _sAlice.size.left)
//	{
//		if (_sAlice.motion != jumping)_sAlice.canPull = true;
//		if (KEYMANAGER->isStayKeyDown('E') && _sAlice.motion != jumping)
//		{
//			if (_sAlice.isPull == false)_sAlice.isPull = true;
//			else _sAlice.isPull = false;
//			/*_sAlice.motion = pulling;
//			(*sMirror).size.right = _sAlice.size.left ;
//			(*sMirror).size.left = (*sMirror).size.right - rcwidth;*/
//		}
//		if (KEYMANAGER->isOnceKeyUp('E') && _sAlice.motion == pulling)
//		{
//
//			//_sAlice.motion = stand;
//		}
//		//_sAlice.size.left = (*sMirror).size.right + 1;
//		//_sAlice.size.right = _sAlice.size.left + _sAlice.width;
//	}
//	else
//	{
//		_sAlice.canPull = false;
//	}
//
//
//	if (_sAlice.isPull == true)
//	{
//
//		(*sMirror).size.left = _sAlice.size.right;
//		(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//		_sAlice.motion = pulling;
//		/*	if ((*sMirror).size.left >= _sAlice.size.right &&
//		(*sMirror).size.left - 5 <= _sAlice.size.right)
//		{
//		_sAlice.motion = pulling;
//		(*sMirror).size.left = _sAlice.size.right;
//		(*sMirror).size.right = (*sMirror).size.left + rcwidth;
//		}
//		else if ((*sMirror).size.right <= _sAlice.size.left &&
//		(*sMirror).size.right + 5 >= _sAlice.size.left)
//		{
//		_sAlice.motion = pulling;
//		(*sMirror).size.right = _sAlice.size.left;
//		(*sMirror).size.left = (*sMirror).size.right - rcwidth;
//		}*/
//	}
//	else
//	{
//		if (_sAlice.motion == pulling)_sAlice.motion = stand;
//	}
//	//else if ((*rc).top <= _sAlice.size.bottom)// &&(*rc).bottom  < alice.size.bottom)
//	//{
//	//	_sAlice.size.bottom = (*rc).top - 0.5f;
//	//	_sAlice.size.top = _sAlice.size.bottom - _sAlice.hight;
//	//	_fGravity = 0;
//	//	_sAlice.jumpPower = 5;
//	//	if (_sAlice.motion == jumping)_sAlice.motion = stand;
//	//}
//	//}
//}

//지금반사기획중점점업데이트

//보고서 클래스 설명,각각의 함수 설명


//
//void coloring()
//{
//	
//
//}
//


