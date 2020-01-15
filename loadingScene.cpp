#include "stdafx.h"
#include "loadingScene.h"
loadingScene::loadingScene()
{
}
loadingScene::~loadingScene()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �ε�����
	this->loadingImage();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();
	
	/*�߿���*/
	//�ε������� ȭ����ȯ
	if (!_loading->loadNext())
	{
		SCENEMANAGER->changeScene("world");
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//==================================================================
//		## ��� �̹����� �̰����� �߰��Ѵ� ## 
//==================================================================
void loadingScene::loadingImage(void)
{
	
	//�߰��ϴ� ����� �ε�Ŭ���� ����� �����ϸ� �ȴ�
	//�̹����Ŵ������� �߰��ϴ� ����� �����ϴ�
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
