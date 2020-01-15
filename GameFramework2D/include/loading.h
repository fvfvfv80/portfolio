#pragma once
#include "gameNode.h"
#include "progressBar.h"

//==================================================================
//		## loadItem ## (로드아이템 클래스)
//==================================================================

//로딩아이템 종류
enum LOADING_KIND
{
	LOADING_KIND_IMAGE_00,
	LOADING_KIND_IMAGE_01,
	LOADING_KIND_IMAGE_02,
	LOADING_KIND_FRAMEIMAGE_00,
	LOADING_KIND_FRAMEIMAGE_01,
	LOADING_KIND_SOUND_00,
	LOADING_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			//키이름
	const char* fileName;	//파일이름
	int x, y;				//위치좌표
	int width, height;		//가로세로크기
	int frameX, frameY;		//프레임
	bool trans;				//투명화 할꺼냐?
	COLORREF transColor;	//투명컬러키
};

//클래스 로드아이템
class loadItem
{
private:
	LOADING_KIND _kind;					//로딩아이템 종류
	tagImageResource _imageResource;	//이미지 리소스 구조체

public:
	//이미지 로드 아이템
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	void release(void);

	//로딩아이템 종류 가져오기
	LOADING_KIND getLoadingKind(void) { return _kind; }
	//이미지 리소스 가져오기
	tagImageResource getImageResource(void) { return _imageResource; }

	loadItem(void);
	~loadItem(void);
};

//==================================================================
//		## loading ## (로딩 클래스)
//==================================================================
class loading : public gameNode
{
private:
	//로드아이템 클래스를 담을 벡터 선언
	typedef vector<loadItem*> arrLoadItem;
	//로드아이템 클래스를 담을 반복자 선언
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;		//로드아이템 벡터

	image* _background;			//로딩화면에서 사용할 백그라운드 이미지
	progressBar* _loadingBar;	//로딩화면에서 사용할 로딩바

	int _currentGauge;			//로딩바 게이지증가용 변수

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	/*이놈이 젤 중요함*/
	//이미지 추가할때 처럼 로딩할때 전부 추가해주면 된다
	//이미지 사용은 키값만 알고 있으면 이미지를 화면에 뿌릴 수 있다
	
	//로드이미지(키값, 가로크기, 세로크기)
	void loadImage(string keyName, int width, int height);
	//로드이미지(키값, 파일이름, 가로크기, 세로크기, true, RGB(255, 0, 255))
	void loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	//로드이미지(키값, 파일이름, 위치좌표x, 위치좌표y, 가로크기, 세로크기, true, RGB(255, 0, 255))
	void loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	//로드프레임이미지(키값, 파일이름, 가로크기, 세로크기, 프레임x, 프레임y, true, RGB(255, 0, 255))
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	//로드프레임이미지(키값, 파일이름, 위치좌표x, 위치좌표y, 가로크기, 세로크기, 프레임x, 프레임y, true, RGB(255, 0, 255))
	void loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	BOOL loadNext(void);

	//로드아이템 벡터 가져오기
	vector<loadItem*> getLoadItem(void) { return _vLoadItem; }

	loading(void);
	~loading(void);
};
