#pragma once
#include "singletonBase.h"
//==================================================================
//		## effectManager ## (이펙트 매니져)
//==================================================================

//이펙트 클래스 전방선언
class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	typedef vector<effect*> arrEffects; //이펙트 클래스를 담을 벡터
	typedef vector<effect*>::iterator iterEffects;
	typedef map<string, arrEffects> arrEffect;	//이펙트 클래스를 담아놓은 벡터를 검사할 맵
	typedef map<string, arrEffects>::iterator iterEffect;
	typedef vector<map<string, arrEffects>> arrTotalEffect;	//모든 이펙트를 관리할 벡터
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffects; //모든 이펙트들 관리

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//이펙트추가(이펙트키값, 이미지이름, 이미지가로크기, 이미지세로크기, 이펙트가로크기, 이펙트세로크기, FPS, 경과시간(이펙트속도), 버퍼갯수)
	void addEffect(string effectName, const char* imageName, int imageWidth, int imageHeight, 
		int effectWidth, int effectHeight, int fps, float elapsed, int buffer);

	//이펙트 플레이(이펙트키값, 이펙트 터트릴 x위치, 이펙트 터트릴 y위치)
	void play(string effectName, int x, int y);

	effectManager();
	~effectManager();
};

