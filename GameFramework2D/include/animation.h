#pragma once
//==================================================================
//		## animation ## (�ִϸ��̼� - ����Ʈ���� �����)
//==================================================================

class animation
{
public:
	typedef vector<POINT> _vFrameList;	//������ ������ ���� ������ �����ؾ��ؼ� public���� ����
	typedef vector<int> _vPlayList;		//������ �÷��̸���Ʈ
private:
	int _frameNum;						//������ ��

	_vFrameList _frameList;				//������ ��ġ ����Ʈ
	_vPlayList _playList;				//�÷��� ����Ʈ

	int _frameWidth;					//������ ����ũ��
	int _frameHeight;					//������ ����ũ��

	BOOL _loop;							//���� �ҷ�?

	float _frameUpdateSec;				//������ ������Ʈ ��
	float _elapsedSec;					//������ ���� ��

	DWORD _nowPlayIdx;					//���� �÷��� �ε���(PLAY_LIST ���� ����)
	BOOL _play;							//���� �÷��� ����

public:
	//init(�̹��� ��ü ����ũ��, �̹��� ��ü ����ũ��, ������ ����ũ��, ������ ����ũ��) 
	HRESULT init(int totalW, int totalH, int frameW, int frameH); 
	void release(void);

	//�⺻����
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);	
	//�÷��� ������ �迭�� ����
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//�÷��� ������ ���۰� ����� ����
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	
	//�ʴ� ���� Ƚ��
	void setFPS(int framePerSec); 
	//������ ������Ʈ Ÿ��
	void frameUpdate(float elpasedTime);
	
	//�÷��� ����
	void start(void);
	//�÷��� ����
	void stop(void);
	//�Ͻ�����
	void pause(void);
	//�ٽ����
	void resume(void);

	//�÷��� ���� Ȯ��
	inline BOOL isPlay(void) { return _play; }
	//������ ��ġ ��������
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	//������ ����ũ�� ������
	inline int getFrameWidth(void) { return _frameWidth; }
	//������ ����ũ�� ������
	inline int getFrameHeight(void) { return _frameHeight; }

	animation();
	~animation();
};

