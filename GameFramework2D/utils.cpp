#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL //이건 너희들이 변경해도 된다
{
	//시작점부터 끝점까지의 각을 라디안값으로 구한다
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrt(x * x + y * y);
		float angle = acos(x / distance);
		if (y > 0) angle = PI2 - angle;

		return angle;
	}

	//두 점 사이의 거리를 구한다
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}
}
