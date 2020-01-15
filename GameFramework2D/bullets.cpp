#include "stdafx.h"
#include "bullets.h"

//===================================================================
//공용으로 쓰는 미슬 + 프레임 애니메이션 (쏠때마다 만들고 삭제)
//===================================================================
missilePF1::missilePF1(void)
{
}
missilePF1::~missilePF1(void)
{
}

HRESULT missilePF1::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void missilePF1::release(void)
{
	_vBullet.clear();
}

void missilePF1::update(void)
{
	move();
}

void missilePF1::render(void)
{
	draw();
}

void missilePF1::draw(void)
{
	int frame;
	float angle;

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		angle = _viBullet->angle + PI_16;
		if (angle >= PI * 2) angle -= 2 * PI;

		frame = int(angle / PI_8);

		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, frame, 0);
	}
}

void missilePF1::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());
	_vBullet.push_back(bullet);
}

void missilePF1::move(void)
{
	float elpasedTime = TIMEMANAGER->getElapsedTime();

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed * elpasedTime;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed * elpasedTime;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getFrameWidth(), _viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void missilePF1::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/////////////////////////////////////////////////////////////////////
//공용으로 쓰는 총알 (쏠때마다 만들고 삭제)
/////////////////////////////////////////////////////////////////////
bullet::bullet(void)
{
}
bullet::~bullet(void)
{
}

HRESULT bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void bullet::release(void)
{
	_vBullet.clear();
}

void bullet::update(void)
{
	//총알 움직여라
	move();
}

void bullet::render(void)
{
	draw();
}

//퐈이아~~
void bullet::fire(float x, float y, float angle, float speed)
{
	//최대 발사 갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->getWidth(), bullet.bulletImage->getHeight());
	
	//총알을 벡터에 담아라
	_vBullet.push_back(bullet);
}

//총알움직여라
void bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//사거리 밖으로 나갔다!!
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

//총알그려라
void bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

//총알 삭제해라
void bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/////////////////////////////////////////////////////////////////////
//미리장전해두고 쏘는 미사일
/////////////////////////////////////////////////////////////////////
missile::missile()
{
}
missile::~missile()
{
}

HRESULT missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile.bmp", 0, 0, 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		
		//총알을 벡터에 담아라
		_vBullet.push_back(bullet);
	}

	
	return S_OK;
}

void missile::release(void)
{
}

void missile::update(void)
{
	//총알 움직여라
	move();
}

void missile::render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}
	
//퐈이어~~
void missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

//총알아 움직여라~
void missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

/////////////////////////////////////////////////////////////////////
//쏠때마다 생성하는 미사일
/////////////////////////////////////////////////////////////////////
missileM1::missileM1()
{
}
missileM1::~missileM1()
{
}

HRESULT missileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void missileM1::release(void)
{
}

void missileM1::update(void)
{
	//총알 움직여라
	move();
}

void missileM1::render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left,
			_viBullet->rc.top, _viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

//퐈이어~~
void missileM1::fire(float x, float y)
{
	//최대발사갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 0, 0, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 10.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	//총알을 벡터에 담아라
	_vBullet.push_back(bullet);
}

//총알아 움직여라~
void missileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

//총알 삭제해라
void missileM1::removeMissile(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}


