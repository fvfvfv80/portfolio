#pragma once
#include "image.h"
//==================================================================
//		## gameNode ## (게임노드)
//==================================================================

//백버퍼 이미지를 스태틱으로 만들어 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", 1400, 1000);


class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//매니져 초기화 했냐?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 가져오기
	image* getBackBuffer(void) { return _backBuffer; }
	//메모리버퍼(MemDC) 가져오기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//화면버퍼(HDC) 가져오기
	HDC getHDC() { return _hdc; }

	//메세지 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wparam, LPARAM lparam);

	gameNode(void);
	virtual ~gameNode(void);
};
