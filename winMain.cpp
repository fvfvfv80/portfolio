//==================================================================
//		## 헤더파일 써준다 ##
//==================================================================
#include "stdafx.h"
#include "mainGame.h"

//==================================================================
//		## 전역변수 써준다 ##
//==================================================================
//참고: 전역변수 및 클래스의 멤버변수에는 _붙여서 변수명을 작성한다
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = {0, 0};
//메인게임 클래스 선언
mainGame _mg;

//==================================================================
//		## 함수의 프로토타입 써준다 ## (함수원형)
//==================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//==================================================================
//		## 윈도우 메인함수 ## 
//==================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//hInstance : 프로그램의 인스턴스 핸들
	//hPrevInstance : 이전에 실행된 인스턴스 핸들 (지금은 사용안함)
	//lpszCmdParam : 명령행으로 입력된 프로그램 인수
	//nCmdShow : 프로그램이 시작될 형태 (최소화, 보통크기등등..)

	//인스턴스를 전역변수에 담아둔다
	_hInstance = hInstance;

	//MSG : 운영체제에서 발행하는 메시지 정보를 저장하기 위한 구조체
	MSG message;

	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//아이콘
	wndClass.hInstance = hInstance;									//인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//클래스이름
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTARTX,				//윈도우 화면좌표 x
		WINSTARTY,				//윈도우 화면좌표 y
		WINSIZEX,				//윈도우 화면좌표 width
		WINSIZEY,				//윈도우 화면좌표 height
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL);					//윈도우 및 자식 윈도우를 생성하면 지정해주되 그렇지 않으면 NULL

	//화면 작업 사이즈 영역 계산
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, nCmdShow);

	//메인게임 클래스의 초기화를 실패하면 바로 종료시켜라
	if (FAILED(_mg.init()))
	{
		return 0;
	}

	//메시지 루프~~
	//GetMessage : GetMessage는 메시지를 꺼내올 수 있을때까지 멈춰있는 함수이고,
	//PeekMessage : PeekMessage는 메시지가 없더라도 리턴되는 함수로서, 계속 루프되는 함수이다. 

	
	//게임용 메세지 루프 나중에 봉인해제할 때까지 그대로 놔둘것!!!
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			//초당 60프레임으로 업데이트 시켜라
			TIMEMANAGER->update(60.0f);
			_mg.update();	//메인게임 업데이트
			_mg.render();	//메인게임 렌더
		}
	}
	

	//TranslateMessage : 키보드 입력메시지 처리를 담당한다.
	//입력된 키가 문자키인지 확인후 대문자 혹은 소문자, 한글, 영문, 인지에 대한 WM_CHAR메시지를 발생시킨다.

	//DispatchMessage : 윈도우 프로시져에서 전달된 메시지를 실제 윈도우로 전달해준다

	/*
	//일반 프로그램용 메세지 루프임~
	//메시지 큐에 메시지가 있으면 메시지 처리...
	while (GetMessage(&message, 0, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/

	//메인게임 클래스 해제
	_mg.release();

	//윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//==================================================================
//		## 윈도우 프로시져 ## (메시지를 운영체제에 전달)
//==================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//메인게임 클래스의 프로시져에서 윈도우 메세지를 처리해준다
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//==================================================================
//		## 윈도우 크기 조정 ## (클라이언트 영역의 사이즈를 정확히 잡아준다)
//==================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 RECT 정보로 윈도우 사이즈 세팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
