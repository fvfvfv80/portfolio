#pragma once
#include "singletonBase.h"
#include <time.h>
//==================================================================
//		## randomFunction ## (추가할것 없음 그냥 가져다 쓸것)
//==================================================================

class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void)
	{
	}

	//getInt
	inline int getInt(int num) { return rand() % num; }
	inline int getFromIntTo(int fromNum, int toNum) { return (rand() % (toNum - fromNum + 1)) + fromNum; }

	//getFloat
	//0.0 ~ 1.0 RAND_MAX rand함수의 최대값 (32767)
	float getFloat() { return (float)rand() / (float)RAND_MAX; }
	float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toFloat - fromFloat) + fromFloat);
	}
};

