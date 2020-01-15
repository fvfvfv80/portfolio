#include "stdafx.h"
#include "cRobotGame.h"


cRobotGame::cRobotGame()
{
}


cRobotGame::~cRobotGame()
{
}


HRESULT cRobotGame::init(void)
{
	
	ImageInit();

	ZeroMemory(&_tRt, sizeof(sRobot));
	
	_tRt.state = STATE_TEMP;

	for (int i = 0;i < 5;i++)
	{
		ZeroMemory(&_robot[i], sizeof(sRobot));
	}

	for (int i = 0;i < 16;i++)
	{
		for (int j = 0;j < 16;j++)
		{
			//타일 초기화
			_tile[i][j].pos.x=50+i * 60;
			_tile[i][j].pos.y =50+j * 60;
			_tile[i][j].isToken = false;
			_tile[i][j].rc = RectMakeCenter(_tile[i][j].pos.x, _tile[i][j].pos.y, 60, 60);
		}

		//껍질? 초기화
		sWall* wall= new sWall;
		(*wall).rc = RectMakeCenter(20, 50 + i * 60, 10, 60);
		(*wall).isVer = false;
		_wall.push_back(wall);
		wall = new sWall;
		(*wall).rc = RectMakeCenter(50 + 15 * 60 + 30, 50 + i * 60, 10, 60);
		(*wall).isVer = false;
		_wall.push_back(wall);
		wall = new sWall;
		(*wall).rc = RectMakeCenter(50 + i * 60, 20, 60, 10);
		(*wall).isVer = true;
		_wall.push_back(wall);
		wall = new sWall;
		(*wall).rc = RectMakeCenter(50 + i * 60, 50 + 15 * 60 + 30, 60, 10);
		(*wall).isVer = true;
		_wall.push_back(wall);
	}
	//노가다 벽 초기화
	TestWallSet();

	//가운데 가는거 막음
	_tile[7][7].isGo = false;
	_tile[7][8].isGo = false;
	_tile[8][7].isGo = false;
	_tile[8][8].isGo = false;

	//말 셋팅
	PlayerSet();
	true;
	//색 세팅
	_gray = CreateSolidBrush(RGB(80, 80, 80));
	_red = CreateSolidBrush(RGB(255, 0, 0));
	_blue = CreateSolidBrush(RGB(0, 0, 255));
	_green = CreateSolidBrush(RGB(0, 255, 0));
	_yellow = CreateSolidBrush(RGB(255, 255,0));
	_white = CreateSolidBrush(RGB(200, 200, 200));
	 a = RND->getInt(100);
	//포인터 셋팅
	_pRobot = &_tRt;
	return S_OK;
}
void cRobotGame::release(void)
{
	
	SAFE_DELETE(_gray);
	SAFE_DELETE(_red);
	SAFE_DELETE(_blue);
	SAFE_DELETE(_green);
	SAFE_DELETE(_yellow);
	SAFE_DELETE(_white);
	SAFE_DELETE(_pen);
	for (int i = 0;i < _wall.size(); i++)
	{
		SAFE_DELETE(_wall[i]);
	}


}
void cRobotGame::update(void)
{	
	for (int i = 0;i < 5;i++)
	{
		
		/*
		1. 커서가 로봇안에 들어갔나
		2.로봇의 생태가 보통 아니면 비어있는지
		3.마우스 왼쪽버튼을 눌렀는지
		4.다맞으면 로봇의 포인터를 바꿔준다
		*/
		if (PtInRect(&_robot[i].rc, _ptMouse))if ((*_pRobot).state == STATE_IDLE|| (*_pRobot).state == STATE_TEMP)if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))_pRobot = &_robot[i];
	}
	for (int i = 0;i < 5;i++)
	{
		/* 커서가 로봇 밖에 있을때 
		2.로봇의 생태가 보통이고
		3.마우스 왼쪽버튼을 눌렀으면
		4.다맞으면 로봇 포인터 껍데기로
		*/
		if (!PtInRect(&_robot[i].rc, _ptMouse))if ((*_pRobot).state == STATE_IDLE)if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))_pRobot = &_tRt;
	}
	//이건 내가 생각한 모드 1
	NormalMode(_pRobot);
	//리셋
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		for (int i = 0;i < 5;i++)
		{
			//원래있던장소로 다보내버리고
			_robot[i].state = STATE_IDLE;
			_robot[i].pos = _robot[i].prevPos;
			_robot[i].rc.left = _robot[i].pos.x - 20;
			_robot[i].rc.right = _robot[i].rc.left + 40;
			_robot[i].rc.top = _robot[i].pos.y - 20;
			_robot[i].rc.bottom = _robot[i].rc.top + 40;
		}

		/*
		vector 메모리 10이었던거에서 하나더 입력하면 11이되는게 아니라 20이 된다
		clear하면 데이터는 사라지지만 메모리는 20으로 계속 남음
		swap을 사용해서 빈 벡터를 넣어주면 메모리 청소도 됨
		*/
		//백터도 초기화
		vector<sRoute*>().swap(_route);
		//vector<sRoute*> temp;
		//_route.clear();
		//_route.swap(temp);
		
	}
	//맞았어
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//포지션들다 셋팅해주고
		for (int i = 0;i < 5;i++)
		{
			_robot[i].prevPos = _robot[i].pos;
		}
		//올렸던 토큰치우고
		for (int i = 0;i < 17;i++)
		{
			if(_token[i].isOpen==true)_token[i].isOpen = false;
		}
		vector<sRoute*>().swap(_route);
		/*
		vector 메모리 10이었던거에서 하나더 입력하면 11이되는게 아니라 20이 된다
		clear하면 데이터는 사라지지만 메모리는 20으로 계속 남음
		swap을 사용해서 빈 벡터를 넣어주면 메모리 청소도 됨
		*/
		//벡터 초기화
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//게임 시작!
		while (true)
		{
			//토큰열고
			bool isopen=false;
			for (int i = 0;i < 17;i++)
			{
				//열려있으면 열지마
				if (_token[i].isOpen == true)
				{
					isopen = true;
					break;
				}
			}
			//열려있으면 나가고
			if (isopen == true)break;
			//열려있지않으면 랜덤을 하나 골라서
			int i = RND->getInt(17);
			//열렸는지 확인하고 아니면 셋팅
			if (_token[i].isOpened == true)continue;
			_token[i].isOpened = true;
			_token[i].isOpen = true;
			break;
		}
	}
}
void cRobotGame::render(void)
{
	
#pragma region  글자셋팅

	char str[128];

	//여긴 새로운 방식 (근데 쓸일이 있을랑가 모르겠당 ㅋ)
	//전부다 이미지로 할꺼 아님?
	HFONT oldFont;
	HFONT font1;
	/*
	CreateFont(
	60,					//문자폭
	0,					//문자높이
	0,					//문자 기울기
	0,					//문자 방향
	600,				//문자 굵기
	0,					//기울기(불값 true, false)
	0,					//밑줄(할꺼냐 말꺼냐)
	1,					//취소선(오덕들의 전유물)
	HANGUL_CHARSET,		//문자셋팅
	0,					//출력 정확도
	0,					//클리핑 정확도
	0,					//출력의 질
	0,					//자간
	TEXT("돋움체")		//폰트
	);
	*/
	
	//출력폰트 예제 1
	font1 = CreateFont(120, 0, 0, 0, 600, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font1);
	sprintf_s(str, "%d", _route.size());//a);
	TextOut(getMemDC(), 1030, 100, "Route", sizeof("Route"));
	TextOut(getMemDC(), 1145, 400, str, sizeof(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font1);
#pragma endregion


	




	for (int i = 0;i < 16;i++)
	{
		for (int j = 0;j < 16;j++)
		{
			//타일 출력
			Rectangle(getMemDC(),_tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].rc.right, _tile[i][j].rc.bottom);
		}
	}
	for (int i = 0;i < 17;i++)
	{
		//색과 문양에 따라서 맵에 토큰 출력
		if (_token[i].color == BLUE)
		{
			if (_token[i].type == TYPE1)
			{
				IMAGEMANAGER->render("blue_type1", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			}
			else if (_token[i].type == TYPE2)IMAGEMANAGER->render("blue_type2", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE3)IMAGEMANAGER->render("blue_type3", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE4)IMAGEMANAGER->render("blue_type4", getMemDC(), _token[i].rc.left, _token[i].rc.top);
		}
		else if (_token[i].color == RED)
		{
			if (_token[i].type == TYPE1)IMAGEMANAGER->render("red_type1", getMemDC(), _token[i].rc.left, _token[i].rc.top);

			else if (_token[i].type == TYPE3)IMAGEMANAGER->render("red_type3", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE4)IMAGEMANAGER->render("red_type4", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE2)IMAGEMANAGER->render("red_type2", getMemDC(), _token[i].rc.left, _token[i].rc.top);
		}

		else if (_token[i].color == GREEN)
		{
			if (_token[i].type == TYPE1)IMAGEMANAGER->render("green_type1", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE2)IMAGEMANAGER->render("green_type2", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE3)IMAGEMANAGER->render("green_type3", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE4)IMAGEMANAGER->render("green_type4", getMemDC(), _token[i].rc.left, _token[i].rc.top);
		}
		else if (_token[i].color == YELLOW)
		{
			if (_token[i].type == TYPE1)IMAGEMANAGER->render("yellow_type1", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE2)IMAGEMANAGER->render("yellow_type2", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE3)IMAGEMANAGER->render("yellow_type3", getMemDC(), _token[i].rc.left, _token[i].rc.top);
			else if (_token[i].type == TYPE4)IMAGEMANAGER->render("yellow_type4", getMemDC(), _token[i].rc.left, _token[i].rc.top);
		}
		else  IMAGEMANAGER->render("dark", getMemDC(), _token[i].rc.left, _token[i].rc.top);

		//색과 문양에 따라서 맵밖에 토큰 생성
		if (_token[i].isOpen == true)
		{
			if (_token[i].color == BLUE)
			{
				if (_token[i].type == TYPE1)IMAGEMANAGER->render("blue_type1", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE2)IMAGEMANAGER->render("blue_type2", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE3)IMAGEMANAGER->render("blue_type3", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE4)IMAGEMANAGER->render("blue_type4", getMemDC(), 1150, 750);
			}
			else if (_token[i].color == RED)
			{
				if (_token[i].type == TYPE1)IMAGEMANAGER->render("red_type1", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE3)IMAGEMANAGER->render("red_type3", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE4)IMAGEMANAGER->render("red_type4", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE2)IMAGEMANAGER->render("red_type2", getMemDC(), 1150, 750);
			}
			else if (_token[i].color == GREEN)
			{
				if (_token[i].type == TYPE1)IMAGEMANAGER->render("green_type1", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE2)IMAGEMANAGER->render("green_type2", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE3)IMAGEMANAGER->render("green_type3", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE4)IMAGEMANAGER->render("green_type4", getMemDC(), 1150, 750);
			}
			else if (_token[i].color == YELLOW)
			{
				if (_token[i].type == TYPE1)IMAGEMANAGER->render("yellow_type1", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE2)IMAGEMANAGER->render("yellow_type2", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE3)IMAGEMANAGER->render("yellow_type3", getMemDC(), 1150, 750);
				else if (_token[i].type == TYPE4)IMAGEMANAGER->render("yellow_type4", getMemDC(), 1150, 750);
			}
			else  IMAGEMANAGER->render("dark", getMemDC(), 1150, 750);
		}
	}


	//말 랜더링
	HPEN pen;
	pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HPEN oldPen;
	oldPen=(HPEN)SelectObject(getMemDC(), pen);

	for (int i = 0;i < 5;i++)
	{
		Rectangle(getMemDC(), _robot[i].rc.left, _robot[i].rc.top, _robot[i].rc.right, _robot[i].rc.bottom);
		if (_robot[i].color == RED)	FillRect(getMemDC(), &_robot[i].rc, _red);
		else if (_robot[i].color == BLUE)	FillRect(getMemDC(), &_robot[i].rc, _blue);
		else if (_robot[i].color == GREEN)	FillRect(getMemDC(), &_robot[i].rc, _green);
		else if (_robot[i].color == WHITE)	FillRect(getMemDC(), &_robot[i].rc, _white);
		else if (_robot[i].color == YELLOW)	FillRect(getMemDC(), &_robot[i].rc, _yellow);
	}
	SelectObject(getMemDC(), oldPen);
	DeleteObject(pen);
	//가운데 부분 막아
	RECT block;
	block = RectMakeCenter(_tile[7][7].pos.x + 30, _tile[7][7].pos.y + 30, 120,120);
	Rectangle(getMemDC(), block.left, block.top, block.right, block.bottom);
	FillRect(getMemDC(), &block, _gray);

	//벽 색칠해
	for (int i = 0;i < _wall.size(); i++)
	{	
		Rectangle(getMemDC(), (*_wall[i]).rc.left, (*_wall[i]).rc.top, (*_wall[i]).rc.right, (*_wall[i]).rc.bottom);
		FillRect(getMemDC(), &(*_wall[i]).rc, _gray);
	}
}

void cRobotGame::ImageInit()
{
	IMAGEMANAGER->addImage("blue_type1", "resources\\blue_type1.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blue_type2", "resources\\blue_type2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blue_type3", "resources\\blue_type3.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blue_type4", "resources\\blue_type4.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("red_type1", "resources\\red_type1.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("red_type3", "resources\\red_type3.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("red_type4", "resources\\red_type4.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("red_type2", "resources\\red_type2.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("green_type1", "resources\\green_type1.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("green_type2", "resources\\green_type2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("green_type3", "resources\\green_type3.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("green_type4", "resources\\green_type4.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("yellow_type1", "resources\\yellow_type1.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("yellow_type2", "resources\\yellow_type2.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("yellow_type3", "resources\\yellow_type3.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("yellow_type4", "resources\\yellow_type4.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("dark", "resources\\dark.bmp", 60, 60, true, RGB(255, 0, 255));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//방향키를 누르면 순간이동하지 않고 말이 이동하는 것을 보여준다
void cRobotGame::NormalMode(sRobot* rt)
{
	if (_pRobot != &_tRt)
	{
		//방향키로 말 움직이기
		if ((*_pRobot).state == STATE_IDLE)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				(*_pRobot).state = STATE_LEFT;
				sRoute* a = new sRoute;
				(*a).record = (*_pRobot).pos;
				(*a).prRob = _pRobot;
				_route.push_back(a);
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				(*_pRobot).state = STATE_RIGHT;
				sRoute* a = new sRoute;
				(*a).record = (*_pRobot).pos;
				(*a).prRob = _pRobot;
				_route.push_back(a);
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				(*_pRobot).state = STATE_UP;
				sRoute* a = new sRoute;
				(*a).record = (*_pRobot).pos;
				(*a).prRob = _pRobot;
				_route.push_back(a);
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				(*_pRobot).state = STATE_DOWN;
				sRoute* a = new sRoute;
				(*a).record = (*_pRobot).pos;
				(*a).prRob = _pRobot;
				_route.push_back(a);
			}
		}
		// 말 상태의 따라 움직여주기
		if ((*_pRobot).state == STATE_LEFT)OffsetRect(&(*_pRobot).rc, -(*_pRobot).speed, 0);
		else if ((*_pRobot).state == STATE_RIGHT)OffsetRect(&(*_pRobot).rc, (*_pRobot).speed, 0);
		else if ((*_pRobot).state == STATE_UP)OffsetRect(&(*_pRobot).rc, 0, -(*_pRobot).speed);
		else if ((*_pRobot).state == STATE_DOWN)OffsetRect(&(*_pRobot).rc, 0, (*_pRobot).speed);
		for (int i = 0;i < 16;i++)
		{
			for (int j = 0;j < 16;j++)
			{
				//말의 포지션을 항상 업데이트***
				if ((*_pRobot).rc.left == _tile[i][j].pos.x - 20 || (*_pRobot).rc.right == _tile[i][j].pos.x + 20)(*_pRobot).pos.x = _tile[i][j].pos.x;
				if ((*_pRobot).rc.top == _tile[i][j].pos.y - 20 || (*_pRobot).rc.bottom == _tile[i][j].pos.y + 20)(*_pRobot).pos.y = _tile[i][j].pos.y;
			}
		}
		for (int i = 0;i < _wall.size();i++)
		{
			//벽과 충돌체크***
			RECT temp;
			if (IntersectRect(&temp, &(*_pRobot).rc, &(*_wall[i]).rc))
			{
				(*_pRobot).state = STATE_IDLE;
				(*_pRobot).rc.left = (*_pRobot).pos.x - 20;
				(*_pRobot).rc.right = (*_pRobot).rc.left + 40;
				(*_pRobot).rc.top = (*_pRobot).pos.y - 20;
				(*_pRobot).rc.bottom = (*_pRobot).rc.top + 40;
			}
		}

		
		for (int i = 0;i < 16;i++)
		{
			for (int j = 0;j < 16;j++)
			{
				//타일의 갈수 없는 가운데 부분 충돌체크 //이부분은 벽으로 만들고 빼도 될거 같은디...
				RECT temp;
				if (IntersectRect(&temp, &(*_pRobot).rc, &_tile[i][j].rc))
				{
					if (_tile[i][j].isGo == false)
					{
						(*_pRobot).state = STATE_IDLE;
						(*_pRobot).rc.left = (*_pRobot).pos.x - 20;
						(*_pRobot).rc.right = (*_pRobot).rc.left + 40;
						(*_pRobot).rc.top = (*_pRobot).pos.y - 20;
						(*_pRobot).rc.bottom = (*_pRobot).rc.top + 40;
					}	
				}
			}
		}
		for (int i = 0;i < 5;i++)
		{
			//지정하는 로봇이 맞으면 돌려
			if (_pRobot == &_robot[i])continue;
			//아니면 다른 로봇들과의 충돌체크 이군
			RECT temp;
			if (IntersectRect(&temp, &(*_pRobot).rc, &_robot[i].rc))
			{
				(*_pRobot).state = STATE_IDLE;
				(*_pRobot).rc.left = (*_pRobot).pos.x - 20;
				(*_pRobot).rc.right = (*_pRobot).rc.left + 40;
				(*_pRobot).rc.top = (*_pRobot).pos.y - 20;
				(*_pRobot).rc.bottom = (*_pRobot).rc.top + 40;
			}
		}
	}

	//뒤로가기 Ctr+Z
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		int i = _route.size()-1;
		if (i >= 0)
		{
			_pRobot = (*_route[i]).prRob;
			(*_pRobot).pos = (*_route[i]).record;
			(*_pRobot).rc.left = (*_pRobot).pos.x - 20;
			(*_pRobot).rc.right = (*_pRobot).rc.left + 40;
			(*_pRobot).rc.top = (*_pRobot).pos.y - 20;
			(*_pRobot).rc.bottom = (*_pRobot).rc.top + 40;
			_route.pop_back();
		}
		
	
	}
}

//벽 노가다+토큰 노가다
void cRobotGame::TestWallSet()
{
	WallSet(_tile[1][0].pos , false);
	WallSet(_tile[9][0].pos , false);
	WallSet(_tile[13][1].pos, false);
	WallSet(_tile[3][1].pos, false);
	WallSet(_tile[1][2].pos, false);
	WallSet(_tile[10][2].pos, false);
	WallSet(_tile[6][3].pos, false);
	WallSet(_tile[2][6].pos, false);
	WallSet(_tile[13][6].pos, false);
	WallSet(_tile[10][7].pos, false);
	WallSet(_tile[3][9].pos, false);
	WallSet(_tile[1][10].pos, false);
	WallSet(_tile[12][10].pos, false);
	WallSet(_tile[7][10].pos, false);
	WallSet(_tile[10][11].pos, false);
	WallSet(_tile[13][12].pos, false);
	WallSet(_tile[5][13].pos, false);
	WallSet(_tile[2][14].pos, false);
	WallSet(_tile[9][14].pos, false);
	WallSet(_tile[3][15].pos, false);
	WallSet(_tile[11][15].pos, false);
	WallSet(_tile[15][3].pos , true);
	WallSet(_tile[0][5].pos , true);
	WallSet(_tile[14][0].pos, true);
	WallSet(_tile[4][0].pos, true);
	WallSet(_tile[1][1].pos, true);
	WallSet(_tile[11][2].pos, true);
	WallSet(_tile[6][3].pos, true);
	WallSet(_tile[3][6].pos, true);
	WallSet(_tile[13][6].pos, true);
	WallSet(_tile[10][6].pos, true);
	WallSet(_tile[4][9].pos, true);
	WallSet(_tile[1][9].pos, true);
	WallSet(_tile[13][9].pos, true);
	WallSet(_tile[8][9].pos, true);
	WallSet(_tile[10][11].pos, true);
	WallSet(_tile[14][12].pos, true);
	WallSet(_tile[6][12].pos, true);
	WallSet(_tile[2][14].pos, true);
	WallSet(_tile[9][13].pos, true);
	WallSet(_tile[15][8].pos, true);
	WallSet(_tile[0][11].pos, true);
	//4삼각3사각2원1육각
	TokenSet(0, &_tile[8][10], DARK, DARK);
	TokenSet(1, &_tile[14][1], TYPE4, RED);
	TokenSet(2, &_tile[1][2], TYPE4 , GREEN);
	TokenSet(3, &_tile[11][2], TYPE1 , BLUE);
	TokenSet(4, &_tile[6][3], TYPE1 , YELLOW);
	TokenSet(5, &_tile[3][6], TYPE3 , BLUE);
	TokenSet(6, &_tile[13][6], TYPE2 , GREEN);
	TokenSet(7, &_tile[10][7], TYPE3 , YELLOW);
	TokenSet(8, &_tile[1][10], TYPE1 , GREEN);
	TokenSet(9, &_tile[13][10], TYPE1 , RED);
	TokenSet(10, &_tile[14][12], TYPE4 , YELLOW);
	TokenSet(11, &_tile[6][13], TYPE4 , BLUE);
	TokenSet(12, &_tile[2][14], TYPE3, RED);
	TokenSet(13, &_tile[4][1], TYPE2, RED);
	TokenSet(14, &_tile[4][9], TYPE2 , YELLOW);
	TokenSet(15, &_tile[10][11], TYPE3 , GREEN);
	TokenSet(16, &_tile[9][14], TYPE2 , BLUE);
}

//벽 노가다를 편하게 해주는 함수
void cRobotGame::WallSet(POINT pt, bool isver)
{
	if (isver == false)
	{
		sWall *wall = new sWall;
		(*wall).rc = RectMakeCenter(pt.x + 30, pt.y, 10, 60);
		(*wall).isVer = isver;
		_wall.push_back(wall);
	}
	else if(isver == true)
	{
		sWall *wall = new sWall;
		(*wall).rc = RectMakeCenter(pt.x , pt.y+30, 60, 10);
		(*wall).isVer = isver;
		_wall.push_back(wall);
	}
}
//토큰 노가다를 편하게 해주는 함수
void cRobotGame::TokenSet(int num,sTile* tk, int type, int color)
{
	_token[num].rc = RectMakeCenter((*tk).pos.x, (*tk).pos.y, 60, 60);
	(*tk).isToken = true;
	_token[num].type = (eTOKEN_TYPE)type;
	_token[num].color = (COLOR)color;
	_token[num].isOpen = false;
	_token[num].isOpened = false;
}
//말 셋팅
void cRobotGame::PlayerSet()
{
	for (int i = 0;i < 5;i++)
	{
		while (true)
		{
			int x = RND->getInt(15);
			int y= RND->getInt(15);
			if (_tile[x][y].isToken == true)continue;
			else
			{
				_robot[i].pos.x = _tile[x][y].pos.x;
				_robot[i].pos.y = _tile[x][y].pos.y;
				_robot[i].prevPos = _robot[i].pos;
				_robot[i].speed = 15;//6
				_robot[i].state = STATE_IDLE;
				_robot[i].rc = RectMakeCenter(_robot[i].pos.x, _robot[i].pos.y, 40, 40);
				_tile[x][y].isToken = true;
				break;
			}
		}
		_robot[i].color = i;
	}
	
}
