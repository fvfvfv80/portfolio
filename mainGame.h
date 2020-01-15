#pragma once
#include "gameNode.h"
#include "loadingScene.h"


#include "world.h"
#include "AliceIntro.h"
#include "intro.h"
#include "P_Engin.h"
#include "cRobotGame.h"
//==================================================================
//		## mainGame ## (메인게임 - 총괄 관리자 역할)
//==================================================================

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame();
	~mainGame();
};

