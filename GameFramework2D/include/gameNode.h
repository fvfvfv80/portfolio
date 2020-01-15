#pragma once
#include "image.h"
//==================================================================
//		## gameNode ## (���ӳ��)
//==================================================================

//����� �̹����� ����ƽ���� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", 1400, 1000);


class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �߳�?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� ��������
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸𸮹���(MemDC) ��������
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//ȭ�����(HDC) ��������
	HDC getHDC() { return _hdc; }

	//�޼��� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wparam, LPARAM lparam);

	gameNode(void);
	virtual ~gameNode(void);
};
