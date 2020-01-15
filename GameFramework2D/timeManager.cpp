#include "stdafx.h"
#include "timeManager.h"
timeManager::timeManager()
{
}
timeManager::~timeManager()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================

//타이머 초기화
HRESULT timeManager::init(void)
{
	//타이머 클래스 생성및 초기화
	_timer = new timer;
	_timer->init();

	return S_OK;
}

//타이머 해제
void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

//타이머 업데이트 (타이머 프레임 적용)
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//타이머 HDC에 정보 표시하기
void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//글자 배경모드 (TRANSPARENT: 투명, QPAQUEL: 불투명)
	SetBkMode(hdc, TRANSPARENT);
	//글자 색상
	SetTextColor(hdc, RGB(255, 0, 255));

//#ifdef _DEBUG
//	if(_timer != NULL)
//	{
//		//프레임 찍는다
//		sprintf(str, "FPS : %d", _timer->getFrameRate());
//		TextOut(hdc, 0, 0, str, strlen(str));
//		//월드타임 찍는다(전체경과시간)
//		sprintf(str, "worldTime : %f", _timer->getWorldTime());
//		TextOut(hdc, 0, 20, str, strlen(str));
//		//갱신 tick 찍는다
//		sprintf(str, "elpasedTime : %f", _timer->getElapsedTime());
//		TextOut(hdc, 0, 40, str, strlen(str));
//	}
//#else
//	if (time != NULL)
//	{
//		//프레임 찍는다
//		sprintf(str, "framePerSec : %d", _timer->getFrameRate());
//		TextOut(hdc, 0, 0, str, strlen(str));
//	}
//#endif
}
