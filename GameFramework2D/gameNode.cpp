#include "StdAfx.h"
#include "gameNode.h"

//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================
gameNode::gameNode(void)
{
}
gameNode::~gameNode(void)
{
}
/////////////////////////////////////////////////////////////////////

//==================================================================
//		## 초기화 - init(void) ## 
//==================================================================
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

//==================================================================
//		## 초기화 - init(bool managerInit) ## 
//==================================================================
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	
	if (managerInit)
	{
		KEYMANAGER->init();				//키매니져 셋팅
		IMAGEMANAGER->init();			//이미지매니져 셋팅
		TIMEMANAGER->init();			//타임매니져 셋팅
		TXTDATA->init();				//텍스트데이타 세팅
		SCENEMANAGER->init();			//씬매니져 셋팅
		EFFECTMANAGER->init();			//이펙트매니져 셋팅
	}

	return S_OK;
}

//==================================================================
//		## 해제 - release(void) ## 
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//키매니져 싱글톤 해제
		KEYMANAGER->releaseSingleton();
		//이미지매니져 싱글톤 해제
		IMAGEMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->releaseSingleton();
		//텍트스데이타 싱글톤 해제
		TXTDATA->releaseSingleton();
		//씬매니져 싱글톤 해제
		SCENEMANAGER->releaseSingleton();
		//이펙트매니져 싱글톤 해제
		EFFECTMANAGER->releaseSingleton();
	}

	//DC해제
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## 업데이트 - update(void) ## 
//==================================================================
void gameNode::update(void)
{
}

//==================================================================
//		## 렌더 - render(void) ## 
//==================================================================
void gameNode::render(void)
{
}

//==================================================================
//		## 메세지 프로시져 ## (윈도우 프로시져를 이곳에서 처리한다)
//==================================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
					break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

