#pragma once
//==================================================================
//		## animation ## (애니메이션 - 이펙트에서 사용함)
//==================================================================

class animation
{
public:
	typedef vector<POINT> _vFrameList;	//프레임 접근은 임의 접근이 가능해야해서 public으로 선언
	typedef vector<int> _vPlayList;		//프레임 플레이리스트
private:
	int _frameNum;						//프레임 수

	_vFrameList _frameList;				//프레임 위치 리스트
	_vPlayList _playList;				//플레이 리스트

	int _frameWidth;					//프레임 가로크기
	int _frameHeight;					//프레임 세로크기

	BOOL _loop;							//루프 할래?

	float _frameUpdateSec;				//프레임 업데이트 초
	float _elapsedSec;					//프레임 지난 초

	DWORD _nowPlayIdx;					//현재 플레이 인덱스(PLAY_LIST 값을 참조)
	BOOL _play;							//현재 플레이 여부

public:
	//init(이미지 전체 가로크기, 이미지 전체 세로크기, 프레임 가로크기, 프레임 세로크기) 
	HRESULT init(int totalW, int totalH, int frameW, int frameH); 
	void release(void);

	//기본셋팅
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);	
	//플레이 프레임 배열로 셋팅
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//플레이 프레임 시작과 종료로 셋팅
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	
	//초당 갱신 횟수
	void setFPS(int framePerSec); 
	//프레임 업데이트 타임
	void frameUpdate(float elpasedTime);
	
	//플레이 시작
	void start(void);
	//플레이 정지
	void stop(void);
	//일시정지
	void pause(void);
	//다시재생
	void resume(void);

	//플레이 여부 확인
	inline BOOL isPlay(void) { return _play; }
	//프레임 위치 가져오기
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	//프레임 가로크기 얻어오기
	inline int getFrameWidth(void) { return _frameWidth; }
	//프레임 세로크기 얻어오기
	inline int getFrameHeight(void) { return _frameHeight; }

	animation();
	~animation();
};

