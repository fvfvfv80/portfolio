#pragma once
#include "gameNode.h"
//==================================================================
//		## effect ## (����Ʈ Ŭ����) 
//==================================================================

//�ִϸ��̼� Ŭ���� ���漱��
class animation;

class effect : public gameNode
{
private:
	image* _effectImage;			//����Ʈ �̹���
	animation* _effectAnimation;	//����Ʈ �ִϸ��̼�

	int _x;							//����Ʈ x��ǥ
	int _y;							//����Ʈ y��ǥ
	float _elapsedTime;				//����Ʈ ����ð�
	bool _isRunning;				//����Ʈ Ȱ��ȭ �Ǿ���?

public:
	//init(����Ʈ �̹���, ������ ����ũ��, ������ ����ũ��, FPS��ġ, ����ð�)
	//FPS��ġ�� �����ص� ������ �����ϱ� ����� �׳� 1�ʷ� �����ϰ�
	//����ð��� �����ؼ� ����Ʈ�ӵ��� �����Ұ�
	HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void release(void);
	void update(void);
	void render(void);

	//����Ʈ ��Ʈ�� ��ǥ
	void startEffect(int x, int y);
	//����Ʈ ��Ȱ��ȭ
	void killEffect(void);

	//����Ʈ Ȱ��ȭ ���°� ��������
	bool getIsRunning(void) { return _isRunning; }
	
	effect();
	~effect();
};

