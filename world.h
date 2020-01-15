#pragma once
#include "gameNode.h"


#define MAX_STRUCTURE1_NUM 10	
#define MAX_STRUCTURE2_NUM 10
#define MAX_DOOR_NUM 10							//�� ����
#define MAX_POINT_NUM 10						//���� ����Ʈ ����
#define MAX_MIRROR_NUM 10						//�ſ� ����
#define MAX_MMIRROR_NUM 10						//����� �ſ� ����
#define MAX_STRUCTURE_NUM 10					//���� ����
#define MAX_ALICE_MOTION 8						//�ٸ��� ��� ����
#define MAX_PLACE_NUM 10						//���� ����
#define GRAVITY 9.8/3600						//�߷�
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
////< �귯�� ����
//Brush = CreateSolidBrush(RGB(0, 200, 0));
//
////< �귯�� ���� �� ���� �귯�� ���
//oBrush = (HBRUSH)SelectObject(hdc, Brush);
//
////< ���
//Rectangle(hdc, 100, 100, 200, 200);
//Ellipse(hdc, 300, 300, 400, 400);
//
////< ���� �귯�� ����
//SelectObject(hdc, oBrush);
//
////< �귯�� ����
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


	sAlice _sAlice;								//�ٸ���
	sButtom _sButton;							//��ư
	sStructure _sStructure[MAX_STRUCTURE_NUM];	//������
	sStructure _sMStructure[MAX_STRUCTURE_NUM];
	sDoor _sDoor[MAX_DOOR_NUM];					//��
	sDoor _sMDoor[MAX_DOOR_NUM];					//��
	sMirror _sMirror[MAX_MIRROR_NUM];				//�ſ�
	sMirror _sMixMirror[MAX_MMIRROR_NUM];

	RECT _rStruc1[MAX_STRUCTURE1_NUM];
	RECT _rStruc2[MAX_STRUCTURE2_NUM];			
	RECT _rFloor;								//�ٴ�
	RECT _rSavePoint[MAX_POINT_NUM];			//�������
	
	
	sMap _sMap;
	

	//vector <sMirror> _vMirror;
	//vector<sMirror>::iterator _viMirror;
	
	bool _bIsInside;							//�ȿ��ִ���   �ȿ� ������ Ŀ���� �ۿ������� �۾����־���մϴ�
	bool _bIsMirror;							//�ſ������
	bool _bIsCheck;								///
	bool _bIsLoad;								//����Ǿ��ִ���
							
	int _iMirrorNum;
	int _iFadelevel;
	int _iFadeTime;
	int _iMoveLevel;
	float _fLoofMapX;
	float _fLoofMapY;
	

	//��������
	float _fGravity;							//�߷�
	float _fDegree;								//�Ÿ�
	

	int _iPlace;								//�����������


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setStage1(void);		
	void updateStage1(void);
	void drawStage1(void);

	void imageInit(void);

	//�̵�
	void movePlace();
	
	void openDoor();										//������

	//
	void crashCheck(RECT *rc);
	void rectCrash(RECT *rc);
	void playerCrash( RECT *rc);
	//

	//void rectPush(sFurniture *sFurniture);

	//void rectPull(sFurniture *sFurniture);

	void pushNPull(int num);

	//�̴°����� ���°����� �˷��ּ���

	void save(int place);									//����

	void fadeinout();										//
	
	void doorLock(sDoor *door,RECT *rc);					//�� ���
		
	void setAliceFrame(int motion, int index);				//�ٸ��� ������ ������

	void frame(image *image, int motion, int maxcount);		//������ ������

	void structureGravity(sMirror* furniture);					//�߷�

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

////�ؾ�����
//���̵��� ���̵�ƿ�
//����
//�̹��� �۾�
//�ʸ����
//�ſ� �� �����
//���� �ȿ��� ������ ������ ����
//�����鵵 �߷°��� ���� �� �ְ�
//�̴� ���� �̿��ϱ� ������Ģ�� ���
//�Ҹ��ִ¹�� �˾Ƴ���
//������ �� ��Ʈ �浹
//�б� ������ ��ųȭ
//png�� Ȱ��ȭ
//���ο� ���� �������� ����(�Ի簢 �ݻ簢. �Ѿ�)
//����\
//�ſ� ����
//���� ���·� �а����
//������ �а���� ������
//��Ʈ�� ������ ����
//����Ʈ �Ŵ����� Ȱ��

//���� �ػ� �Ǵ� ������