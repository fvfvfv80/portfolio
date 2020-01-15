#pragma once
//#include <cmath>
//==================================================================
//		## using namespace MY_UTIL ##
//==================================================================

#define DEG_TO_RAD 0.017453f //degree 1도(라디안 값)
#define PI 3.141592654f
#define PI2 (PI * 2)

#define PI_8		float(PI / 8.0f)
#define PI_16	float(PI / 16.0f)
#define PI_32	float(PI / 32.0f)
#define PI_64	float(PI / 64.0f)
#define PI_128	float(PI / 128.0f)

#define FLOAT_EPSILON 0.001f //실수의 가장 작은 단위
#define FLOAT_TO_INT(f1) static_cast<int> (f1 + FLOAT_EPSILON) //실수형을 정수형으로 변환한다
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON) //두 실수가 같은지 확인한다

namespace MY_UTIL //이건 너희들이 변경해도 된다
{
	//시작점부터 끝점까지의 각을 라디안값으로 구한다
	float getAngle(float startX, float startY, float endX, float endY);

	//두 점 사이의 거리를 구한다
	float getDistance(float startX, float startY, float endX, float endY);
}
