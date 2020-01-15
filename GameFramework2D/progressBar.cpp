#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}
progressBar::~progressBar()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================


//프로그래스바 초기화(프로그래스바 앞 이미지, 프로그래스바 백 이미지, x위치, y위치, 가로길이, 세로길이)
HRESULT progressBar::init(char* frontImageName, char* backImageName, float x, float y, int width, int height)
{
	//프로그래스바 위치좌표 초기화
	_x = x;
	_y = y;

	//프로그래스바 렉트위치, 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//프로그래스바 앞 이미지 초기화
	_progressBarFront = new image;
	_progressBarFront->init(frontImageName, x, y, width, height, true, RGB(255, 0, 255));

	//프로그래스바 백 이미지 초기화
	_progressBarBack = new image;
	_progressBarBack->init(backImageName, x, y, width, height, true, RGB(255, 0, 255));

	//가로길이 초기화
	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release(void)
{
	//프로그래스바 앞, 뒤 이미지 해제
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(),
		_progressBarBack->getHeight());
}

void progressBar::render(void)
{
	//프로그래스바 백 이미지 렌더(변경되는게 없다)
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	//프로그래스바 앞 이미지 렌더(가로길이가 변경되야 한다)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

//프로그래스바의 게이지 세팅하기 
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}