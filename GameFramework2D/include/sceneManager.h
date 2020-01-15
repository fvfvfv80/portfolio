#pragma once
#include "singletonBase.h"
//==================================================================
//		## sceneManager ##
//==================================================================

//게임노드 클래스 전방선언
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene; //현재씬
	static gameNode* _loadScene;	//로딩씬
	static gameNode* _readyScene;	//교체 대기 중인 씬

	mSceneList _mSceneList;
	//mSceneList _mLoadingSceneList;

	//DWORD _loadThreadID;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);

	//로딩씬 추가
	//gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 체인지
	HRESULT changeScene(string sceneName);
	//HRESULT changeScene(string sceneName, string loadingSceneName);

	//friend DWORD CALLBACK loadingScene(LPVOID prc);

	sceneManager();
	~sceneManager();
};

