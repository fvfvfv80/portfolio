#pragma once
#include "singletonBase.h"
#include <bitset>
//==================================================================
//		## keyManager ## (�߰��Ұ� ���� �׳� ������ ����)
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

	//Ű�� �ѹ� ���ȴ��� üũ�Ѵ�
	bool isOnceKeyDown(int key);
	//Ű�� ���ѹ� ���ȴ� ���Ǿ����� üũ�Ѵ�
	bool isOnceKeyUp(int key);
	//Ű�� ��� ������ �ִ��� üũ�Ѵ�
	bool isStayKeyDown(int key);
	//���Ű��? (ĸ����, �ѹ���, ���� on/off)
	bool isToggleKey(int key);

	//����
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//����
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	keyManager();
	~keyManager();
};

