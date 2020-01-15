#pragma once
#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## imageManager ## (�̹��� �Ŵ���)
//==================================================================

class imageManager : public singletonBase <imageManager>
{
public:
	typedef map<string, image*> mapImageList;				//�̹��� ����Ʈ ��
	typedef map<string, image*>::iterator mapImageIter;		//�̹��� ����Ʈ ���ͷ����� (�ݺ���)

private:
	mapImageList _mImageList; //������ ������ �̹��� ����Ʈ		

public:
	HRESULT	init(void);
	void release(void);

	//�߰� 
	//Ű�� �����Ͽ� �߰�
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, int x, int y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(int width, int height, const char* fileName, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//Ű�� + ������ �����Ͽ� �߰�
	image* addFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//�̹��� ã��
	image* findImage(string strKey);

	//����
	BOOL deleteImage(string strKey);

	//��ü ����
	BOOL deleteAll(void);

	//�Ϲ� ����
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//������ ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY);

	//���� ����
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//������ ���ķ���
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha);
	
	//���� ���� �Լ�
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	
	imageManager(void);
	~imageManager(void);

private:
	//�̹��� ��� �̸��� �����̸����� �˻�
	BOOL getFileName(string& fileName);
};
