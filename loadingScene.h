#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading* _loading; //로딩클래스 선언
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//로딩 이미지 함수(이함수안에 전부 때려 넣어라)
	void loadingImage(void);

	loadingScene();
	~loadingScene();
};

