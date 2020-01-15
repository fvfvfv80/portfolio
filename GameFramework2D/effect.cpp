#include "stdafx.h"
#include "effect.h"
#include "animation.h"
//����̴ϼȶ������ �ʱ�ȭ
effect::effect() : _effectImage(NULL), _effectAnimation(NULL), _isRunning(false), _x(0), _y(0)
{
}
effect::~effect()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//���࿡ �̹����� ������ ����
	if (!effectImage) return E_FAIL;

	//Ȱ��ȭ ���� �ʱ�ȭ
	_isRunning = false;

	//����Ʈ �̹��� ��������
	_effectImage = effectImage;

	//����Ʈ ����ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ ��������
	if (!_effectAnimation) _effectAnimation = new animation;

	//�ִϸ��̼� ���� ����
	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void effect::release(void)
{
	//����Ʈ �ִϸ��̼� ����
	SAFE_DELETE(_effectAnimation);
}

void effect::update(void)
{
	//Ȱ��ȭ ���� ������ ����������� �ʴ´�
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(_elapsedTime);

	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� Kill���ش�
	if (!_effectAnimation->isPlay())killEffect();
}

void effect::render(void)
{
	//������ �ȵǸ� �׷��ָ� �ȵ�
	if (!_isRunning) return;

	//����Ʈ �ִϸ��̼� ����(hdc, x��ġ, y��ġ, �ִϸ��̼�)
	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

//����Ʈ ��Ʈ�� ��ǥ
void effect::startEffect(int x, int y)
{
	//������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������� �ʴ´�.
	if (!_effectImage || !_effectAnimation) return;

	//�߾���ǥ�� �̵�������
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

//����Ʈ ��Ȱ��ȭ
void effect::killEffect(void)
{
	_isRunning = false;
}
