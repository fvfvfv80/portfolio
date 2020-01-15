#include "stdafx.h"
#include "intro.h"


intro::intro()
{
}


intro::~intro()
{
}


HRESULT intro:: init(void)
{
	_title = 0;
	return S_OK;
}
void intro::release(void)
{

}
void intro::update(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
		--_title;
	
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		++_title;
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_title%MAXNUM == 0)SCENEMANAGER->changeScene("world");
		else if (_title%MAXNUM == 1)SCENEMANAGER->changeScene("P_Engin");
		else if (_title%MAXNUM == 2)
		{

			MoveWindow(FindWindow("2D Game Framework", NULL), WINSTARTX, WINSTARTY, 1400, 1040, true);
			SCENEMANAGER->changeScene("robot");
		}
	}
	if (_title%MAXNUM == 0)
		_selectBox = RectMakeCenter(WINSIZEX / 2, 100+ 0*100, 500, 100);
	else if (_title%MAXNUM == 1)
		_selectBox = RectMakeCenter(WINSIZEX / 2 , 100 + 1 * 100, 500, 100);
	else if (_title%MAXNUM == 2)
		_selectBox = RectMakeCenter(WINSIZEX / 2, 100 + 2 * 100, 500, 100);

}
void intro::render(void)
{
	Rectangle(getMemDC(), _selectBox.left, _selectBox.top, _selectBox.right, _selectBox.bottom);
	TextOut(getMemDC(), WINSIZEX/2-15, 100+0 * 100, "������", sizeof("������")-1);
	TextOut(getMemDC(), WINSIZEX/2-15, 100+1 * 100, "������", sizeof("������") - 1);
	TextOut(getMemDC(), WINSIZEX /2-30, 100+2 * 100, "�Ѿ�ź�κ�", sizeof("�Ѿ�ź�κ�") - 1);
	
	
}


//�������� ��Ʈ �ο� ����ü�� ����ؼ� �� _title�� �ɸ��͸� �����°ɷ� �ϴ°��� ȿ�����ϰ� ����