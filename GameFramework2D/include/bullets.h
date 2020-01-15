#pragma once
#include "gameNode.h"

//총알구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	int radius;
	float speed;
	float x;
	float y;
	float fireX, fireY;
	float angle;
	bool fire;
	int count;
};

//공용으로 쓰는 미슬 + 프레임 애니메이션 (쏠때마다 만들고 삭제)
class missilePF1 : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void move(void);
	void draw(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missilePF1(void);
	~missilePF1(void);
};

//공용으로 쓰는 총알 (쏠때마다 만들고 삭제)
class bullet : public gameNode
{
private:
	//총알구조체를 담을 벡터와 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName; //총알이미지 이름
	float _range; //총알 사거리
	int _bulletMax; //총알갯수

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//퐈이아~~
	void fire(float x, float y, float angle, float speed);
	//총알움직여라
	void move(void);
	//총알그려라
	void draw(void);

	//총알 삭제해라
	void removeBullet(int arrNum);

	//총알 벡터 가져오기
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	//총알 벡터 반복자 가져오기
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	bullet(void);
	~bullet(void);
};

//미리 준비(장전)해두고 발사하는 미사일
class missile : public gameNode
{
private:
	//총알구조체를 담을 벡터와 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //사거리

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//퐈이아~~
	void fire(float x, float y);
	//총알움직여라
	void move(void);

	missile(void);
	~missile(void);
};

//쏠때마다 생성하는 미사일
class missileM1 : public gameNode
{
private:
	//총알구조체를 담을 벡터와 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //사거리
	float _bulletMax; //총알갯수

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//퐈이아~~
	void fire(float x, float y);
	//총알움직여라
	void move(void);

	//총알 삭제해라
	void removeMissile(int arrNum);

	//총알벡터를 가져오자(겟터)
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missileM1(void);
	~missileM1(void);
};