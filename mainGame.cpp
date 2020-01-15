#include "stdafx.h"
#include "mainGame.h"

//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
/////////////////////////////////////////////////////////////////////

//==================================================================
//		## 초기화 - init(void) ## 
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	//이곳에 초기화 부분을 집어 넣어라
	SCENEMANAGER->addScene("world", new world);

	SCENEMANAGER->addScene("intro", new intro);

	SCENEMANAGER->addScene("P_Engin", new P_Engin);
	
	SCENEMANAGER->addScene("robot", new cRobotGame);
	//로딩씬 추가
	//SCENEMANAGER->addScene("loadingScene", new loadingScene);
	//현재씬 설정
	//로딩씬을 현재씬으로 설정하면 로딩씬에서 다음씬을 추가할것
	SCENEMANAGER->changeScene("intro");
	
	



	

	

	

	return S_OK;
}

//==================================================================
//		## 해제 - release(void) ## 
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
	//초기화부분에서 동적할당 했으면 여기서 지우고 나가라
	
}

//==================================================================
//		## 업데이트 - update(void) ## 
//==================================================================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에 움직여야 하는 부분을 넣어라 (키보드, 마우스,)

	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//==================================================================
//		## 렌더 - render(void) ## 
//==================================================================
void mainGame::render(void)
{
	//흰색 빈맵 이미지(렌더에 그냥 놔둘것)
	PatBlt(getMemDC(), 0, 0, 1400, 1000, WHITENESS);

	//씬매니져 렌더
	SCENEMANAGER->render();

	//타임매니져 렌더
	TIMEMANAGER->render(getMemDC());

	//백버퍼 내용을 hdc에 그린다 (렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(getHDC());
}