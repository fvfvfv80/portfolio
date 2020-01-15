#pragma once
#include "gameNode.h"


#define MAX_STRUCTURE1_NUM 10	
#define MAX_STRUCTURE2_NUM 10
#define MAX_DOOR_NUM 10							//문 개수
#define MAX_POINT_NUM 10						//저장 포인트 개수
#define MAX_MIRROR_NUM 10						//거울 개수
#define MAX_MMIRROR_NUM 10						//복사된 거울 개수
#define MAX_STRUCTURE_NUM 10					//가구 개수
#define MAX_ALICE_MOTION 8						//앨리스 모션 개수
#define MAX_PLACE_NUM 10						//맵의 개수
#define GRAVITY 9.8/3600						//중력
#define PI 3.14159265359

enum eMirrorType
{
	turnup,
	turnleft,
	both
};

enum eShape
{
	leftUp,
	leftDown,
	rightUp,
	rightDown,
};

enum eMotion
{
	stand,
	walking,
	jumping,
	runing,
	pulling,
	falling,
	pushing,
	
	Lgrab,
	Rgrab
};
enum eColor
{
	red,
	blue,
	green,
	purple,
	yellow,
	bgreen,
	black,
	white,
};
enum ePlace
{
	Stage1,
	Floor3,
	Floor2,
	Floor1,
};


enum eFurniture
{
	bed,
};

struct sAlice
{
	int weight;
	RECT size;
	int motion;
	float jumpPower;
	int hight;
	int width;
	int speed;
	bool isRight;
	bool canPull;
	

};

struct sButtom
{
	RECT yes;
	RECT no;
};


struct sFurniture
{
	//bool ispush;
	//RECT size;
	//image *image;
	//int kind;
	//int weight;
	//int gravity;


};

struct sMirror
{
	RECT size;
	int type;
	int color;
	bool isMake;
	int mixLv;
	bool isCanPush;

};

struct sStructure
{
	
	image *image;
	RECT size[2];
	int type;
	int color;
	//int weight;
	int width[2];
	int height[2];
	bool isSizeGaro;
	HBRUSH brush;
	
	
};

//hdc = BeginPaint(g_hWnd, &ps);
//
////< 브러쉬 생성
//Brush = CreateSolidBrush(RGB(0, 200, 0));
//
////< 브러쉬 선택 및 이전 브러쉬 백업
//oBrush = (HBRUSH)SelectObject(hdc, Brush);
//
////< 사용
//Rectangle(hdc, 100, 100, 200, 200);
//Ellipse(hdc, 300, 300, 400, 400);
//
////< 이전 브러쉬 선택
//SelectObject(hdc, oBrush);
//
////< 브러쉬 삭제
//DeleteObject(Brush);




struct sMap
{
	int kind;
	bool isRed;
	bool isBlue;
	bool isGreen;
	bool isPurple;
	bool isYellow;
	bool isBGreen;
	bool iscamera;
};

struct sAliceImage
{
	image* stand;
	image* jumping;
	image* walking;

	image* RM;
	image* GM;
	image* BM;
	image* PM;
	image* BGM;
	image* map;
	image* floor;
};

struct sFrame
{
	int time;
	int index;
};

struct sDoor
{
	RECT size;
	bool islock;
};

class world :
	public gameNode
{
private:
	

	sAliceImage _sAliceimage;
	sFrame _sAliceFrame[MAX_ALICE_MOTION];


	sAlice _sAlice;								//앨리스
	sButtom _sButton;							//버튼
	sStructure _sStructure[MAX_STRUCTURE_NUM];	//가구들
	sStructure _sMStructure[MAX_STRUCTURE_NUM];
	sDoor _sDoor[MAX_DOOR_NUM];					//문
	sDoor _sMDoor[MAX_DOOR_NUM];					//문
	sMirror _sMirror[MAX_MIRROR_NUM];				//거울
	sMirror _sMixMirror[MAX_MMIRROR_NUM];

	RECT _rStruc1[MAX_STRUCTURE1_NUM];
	RECT _rStruc2[MAX_STRUCTURE2_NUM];			
	RECT _rFloor;								//바닥
	RECT _rSavePoint[MAX_POINT_NUM];			//저장장소
	
	
	sMap _sMap;
	

	//vector <sMirror> _vMirror;
	//vector<sMirror>::iterator _viMirror;
	
	bool _bIsInside;							//안에있는지   안에 있을때 커지고 밖에있을땐 작아져있어야합니당
	bool _bIsMirror;							//거울속인지
	bool _bIsCheck;								///
	bool _bIsLoad;								//저장되어있는지
							
	int _iMirrorNum;
	int _iFadelevel;
	int _iFadeTime;
	int _iMoveLevel;
	float _fLoofMapX;
	float _fLoofMapY;
	

	//물리엔진
	float _fGravity;							//중력
	float _fDegree;								//거리
	

	int _iPlace;								//어디있으신지


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setStage1(void);		
	void updateStage1(void);
	void drawStage1(void);

	void imageInit(void);

	//이동
	void movePlace();
	
	void openDoor();										//문열기

	//
	void crashCheck(RECT *rc);
	void rectCrash(RECT *rc);
	void playerCrash( RECT *rc);
	//

	//void rectPush(sFurniture *sFurniture);

	//void rectPull(sFurniture *sFurniture);

	void pushNPull(int num);

	//미는것인지 당기는것인지 알려주세요

	void save(int place);									//저장

	void fadeinout();										//
	
	void doorLock(sDoor *door,RECT *rc);					//문 잠김
		
	void setAliceFrame(int motion, int index);				//앨리스 프레임 돌리기

	void frame(image *image, int motion, int maxcount);		//프레임 돌리기

	void structureGravity(sMirror* furniture);					//중력

	void setMap();

	void AliceInside();

	void EnterMirror(sMirror *mirror);
	void turnStructure(int color,bool mix);

	void setStructure(int num, int width1, int height1, int width2, int height2, int color, POINT pt1,int shape,bool isinside);

	void mixMirror();

	void moveCamera(int speedX,int speedY);

	void setMirror(bool what,int color, int ptx, int pty, int width, int height, int type);
	void eraseMirror(bool ismixmirror, int num);

	void reset();



	

	world();
	~world();
};

//_sMap.place

////해야할일
//페이드인 페이드아웃
//당기기
//이미지 작업
//맵만들기
//거울 속 만들기
//병원 안에서 있을때 사이즈 조절
//가구들도 중력값을 받을 수 있게
//미는 힘을 이용하기 물리법칙의 사용
//소리넣는방법 알아내기
//메이플 식 렉트 충돌
//밀기 당기기의 스킬화
//png의 활성화
//새로운 게임 컨텐츠의 도입(입사각 반사각. 총알)
//정리\
//거울 구현
//누른 상태로 밀고당기기
//누르고 밀고당기고 누르기
//인트로 영상의 수정
//이펙트 매니저의 활용

//문이 휜색 또는 검은색