#pragma once
#include "gameNode.h"
//==================================================================
//		## button ## (��ư Ŭ����)
//==================================================================

//�Լ������� Ÿ�� ������
typedef void(*CALLBACK_FUNCTION)(void);

//��ư��,�ٿ� �̳ѹ�
enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction; //��ư����
	const char* _imageName;		//��ư�̹��� �̸�
	image* _image;				//��ư�̹���
	RECT _rc;					//��ư��Ʈ
	float _x, _y;				//��ġ

	POINT _btnDownFramePoint;	//��ư�ٿ� ������ ����Ʈ
	POINT _btnUpFramePoint;		//��ư�� ������ ����Ʈ

	CALLBACK_FUNCTION _callbackFunction; //�ݹ��Լ� ���� ����

public:
	//�ʱ�ȭ(�̹����̸�, ��ġx, ��ġy, ��ư�ٿ� ������ ����Ʈ, ��ư�� ������ ����Ʈ, ��ư�ݹ��Լ�)
	HRESULT init(const char* imageName, int x, int y, 
		POINT btnDownFramePoint, POINT btnUpFramePoint, 
		CALLBACK_FUNCTION cbFunction);
	void release(void);
	void update(void);
	void render(void);

	button();
	~button();
};

