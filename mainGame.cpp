#include "stdafx.h"
#include "mainGame.h"

//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
/////////////////////////////////////////////////////////////////////

//==================================================================
//		## �ʱ�ȭ - init(void) ## 
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	//�̰��� �ʱ�ȭ �κ��� ���� �־��
	SCENEMANAGER->addScene("world", new world);

	SCENEMANAGER->addScene("intro", new intro);

	SCENEMANAGER->addScene("P_Engin", new P_Engin);
	
	SCENEMANAGER->addScene("robot", new cRobotGame);
	//�ε��� �߰�
	//SCENEMANAGER->addScene("loadingScene", new loadingScene);
	//����� ����
	//�ε����� ��������� �����ϸ� �ε������� �������� �߰��Ұ�
	SCENEMANAGER->changeScene("intro");
	
	



	

	

	

	return S_OK;
}

//==================================================================
//		## ���� - release(void) ## 
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
	//�ʱ�ȭ�κп��� �����Ҵ� ������ ���⼭ ����� ������
	
}

//==================================================================
//		## ������Ʈ - update(void) ## 
//==================================================================
void mainGame::update(void)
{
	gameNode::update();
	//�̰��� �������� �ϴ� �κ��� �־�� (Ű����, ���콺,)

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

//==================================================================
//		## ���� - render(void) ## 
//==================================================================
void mainGame::render(void)
{
	//��� ��� �̹���(������ �׳� ���Ѱ�)
	PatBlt(getMemDC(), 0, 0, 1400, 1000, WHITENESS);

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());

	//����� ������ hdc�� �׸��� (������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(getHDC());
}