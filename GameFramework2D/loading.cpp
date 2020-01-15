#include "stdafx.h"
#include "loading.h"

//==================================================================
//		## loadItem ## (로드아이템 클래스)
//==================================================================
loadItem::loadItem(void)
{
}

loadItem::~loadItem(void)
{
}

//이미지 로드 아이템
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
//		## loading ## (로딩 클래스)
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

	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "image\\wall.bmp", WINSIZEX, WINSIZEY);

	//로딩바 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront.bmp", "loadingBarBack.bmp", WINSIZEX/2-300, WINSIZEY/2+200, 600, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;
}

//로드이미지(키값, 가로크기, 세로크기)
void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

//로드이미지(키값, 파일이름, 가로크기, 세로크기, true, RGB(255, 0, 255))
void loading::loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

//로드이미지(키값, 파일이름, 위치좌표x, 위치좌표y, 가로크기, 세로크기, true, RGB(255, 0, 255))
void loading::loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

//로드프레임이미지(키값, 파일이름, 가로크기, 세로크기, 프레임x, 프레임y, true, RGB(255, 0, 255))
void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

//로드프레임이미지(키값, 파일이름, 위치좌표x, 위치좌표y, 가로크기, 세로크기, 프레임x, 프레임y, true, RGB(255, 0, 255))
void loading::loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::release(void)
{
	//로딩바 해제
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//로딩바 업데이트
	_loadingBar->update();
}

void loading::render(void)
{
	//백그라운드 이미지 렌더
	_background->render(getMemDC());
	//로딩바 렌더
	_loadingBar->render();
}

BOOL loading::loadNext(void)
{
	//아이템 갯수가 벡터 사이즈 이상 넘어가면 펄쓰~~~
	if (_currentGauge >= _vLoadItem.size())
	{
		return false;
	}

	//여기오면 로딩중~~
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

		//사운드는 나중에
		case LOADING_KIND_SOUND_00:
			break;
	}

	//로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	//카운트
	_currentGauge++;

	return true;
}



