#include "stdafx.h"
#include "enemy.h"
enemy::enemy()
{
}
enemy::~enemy()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	//������ �ʱ�ȭ
	_currentFrameX = _currentFrameY = 0;
	_count = 0;
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 1000);

	//�̹����� �̹����� ��Ʈ �ʱ�ȭ
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	_count++;
	if (_count % 2 == 0)
	{
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX > _image->getFrameX()) _currentFrameX = 0;
	}
}

void enemy::render(void)
{
	draw();
}

void enemy::move(void)
{
}

void enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool enemy::bulletCountFire(void)
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount++;
		_rndFireCount = RND->getFromIntTo(1, 1000);
		return true;
	}

	return false;
}


