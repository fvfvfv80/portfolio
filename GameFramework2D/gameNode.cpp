#include "StdAfx.h"
#include "gameNode.h"

//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================
gameNode::gameNode(void)
{
}
gameNode::~gameNode(void)
{
}
/////////////////////////////////////////////////////////////////////

//==================================================================
//		## �ʱ�ȭ - init(void) ## 
//==================================================================
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

//==================================================================
//		## �ʱ�ȭ - init(bool managerInit) ## 
//==================================================================
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	
	if (managerInit)
	{
		KEYMANAGER->init();				//Ű�Ŵ��� ����
		IMAGEMANAGER->init();			//�̹����Ŵ��� ����
		TIMEMANAGER->init();			//Ÿ�ӸŴ��� ����
		TXTDATA->init();				//�ؽ�Ʈ����Ÿ ����
		SCENEMANAGER->init();			//���Ŵ��� ����
		EFFECTMANAGER->init();			//����Ʈ�Ŵ��� ����
	}

	return S_OK;
}

//==================================================================
//		## ���� - release(void) ## 
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();
		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->releaseSingleton();
		//��Ʈ������Ÿ �̱��� ����
		TXTDATA->releaseSingleton();
		//���Ŵ��� �̱��� ����
		SCENEMANAGER->releaseSingleton();
		//����Ʈ�Ŵ��� �̱��� ����
		EFFECTMANAGER->releaseSingleton();
	}

	//DC����
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## ������Ʈ - update(void) ## 
//==================================================================
void gameNode::update(void)
{
}

//==================================================================
//		## ���� - render(void) ## 
//==================================================================
void gameNode::render(void)
{
}

//==================================================================
//		## �޼��� ���ν��� ## (������ ���ν����� �̰����� ó���Ѵ�)
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

