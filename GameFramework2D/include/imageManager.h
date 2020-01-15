#pragma once
#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## imageManager ## (이미지 매니져)
//==================================================================

class imageManager : public singletonBase <imageManager>
{
public:
	typedef map<string, image*> mapImageList;				//이미지 리스트 맵
	typedef map<string, image*>::iterator mapImageIter;		//이미지 리스트 이터레이터 (반복자)

private:
	mapImageList _mImageList; //맵으로 구현된 이미지 리스트		

public:
	HRESULT	init(void);
	void release(void);

	//추가 
	//키값 설정하여 추가
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, int x, int y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(int width, int height, const char* fileName, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//키값 + 프레임 설정하여 추가
	image* addFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//이미지 찾기
	image* findImage(string strKey);

	//삭제
	BOOL deleteImage(string strKey);

	//전체 삭제
	BOOL deleteAll(void);

	//일반 렌더
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//프레임 렌더
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY);

	//알파 렌더
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 알파렌더
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha);
	
	//루프 렌더 함수
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	
	imageManager(void);
	~imageManager(void);

private:
	//이미지 경로 이름을 파일이름으로 검색
	BOOL getFileName(string& fileName);
};
