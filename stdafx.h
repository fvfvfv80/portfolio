// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

//==================================================================
//		## STL ���� ����ϴ� ��� ���� ##
//==================================================================
#include <string>
#include <vector>
#include <map>

//==================================================================
//		## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//==================================================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "txtData.h"
#include "sceneManager.h"
#include "effectManager.h"



//==================================================================
//		## �̱����� �߰��Ѵ� ##
//==================================================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER	timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()

//==================================================================
//		## �����ι� ## (������ �ʱ�ȭ ����)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("2D Game Framework"))
#define WINSTARTX 500
#define WINSTARTY 000
#define WINSIZEX 1200
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================================
//		## ��ũ���Լ� ## (���ΰ����� ������ �κп��� ����Ѵ�)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = NULL;}}

//==================================================================
//		## ���� ���� ���ӽ����̽� �̰��� �߰��Ѵ� ##
//==================================================================
using namespace MY_UTIL;

//==================================================================
//		##  �������� ## (�ν��Ͻ�, �������ڵ�, ���콺��ǥ)
//==================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.