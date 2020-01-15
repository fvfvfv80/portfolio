#pragma once
#include "gameNode.h"

//�Ѿ˱���ü
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

//�������� ���� �̽� + ������ �ִϸ��̼� (�򶧸��� ����� ����)
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

//�������� ���� �Ѿ� (�򶧸��� ����� ����)
class bullet : public gameNode
{
private:
	//�Ѿ˱���ü�� ���� ���Ϳ� �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName; //�Ѿ��̹��� �̸�
	float _range; //�Ѿ� ��Ÿ�
	int _bulletMax; //�Ѿ˰���

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//ǡ�̾�~~
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˿�������
	void move(void);
	//�Ѿ˱׷���
	void draw(void);

	//�Ѿ� �����ض�
	void removeBullet(int arrNum);

	//�Ѿ� ���� ��������
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	//�Ѿ� ���� �ݺ��� ��������
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	bullet(void);
	~bullet(void);
};

//�̸� �غ�(����)�صΰ� �߻��ϴ� �̻���
class missile : public gameNode
{
private:
	//�Ѿ˱���ü�� ���� ���Ϳ� �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //��Ÿ�

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//ǡ�̾�~~
	void fire(float x, float y);
	//�Ѿ˿�������
	void move(void);

	missile(void);
	~missile(void);
};

//�򶧸��� �����ϴ� �̻���
class missileM1 : public gameNode
{
private:
	//�Ѿ˱���ü�� ���� ���Ϳ� �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //��Ÿ�
	float _bulletMax; //�Ѿ˰���

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//ǡ�̾�~~
	void fire(float x, float y);
	//�Ѿ˿�������
	void move(void);

	//�Ѿ� �����ض�
	void removeMissile(int arrNum);

	//�Ѿ˺��͸� ��������(����)
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missileM1(void);
	~missileM1(void);
};