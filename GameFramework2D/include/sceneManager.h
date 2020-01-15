#pragma once
#include "singletonBase.h"
//==================================================================
//		## sceneManager ##
//==================================================================

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene; //�����
	static gameNode* _loadScene;	//�ε���
	static gameNode* _readyScene;	//��ü ��� ���� ��

	mSceneList _mSceneList;
	//mSceneList _mLoadingSceneList;

	//DWORD _loadThreadID;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�ε��� �߰�
	//gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ü����
	HRESULT changeScene(string sceneName);
	//HRESULT changeScene(string sceneName, string loadingSceneName);

	//friend DWORD CALLBACK loadingScene(LPVOID prc);

	sceneManager();
	~sceneManager();
};

