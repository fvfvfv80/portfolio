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
	TextOut(getMemDC(), WINSIZEX/2-15, 100+0 * 100, "엘리스", sizeof("엘리스")-1);
	TextOut(getMemDC(), WINSIZEX/2-15, 100+1 * 100, "포물선", sizeof("포물선") - 1);
	TextOut(getMemDC(), WINSIZEX /2-30, 100+2 * 100, "총알탄로봇", sizeof("총알탄로봇") - 1);
	
	
}


//선택지에 렉트 부여 구조체를 사용해서 그 _title에 걸린것만 나오는걸로 하는것이 효율적일것 같음