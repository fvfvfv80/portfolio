#pragma once
//==================================================================
//		## singletonBase ##
//==================================================================

template <typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	singletonBase(void) {}
	~singletonBase(void) {}
public:
	static T* getSingleton(void);
	void releaseSingleton(void);
};

//싱글톤 초기화
template <typename T>
T* singletonBase<T>::singleton = 0;

//싱글톤 값 가져온다
template <typename T>
T* singletonBase<T>::getSingleton(void)
{
	//싱글톤이 없다면 새로 생성해줘라
	if (!singleton) singleton = new T;
	return singleton;
}

//싱글톤을 메모리에서 해제한다
template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면 메모리에서 해제해주고 싱글톤을 0으로 초기화 해라
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}

