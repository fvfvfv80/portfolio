#pragma once
//#include <cmath>
//==================================================================
//		## using namespace MY_UTIL ##
//==================================================================

#define DEG_TO_RAD 0.017453f //degree 1��(���� ��)
#define PI 3.141592654f
#define PI2 (PI * 2)

#define PI_8		float(PI / 8.0f)
#define PI_16	float(PI / 16.0f)
#define PI_32	float(PI / 32.0f)
#define PI_64	float(PI / 64.0f)
#define PI_128	float(PI / 128.0f)

#define FLOAT_EPSILON 0.001f //�Ǽ��� ���� ���� ����
#define FLOAT_TO_INT(f1) static_cast<int> (f1 + FLOAT_EPSILON) //�Ǽ����� ���������� ��ȯ�Ѵ�
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON) //�� �Ǽ��� ������ Ȯ���Ѵ�

namespace MY_UTIL //�̰� ������� �����ص� �ȴ�
{
	//���������� ���������� ���� ���Ȱ����� ���Ѵ�
	float getAngle(float startX, float startY, float endX, float endY);

	//�� �� ������ �Ÿ��� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY);
}
