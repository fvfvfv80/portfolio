#pragma once
#include "gameNode.h"
//==================================================================
//		## progressBar ## (프로그래스바)
//==================================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//프로그래스바 렉트
	int _x, _y;					//프로그래스바 위치좌표
	float _width;				//프로그래스바 가로길이

	image* _progressBarFront;	//프로그래스바 앞 이미지
	image* _progressBarBack;	//프로그래스바 백(뒷배경) 이미지

public:
	//프로그래스바 초기화(프로그래스바 앞이미지, 프로그래스바 백이미지, x위치, y위치, 가로길이, 세로길이)
	HRESULT init(char* frontImageName, char* backImageName, float x, float y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//프로그래스바의 게이지 세팅하기 
	void setGauge(float currentGauge, float maxGauge);

	//프로그래스바 X위치세팅
	void setX(int x) { _x = x; }
	//프로그래스바 Y위치세팅
	void setY(int y) { _y = y; }
	//프로그래스바 렉트 얻기
	RECT getRect(void) { return _rcProgress; }

	progressBar(void);
	~progressBar(void);
};

