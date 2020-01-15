#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"
sceneManager::sceneManager()
{
}
sceneManager::~sceneManager()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================

/*
//로딩 쓰레드
DWORD CALLBACK loadingScene(LPVOID prc)
{
	//교체 될 init 함수 실행한다
	sceneManager::_readyScene->init();

	//현재씬을 교체될 씬으로 바꾼다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩씬 해제한다
	sceneManager::_loadScene->release();
	sceneManager::_loadScene = NULL;
	sceneManager::_readyScene = NULL;

	return NULL;
}
*/

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

//씬매니져 초기화
HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

//씬매니져 해제
void sceneManager::release(void)
{
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mSceneList.clear();
}

//씬매니져 업데이트
void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

//씬매니져 렌더
void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//씬 추가
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

/*
//로딩씬 추가
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}
*/

//씬 체인지
HRESULT sceneManager::changeScene(string sceneName)
{
	//기존에 씬이 있으면 릴리즈
	if (_currentScene) _currentScene->release();

	miSceneList find = _mSceneList.find(sceneName);

	//못찾았음
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려 하는 씬과 현재씬이 같으면 리턴
	if (find->second == _currentScene) return E_FAIL;

	//찾으면 변경될 씬을 초기화한다
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

/*
HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았음
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려 하는 씬과 현재씬이 같으면 리턴
	if (find->second == _currentScene) return E_FAIL;

	//로딩씬 찾는다
	miSceneList findLoading = _mLoadingSceneList.find(loadingSceneName);

	//로딩씬 찾아서 없으면 바로 교체할 씬
	if (findLoading == _mLoadingSceneList.end()) return changeScene(loadingSceneName);
	
	//찾으면 변경될 씬을 초기화한다
	if (SUCCEEDED(find->second->init()))
	{
		//기존에 씬이 있으면 릴리즈
		if (_currentScene) _currentScene->release();

		//로딩씬
		_currentScene = findLoading->second;
		
		//로딩끝난 후에 변결될 씬을 집어 넣는다
		_readyScene = find->second;

		//쓰뤠드 해제
		CloseHandle(CreateThread(NULL, 0, loadingScene, NULL, 0, &_loadThreadID));
		
		return S_OK;
	}

	return E_FAIL;
}
*/
