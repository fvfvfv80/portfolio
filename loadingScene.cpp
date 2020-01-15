#include "stdafx.h"
#include "loadingScene.h"
loadingScene::loadingScene()
{
}
loadingScene::~loadingScene()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 로딩하자
	this->loadingImage();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();
	
	/*중요함*/
	//로딩끝난후 화면전환
	if (!_loading->loadNext())
	{
		SCENEMANAGER->changeScene("world");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//==================================================================
//		## 모든 이미지를 이곳에서 추가한다 ## 
//==================================================================
void loadingScene::loadingImage(void)
{
	
	//추가하는 방법은 로딩클래스 헤더를 참조하면 된다
	//이미지매니져에서 추가하는 방법과 동일하다
	//_loading->loadImage()
	//_loading->loadFrameImage()

		
	/*IMAGEMANAGER->addImage("black", "image\\black.bmp", 1200, 600,false,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("aliceStand", "image\\aliceStand.bmp", 195, 194,3,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceJump", "image\\aliceJump.bmp", 350, 260, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceWalk", "image\\aliceWalk.bmp", 252, 196, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("aliceWalk", "image\\aliceWalk.bmp", 252, 196, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RM", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BM", "image\\blueMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GM", "image\\greenMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GM", "image\\purpleMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BGM", "image\\BGMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BBG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BBS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BKG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BKS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GLG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GLS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GPG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GPS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RKG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RKS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RQG", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RQS", "image\\redMirror.bmp", 50, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackGround", "image\\BackGround.bmp", 1500, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor", "image\\floor.bmp", 1200, 100, false, RGB(255, 0, 255));*/



	//350//260
	IMAGEMANAGER->addImage("test", "image\\test.bmp", 58, 97, true, RGB(255, 0, 255));
	for (int i = 0; i < 500; i++)
	{
		//IMAGEMANAGER->addImage("background", "background.bmp", 800, 600, true, RGB(255, 0, 255));
	}
}
