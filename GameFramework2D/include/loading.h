#pragma once
#include "gameNode.h"
#include "progressBar.h"

//==================================================================
//		## loadItem ## (�ε������ Ŭ����)
//==================================================================

//�ε������� ����
enum LOADING_KIND
{
	LOADING_KIND_IMAGE_00,
	LOADING_KIND_IMAGE_01,
	LOADING_KIND_IMAGE_02,
	LOADING_KIND_FRAMEIMAGE_00,
	LOADING_KIND_FRAMEIMAGE_01,
	LOADING_KIND_SOUND_00,
	LOADING_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;			//Ű�̸�
	const char* fileName;	//�����̸�
	int x, y;				//��ġ��ǥ
	int width, height;		//���μ���ũ��
	int frameX, frameY;		//������
	bool trans;				//����ȭ �Ҳ���?
	COLORREF transColor;	//�����÷�Ű
};

//Ŭ���� �ε������
class loadItem
{
private:
	LOADING_KIND _kind;					//�ε������� ����
	tagImageResource _imageResource;	//�̹��� ���ҽ� ����ü

public:
	//�̹��� �ε� ������
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	void release(void);

	//�ε������� ���� ��������
	LOADING_KIND getLoadingKind(void) { return _kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource(void) { return _imageResource; }

	loadItem(void);
	~loadItem(void);
};

//==================================================================
//		## loading ## (�ε� Ŭ����)
//==================================================================
class loading : public gameNode
{
private:
	//�ε������ Ŭ������ ���� ���� ����
	typedef vector<loadItem*> arrLoadItem;
	//�ε������ Ŭ������ ���� �ݺ��� ����
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;		//�ε������ ����

	image* _background;			//�ε�ȭ�鿡�� ����� ��׶��� �̹���
	progressBar* _loadingBar;	//�ε�ȭ�鿡�� ����� �ε���

	int _currentGauge;			//�ε��� ������������ ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	/*�̳��� �� �߿���*/
	//�̹��� �߰��Ҷ� ó�� �ε��Ҷ� ���� �߰����ָ� �ȴ�
	//�̹��� ����� Ű���� �˰� ������ �̹����� ȭ�鿡 �Ѹ� �� �ִ�
	
	//�ε��̹���(Ű��, ����ũ��, ����ũ��)
	void loadImage(string keyName, int width, int height);
	//�ε��̹���(Ű��, �����̸�, ����ũ��, ����ũ��, true, RGB(255, 0, 255))
	void loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	//�ε��̹���(Ű��, �����̸�, ��ġ��ǥx, ��ġ��ǥy, ����ũ��, ����ũ��, true, RGB(255, 0, 255))
	void loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	//�ε��������̹���(Ű��, �����̸�, ����ũ��, ����ũ��, ������x, ������y, true, RGB(255, 0, 255))
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	//�ε��������̹���(Ű��, �����̸�, ��ġ��ǥx, ��ġ��ǥy, ����ũ��, ����ũ��, ������x, ������y, true, RGB(255, 0, 255))
	void loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	BOOL loadNext(void);

	//�ε������ ���� ��������
	vector<loadItem*> getLoadItem(void) { return _vLoadItem; }

	loading(void);
	~loading(void);
};
