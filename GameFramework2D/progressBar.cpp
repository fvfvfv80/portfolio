#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}
progressBar::~progressBar()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================


//���α׷����� �ʱ�ȭ(���α׷����� �� �̹���, ���α׷����� �� �̹���, x��ġ, y��ġ, ���α���, ���α���)
HRESULT progressBar::init(char* frontImageName, char* backImageName, float x, float y, int width, int height)
{
	//���α׷����� ��ġ��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	//���α׷����� ��Ʈ��ġ, ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);

	//���α׷����� �� �̹��� �ʱ�ȭ
	_progressBarFront = new image;
	_progressBarFront->init(frontImageName, x, y, width, height, true, RGB(255, 0, 255));

	//���α׷����� �� �̹��� �ʱ�ȭ
	_progressBarBack = new image;
	_progressBarBack->init(backImageName, x, y, width, height, true, RGB(255, 0, 255));

	//���α��� �ʱ�ȭ
	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release(void)
{
	//���α׷����� ��, �� �̹��� ����
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
	//���α׷����� �� �̹��� ����(����Ǵ°� ����)
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	//���α׷����� �� �̹��� ����(���α��̰� ����Ǿ� �Ѵ�)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

//���α׷������� ������ �����ϱ� 
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}