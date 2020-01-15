#include "stdafx.h"
#include "keyManager.h"
keyManager::keyManager()
{
}
keyManager::~keyManager()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ## 
//==================================================================

//키매니져 초기화
HRESULT keyManager::init(void)
{
	//키값을 전부 눌려있지 않은 상태로 초기화 한다
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}

	return S_OK;
}

void keyManager::release(void)
{
}

//키가 한번 눌렸는지 체크한다
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}

	return false;
}

//키가 단한번 눌렸다 업되었는지 체크한다
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

//키를 계속 누르고 있는지 체크한다
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}

	return false;
}

//토글키냐? (캡스락, 넘버락..)
bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}

	return false;
}
