#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
//==================================================================
//		## txtData ## (텍스트데이타)
//==================================================================

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//로드
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	//세이브
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	txtData();
	~txtData();
};

