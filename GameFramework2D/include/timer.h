#pragma once
//==================================================================
//		## timer ##
//==================================================================

class timer
{
private:
	bool			_isHardware;		//고성능 타이머를 지원하냐?
	float			_timeScale;			//시간 경과량
	float			_timeElapsed;		//마지막 시간과 현재 시간의 경과량
	__int64			_curTime;			//현재시간
	__int64			_lastTime;			//마지막시간
	__int64			_periodFrequency;	//시간주기

	unsigned long	_frameRate;			//FPS
	unsigned long	_FPSFrameCount;		//FPS카운트
	float			_FPSTimeElapsed;	//FPS 마지막 시간과 현재 시간의 경과량
	float			_worldTime;			//월드타임

public:
	//타이머 초기화
	HRESULT init(void);
	//현재 시간 계산
	void tick(float lockFPS = 0.0f);
	//현재 FPS를 얻어온다
	unsigned long getFrameRate(char* str = NULL) const;

	//마지막 시간과 현재시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	//전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }

	timer();
	~timer();
};

