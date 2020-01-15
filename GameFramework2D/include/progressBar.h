#pragma once
#include "gameNode.h"
//==================================================================
//		## progressBar ## (���α׷�����)
//==================================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//���α׷����� ��Ʈ
	int _x, _y;					//���α׷����� ��ġ��ǥ
	float _width;				//���α׷����� ���α���

	image* _progressBarFront;	//���α׷����� �� �̹���
	image* _progressBarBack;	//���α׷����� ��(�޹��) �̹���

public:
	//���α׷����� �ʱ�ȭ(���α׷����� ���̹���, ���α׷����� ���̹���, x��ġ, y��ġ, ���α���, ���α���)
	HRESULT init(char* frontImageName, char* backImageName, float x, float y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//���α׷������� ������ �����ϱ� 
	void setGauge(float currentGauge, float maxGauge);

	//���α׷����� X��ġ����
	void setX(int x) { _x = x; }
	//���α׷����� Y��ġ����
	void setY(int y) { _y = y; }
	//���α׷����� ��Ʈ ���
	RECT getRect(void) { return _rcProgress; }

	progressBar(void);
	~progressBar(void);
};

