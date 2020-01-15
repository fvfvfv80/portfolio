#include "stdafx.h"
#include "loading.h"

//==================================================================
//		## loadItem ## (�ε������ Ŭ����)
//==================================================================
loadItem::loadItem(void)
{
}

loadItem::~loadItem(void)
{
}

//�̹��� �ε� ������
HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOADING_KIND_IMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_02;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_FRAMEIMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_FRAMEIMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//==================================================================
//		## loading ## (�ε� Ŭ����)
//==================================================================
loading::loading(void)
{
}
loading::~loading(void)
{
}

HRESULT loading::init(void)
{
	gameNode::init();

	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "image\\wall.bmp", WINSIZEX, WINSIZEY);

	//�ε��� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront.bmp", "loadingBarBack.bmp", WINSIZEX/2-300, WINSIZEY/2+200, 600, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;
}

//�ε��̹���(Ű��, ����ũ��, ����ũ��)
void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

//�ε��̹���(Ű��, �����̸�, ����ũ��, ����ũ��, true, RGB(255, 0, 255))
void loading::loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

//�ε��̹���(Ű��, �����̸�, ��ġ��ǥx, ��ġ��ǥy, ����ũ��, ����ũ��, true, RGB(255, 0, 255))
void loading::loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

//�ε��������̹���(Ű��, �����̸�, ����ũ��, ����ũ��, ������x, ������y, true, RGB(255, 0, 255))
void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

//�ε��������̹���(Ű��, �����̸�, ��ġ��ǥx, ��ġ��ǥy, ����ũ��, ����ũ��, ������x, ������y, true, RGB(255, 0, 255))
void loading::loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::release(void)
{
	//�ε��� ����
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//�ε��� ������Ʈ
	_loadingBar->update();
}

void loading::render(void)
{
	//��׶��� �̹��� ����
	_background->render(getMemDC());
	//�ε��� ����
	_loadingBar->render();
}

BOOL loading::loadNext(void)
{
	//������ ������ ���� ������ �̻� �Ѿ�� �޾�~~~
	if (_currentGauge >= _vLoadItem.size())
	{
		return false;
	}

	//������� �ε���~~
	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadingKind())
	{
		case LOADING_KIND_IMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.width, imageResource.height);
		}
		break;

		case LOADING_KIND_IMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height, 
				imageResource.trans, imageResource.transColor);
		}
		break;

		case LOADING_KIND_IMAGE_02:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				imageResource.x, imageResource.y,
				imageResource.width, imageResource.height, 
				imageResource.trans, imageResource.transColor);
		}
		break;

		case LOADING_KIND_FRAMEIMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans, imageResource.transColor);
		}
		break;

		case LOADING_KIND_FRAMEIMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				imageResource.x, imageResource.y,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans, imageResource.transColor);
		}
		break;

		//����� ���߿�
		case LOADING_KIND_SOUND_00:
			break;
	}

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	//ī��Ʈ
	_currentGauge++;

	return true;
}



