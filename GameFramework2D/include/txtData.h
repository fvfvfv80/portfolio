#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
//==================================================================
//		## txtData ## (�ؽ�Ʈ����Ÿ)
//==================================================================

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	//���̺�
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	txtData();
	~txtData();
};

