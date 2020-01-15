#pragma once
#include "singletonBase.h"
#include <bitset>
//==================================================================
//		## keyManager ## (추가할것 없음 그냥 가져다 쓸것)
//==================================================================
using namespace std;
#define KEYMAX 256

class keyManager : public singletonBase <keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init(void);
	void release(void);

	//키가 한번 눌렸는지 체크한다
	bool isOnceKeyDown(int key);
	//키가 단한번 눌렸다 업되었는지 체크한다
	bool isOnceKeyUp(int key);
	//키를 계속 누르고 있는지 체크한다
	bool isStayKeyDown(int key);
	//토글키냐? (캡스락, 넘버락, 사운드 on/off)
	bool isToggleKey(int key);

	//겟터
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//셋터
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	keyManager();
	~keyManager();
};

