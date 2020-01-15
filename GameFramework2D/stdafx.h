// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

//==================================================================
//		## STL 자주 사용하는 헤더 파일 ##
//==================================================================
#include <string>
#include <vector>
#include <map>

//==================================================================
//		## 내가 만든 헤더파일을 이곳에 추가한다 ##
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
//		## 싱글톤을 추가한다 ##
//==================================================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER	timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()

//==================================================================
//		## 디파인문 ## (윈도우 초기화 세팅)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("2D Game Framework"))
#define WINSTARTX 500
#define WINSTARTY 000
#define WINSIZEX 1200
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================================
//		## 매크로함수 ## (메인게임의 릴리즈 부분에서 사용한다)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = NULL;}}

//==================================================================
//		## 내가 만든 네임스페이스 이곳에 추가한다 ##
//==================================================================
using namespace MY_UTIL;

//==================================================================
//		##  전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//==================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.