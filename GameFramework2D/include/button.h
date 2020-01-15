#pragma once
#include "gameNode.h"
//==================================================================
//		## button ## (버튼 클래스)
//==================================================================

//함수포인터 타입 재정의
typedef void(*CALLBACK_FUNCTION)(void);

//버튼업,다운 이넘문
enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction; //버튼상태
	const char* _imageName;		//버튼이미지 이름
	image* _image;				//버튼이미지
	RECT _rc;					//버튼렉트
	float _x, _y;				//위치

	POINT _btnDownFramePoint;	//버튼다운 프레임 포인트
	POINT _btnUpFramePoint;		//버튼업 프레임 포인트

	CALLBACK_FUNCTION _callbackFunction; //콜백함수 원형 선언

public:
	//초기화(이미지이름, 위치x, 위치y, 버튼다운 프레임 포인트, 버튼업 프레임 포인트, 버튼콜백함수)
	HRESULT init(const char* imageName, int x, int y, 
		POINT btnDownFramePoint, POINT btnUpFramePoint, 
		CALLBACK_FUNCTION cbFunction);
	void release(void);
	void update(void);
	void render(void);

	button();
	~button();
};

