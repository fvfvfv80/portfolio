#pragma once
#include "singletonBase.h"
//==================================================================
//		## effectManager ## (����Ʈ �Ŵ���)
//==================================================================

//����Ʈ Ŭ���� ���漱��
class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	typedef vector<effect*> arrEffects; //����Ʈ Ŭ������ ���� ����
	typedef vector<effect*>::iterator iterEffects;
	typedef map<string, arrEffects> arrEffect;	//����Ʈ Ŭ������ ��Ƴ��� ���͸� �˻��� ��
	typedef map<string, arrEffects>::iterator iterEffect;
	typedef vector<map<string, arrEffects>> arrTotalEffect;	//��� ����Ʈ�� ������ ����
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffects; //��� ����Ʈ�� ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//����Ʈ�߰�(����ƮŰ��, �̹����̸�, �̹�������ũ��, �̹�������ũ��, ����Ʈ����ũ��, ����Ʈ����ũ��, FPS, ����ð�(����Ʈ�ӵ�), ���۰���)
	void addEffect(string effectName, const char* imageName, int imageWidth, int imageHeight, 
		int effectWidth, int effectHeight, int fps, float elapsed, int buffer);

	//����Ʈ �÷���(����ƮŰ��, ����Ʈ ��Ʈ�� x��ġ, ����Ʈ ��Ʈ�� y��ġ)
	void play(string effectName, int x, int y);

	effectManager();
	~effectManager();
};

