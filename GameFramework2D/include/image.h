#pragma once
#include "animation.h" //애니메이션 클래스 추가
//==================================================================
//		## image ## (이미지 클래스)
//==================================================================

class image
{
public:

	//이미지 로딩 스타일
	enum IMAGE_LOADKIND
	{
		LOAD_RESOURCE = 0,	//리소스로 로딩
		LOAD_FILE,			//파일로부터 로딩
		LOAD_EMPTY,			//그냥 생성
		LOAD_END
	};

	//이미지 정보 구조체
	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP	hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;	//현재 프레임 X
		int		currentFrameY;	//현재 프레임 Y
		int		maxFrameX;		//최대 프레임 X
		int		maxFrameY;		//최대 프레임 Y
		int		frameWidth;		//프레임 가로크기
		int		frameHeight;	//프레임 세로크기
		BYTE	loadType;
		RECT	boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 경로명

	BOOL			_tran;			//투명 배경있나 없나?
	COLORREF		_transColor;	//투명 컬러키

	BLENDFUNCTION	_blendFunc;		//알파 블렌드를 위한 정보
	LPIMAGE_INFO	_blendImage;	//알파 블렌드를 사용하기 위한 이미지 정보

public:
	image(void);
	~image(void);

	//빈 비트맵 만들기

	//초기화 함수
	//아무것도 없는 빈 비트맵 생성
	HRESULT init(int width, int height);

	//리소스로 부터 읽어오기
	HRESULT init(const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 파일 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 + 프레임 파일 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//릴리즈 (삭제함수)
	void release(void);

	//투명도 설정
	void setTransColor(BOOL trans, COLORREF transColor);

	//렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
	//프레임 알파렌더
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//애니 렌더
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniRenderAlpha(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//DC얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//좌표 x 세팅
	inline void setX(float x) { _imageInfo->x = x; }
	//좌표 x 얻기
	inline float getX(void) { return _imageInfo->x; }
	//좌표 y 세팅
	inline void setY(float y) { _imageInfo->y = y; }
	//좌표 y 얻기
	inline float getY(void) { return _imageInfo->y; }

	//좌표센터 x, y
	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로길이
	inline int getWidth(void) { return _imageInfo->width; }
	//이미지 세로길이
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩 박스(충돌체크)
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x - (_imageInfo->width / 2)),
			int(_imageInfo->y - (_imageInfo->height / 2)),
			int(_imageInfo->x + (_imageInfo->width / 2)),
			int(_imageInfo->y + (_imageInfo->height / 2)) };
		return rc;
	}
	//프레임바운드 박스(충돌체크)
	inline RECT frameBoundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->x + _imageInfo->frameWidth),
			int(_imageInfo->y + _imageInfo->frameHeight) };
		return rc;
	}

	//프레임 x 세팅하기
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	//프레임 y 세팅하기
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	
	//맥스프레임 x 얻기
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	//맥스프레임 y 얻기
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
	//프레임 x 얻기
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	//프레임 y 얻기
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	//프레임 가로길이 얻기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	//프레임 세로길이 얻기
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
};
