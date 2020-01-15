#pragma once
#include "gameNode.h"
//==================================================================
//		## effect ## (이펙트 클래스) 
//==================================================================

//애니메이션 클래스 전방선언
class animation;

class effect : public gameNode
{
private:
	image* _effectImage;			//이펙트 이미지
	animation* _effectAnimation;	//이펙트 애니메이션

	int _x;							//이펙트 x좌표
	int _y;							//이펙트 y좌표
	float _elapsedTime;				//이펙트 경과시간
	bool _isRunning;				//이펙트 활성화 되었냐?

public:
	//init(이펙트 이미지, 프레임 가로크기, 프레임 세로크기, FPS수치, 경과시간)
	//FPS수치를 변경해도 되지만 조정하기 힘드니 그냥 1초로 세팅하고
	//경과시간을 변경해서 이펙트속도를 조정할것
	HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void release(void);
	void update(void);
	void render(void);

	//이펙트 터트릴 좌표
	void startEffect(int x, int y);
	//이펙트 비활성화
	void killEffect(void);

	//이펙트 활성화 상태값 가져오기
	bool getIsRunning(void) { return _isRunning; }
	
	effect();
	~effect();
};

