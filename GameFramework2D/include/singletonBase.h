#pragma once
//==================================================================
//		## singletonBase ##
//==================================================================

template <typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	singletonBase(void) {}
	~singletonBase(void) {}
public:
	static T* getSingleton(void);
	void releaseSingleton(void);
};

//�̱��� �ʱ�ȭ
template <typename T>
T* singletonBase<T>::singleton = 0;

//�̱��� �� �����´�
template <typename T>
T* singletonBase<T>::getSingleton(void)
{
	//�̱����� ���ٸ� ���� ���������
	if (!singleton) singleton = new T;
	return singleton;
}

//�̱����� �޸𸮿��� �����Ѵ�
template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	//�̱����� �ִٸ� �޸𸮿��� �������ְ� �̱����� 0���� �ʱ�ȭ �ض�
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}

