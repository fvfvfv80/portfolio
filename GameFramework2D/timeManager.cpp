#include "stdafx.h"
#include "timeManager.h"
timeManager::timeManager()
{
}
timeManager::~timeManager()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

//Ÿ�̸� �ʱ�ȭ
HRESULT timeManager::init(void)
{
	//Ÿ�̸� Ŭ���� ������ �ʱ�ȭ
	_timer = new timer;
	_timer->init();

	return S_OK;
}

//Ÿ�̸� ����
void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

//Ÿ�̸� ������Ʈ (Ÿ�̸� ������ ����)
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//Ÿ�̸� HDC�� ���� ǥ���ϱ�
void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//���� ����� (TRANSPARENT: ����, QPAQUEL: ������)
	SetBkMode(hdc, TRANSPARENT);
	//���� ����
	SetTextColor(hdc, RGB(255, 0, 255));

//#ifdef _DEBUG
//	if(_timer != NULL)
//	{
//		//������ ��´�
//		sprintf(str, "FPS : %d", _timer->getFrameRate());
//		TextOut(hdc, 0, 0, str, strlen(str));
//		//����Ÿ�� ��´�(��ü����ð�)
//		sprintf(str, "worldTime : %f", _timer->getWorldTime());
//		TextOut(hdc, 0, 20, str, strlen(str));
//		//���� tick ��´�
//		sprintf(str, "elpasedTime : %f", _timer->getElapsedTime());
//		TextOut(hdc, 0, 40, str, strlen(str));
//	}
//#else
//	if (time != NULL)
//	{
//		//������ ��´�
//		sprintf(str, "framePerSec : %d", _timer->getFrameRate());
//		TextOut(hdc, 0, 0, str, strlen(str));
//	}
//#endif
}
