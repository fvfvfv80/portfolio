#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager(void)
{
}
imageManager::~imageManager(void)
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================

//셋업
HRESULT	imageManager::init(void)
{
	return S_OK;
}

//릴리즈
void imageManager::release(void)
{
	deleteAll();
}

//키값 설정하여 빈이미지 추가
image* imageManager::addImage(string strKey, int width, int height)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키값 설정하여 리소스ID로 이미지 추가
image* imageManager::addImage(string strKey, const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키값 설정하여 파일로 이미지 추가
image* imageManager::addImage(string strKey, const char* fileName, int x, int y, int width, int height, BOOL trans, COLORREF transColor)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, (float)x, (float)y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img)
		return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키값 설정하여 파일로 이미지 추가
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//파일로 이미지추가 (키값은 파일 이름)
image* imageManager::addImage(int width, int height, const char* fileName, BOOL trans, COLORREF transColor)
{
	//추가하려는 이미지의 키값을 파일 이름으로 변경한다.
	string strFileName = fileName;
	if (!getFileName(strFileName))
	{
		//이름 추출이 실패 하면 NULL 리턴
		return NULL;
	}

	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strFileName);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strFileName, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//추가 하려는 키 값의 이미지가 존재하는 지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 존재한다면 추가하지 않고 리턴 한다.
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지 셋팅 하고 이미지가 제대로 셋팅이 되지 않았다면 NULL 리턴
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img)
			return NULL;
	}

	//생성된 이미지 Map 리스트에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//이미지 찾기
image* imageManager::findImage(string strKey)
{
	//해당 키를 검색
	mapImageIter key = _mImageList.find(strKey);

	//해당 키값을 찾았다면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당 키를 검색
	mapImageIter key = _mImageList.find(strKey);

	//해당 키값을 찾았다면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();

		//메모리해제
		SAFE_DELETE(key->second);

		//맵리스트에서 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//전체 삭제
BOOL imageManager::deleteAll(void)
{
	//맵 전체를 돌면서 지운다.
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//지워지면 반복자를 증가하지 않는다.
		if (iter->second != NULL)
		{
			iter->second->release();
			delete iter->second;
			iter = _mImageList.erase(iter);
		}
		else
		{
			//반복자 증가
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

//이미지 경로 이름을 파일이름으로 검색
BOOL imageManager::getFileName(string& strFile)
{
	if (strFile.empty()) return FALSE;

	//String 포지션 위치 값
	size_t pos;

	// 경로 짜르기
	//뒤에서 부터 '/' 문자만나는 지점 찾아 pos 에 대입
	pos = strFile.find_first_of("/");

	//찾았다면..
	if (pos != string::npos)
	{
		//짤라 낸다
		strFile = strFile.substr(pos + 1, strFile.length());
	}
	else //못 찾았다면... '\' 로 찾는다
	{
		//다시 찾는다/
		pos = strFile.find_last_of("\\");

		if (pos != string::npos)
		{
			//짤라 낸다
			strFile = strFile.substr(pos + 1, strFile.length());
		}
	}

	// 확장자 짜르기
	pos = strFile.find(".");

	if (pos != string::npos) strFile = strFile.substr(0, pos);
	else return FALSE;

	return TRUE;
}

//렌더 (렌더할 이미지의 키 값 필요)
//일반 렌더
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//프레임렌더
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, frameX, frameY);
}

//알파 렌더
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	image* img = findImage(strKey);
	
	if (img) img->frameAlphaRender(hdc, destX, destY, frameX, frameY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}