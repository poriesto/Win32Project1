// Win32Project1.cpp: ���������� ����� ����� ��� ����������.
//
#include "stdafx.h"
#include "Win32Project1.h"

#define FILE_NAME "../stat.txt"
#define CONFIG "../config.txt"
#define GRAPHICS_MODE "../graphics.txt"
#define BITMAP_PATH "../btm.bmp"
#define PLAYLIST "../pl1.txt"
#define MAX_LOADSTRING 100
#define WIN32_LEAN_AND_MEAN
#define ID_BT1 100    /* ������������� ��� �������� ������ �������� ���� */
#define ID_BT2 200	
#define ID_BT3 300
#define ID_LIST 120

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
HBRUSH g_brush;
HANDLE SnD;
DWORD SnDid;
//HFONT g_hfFont;
//COLORREF g_rgbText;
int argc = 2; 
char *argv[] = {"GLUT_RGB", "-f", "GLUT_RGBA"};
// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Options(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Records(HWND, UINT, WPARAM, LPARAM);
void Game(int argc, char **argv);
DWORD WINAPI ThreadProcSound(LPVOID lpParameter);
void BitMap(HDC hdc, LPCSTR  Path, int x, int y, int Width, int Height, DWORD Param);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;
	
    g_brush = (HBRUSH)GetStockObject( NULL_BRUSH );

	//g_hfFont = (HFONT)GetStockObject(SYSTEM_FONT);
    //g_rgbText = (COLORREF)RGB(0, 0, 128);

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));
	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//   �������: InitInstance(HINSTANCE, int)
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//   �����������:
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������
   hWnd = CreateWindow(szWindowClass, "SuperSnake3D", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ����������:  ������������ ��������� � ������� ����.
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
void Bitmap(HDC hdc, LPCSTR  Path, int x, int y, int Width, int Height, DWORD Param)
{
    HBITMAP bmp = (HBITMAP) LoadImage(NULL,Path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    HDC memdc = CreateCompatibleDC(hdc);
    SelectObject(memdc,bmp);
    BitBlt(hdc,x,y,Width,Height,memdc,0,0,Param);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps, ps1, ps2, ps3;
	RECT rec1, rectGame, rectOpt, rectExt;
	static HWND hGame, hOptions, hExit;
	HDC hdc, hCompatibleDC, hdcGame, hdcOpt, hdcExt;
	HANDLE hBitmap, hOldBitmap;
	BITMAP Bitmap;
	GetClientRect(hWnd, &rec1);

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		CreateWindow("button","Start Game",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-100,rec1.bottom/2 - 35,200,30,hWnd,(HMENU)ID_BT1,NULL,NULL);
		CreateWindow("button","Options",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-100,rec1.bottom/2+20,200,30,hWnd,(HMENU)ID_BT2,NULL,NULL);
		CreateWindow("button","Exit",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-100,rec1.bottom/2+70,200,30,hWnd,(HMENU)ID_BT3,NULL,NULL);
		hGame = GetDlgItem(hWnd, ID_BT1);
		hOptions = GetDlgItem(hWnd, ID_BT2);
		hExit = GetDlgItem(hWnd, ID_BT3);
		GetClientRect(hGame, &rectGame);
		GetClientRect(hOptions, &rectOpt);
		GetClientRect(hExit, &rectExt);
		return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		int Exit;
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT1)) 
			Game(argc, argv);
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT2)) 
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Options);
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT3)) 
			Exit = MessageBox(hWnd, "Do u want exit?", "Exit from game", MB_YESNO|MB_ICONQUESTION);
			if(Exit == IDYES){
				DestroyWindow(hWnd);
			}
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_32771:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Records);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rec1);
		hBitmap = LoadImage(NULL, "../btm.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if(!hBitmap)
		{
			MessageBox(NULL, "FILE NOT FOUND!", "ERROR", MB_OK);
		}
		GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        /* ������� ����������� � ���������� ���� �������� � ������ */
        hCompatibleDC = CreateCompatibleDC(hdc);
        /* ������ ����������� ������ ������� � ����������� ��������� */
        hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
         /* ���������� ������ ������� ������� ���� */
        GetClientRect(hWnd, &rec1);
		// ���������� ������ � ������������ �� �������� �������� ���������� � ���������������� 
        StretchBlt(hdc, 0, 0, rec1.right, rec1.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, 
                    Bitmap.bmHeight, SRCCOPY);
		if(GetFocus() == hGame){
			hdcGame = BeginPaint(hGame, &ps1);
			GetClientRect(hGame, &rectGame);
			TextOut(hdcGame, rectGame.left/2 + 70, 
				rectGame.bottom/2, "Start Game", 10);
			SetBkColor(hdcGame, LTGRAY_BRUSH);
			EndPaint(hGame, &ps1);
		}
		if(GetFocus() == hOptions){
			hdcOpt = BeginPaint(hOptions, &ps2);
			GetClientRect(hOptions, &rectOpt);
			TextOut(hdcOpt, rectOpt.left/2 + 80,
				rectOpt.bottom/2, "Options", 7);
			SetBkColor(hdcOpt, LTGRAY_BRUSH);
			EndPaint(hOptions, &ps2);
		}
		if(GetFocus() == hExit){
			hdcExt = BeginPaint(hExit, &ps3);
			GetClientRect(hExit, &rectExt);
			TextOut(hdcExt, rectExt.left/2 + 90,
				rectExt.bottom/2, "Exit", 4);
			SetBkColor(hdcExt, LTGRAY_BRUSH);
			EndPaint(hExit, &ps3);
		}
		SnD = CreateThread(NULL, 0,ThreadProcSound,NULL,0,&SnDid);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETCURSOR:
		{
			if((HWND) wParam == hGame){
				if (GetFocus() != hGame){
					SetFocus(hGame);
					g_brush = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //The GetStockObject function retrieves a handle to one of the stock pens, brushes, fonts, or palettes.
					InvalidateRect(hWnd, NULL, FALSE);
					UpdateWindow(hWnd);
				}
			}
			else{
				g_brush = (HBRUSH)GetStockObject(NULL_BRUSH);
				SetFocus(hWnd);
			}
			if((HWND) wParam == hOptions){
				if (GetFocus() != hOptions) {
					SetFocus(hOptions);
					g_brush = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //The GetStockObject function retrieves a handle to one of the stock pens, brushes, fonts, or palettes.
					InvalidateRect(hWnd, NULL, FALSE);
					UpdateWindow(hWnd);
				}
			}
			if((HWND) wParam == hExit){
				if (GetFocus() != hExit) {
					SetFocus(hExit);
					g_brush = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //The GetStockObject function retrieves a handle to one of the stock pens, brushes, fonts, or palettes.
					InvalidateRect(hWnd, NULL, FALSE);
					UpdateWindow(hWnd);
				}
			}
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND DlgAbout, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(DlgAbout, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Options(HWND DlgOptions, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND optionsList;
	list<string>GraphicsMode;
	GraphicsMode = ReadConfigFromFile(GRAPHICS_MODE);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		optionsList = CreateWindow("listbox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT, 100, 0, 200, 100,
			DlgOptions, (HMENU) ID_LIST, hInst, NULL);
		SendMessage(optionsList, WM_SETREDRAW, FALSE, 0L);
		CreateOptions(optionsList, GraphicsMode);
		SendMessage(optionsList, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(optionsList, NULL, TRUE);
		return (INT_PTR)TRUE;
	case WM_SETFOCUS:
		SetFocus(optionsList);
		return 0;
	case WM_COMMAND:
		if(wParam == ID_LIST)
		{
			if(HIWORD(lParam) == (unsigned)LBN_ERRSPACE)
			{
				MessageBox(DlgOptions, "���� ������",
					"������", MB_OK|MB_ICONERROR);
			}
			else if(HIWORD(lParam) == LBN_DBLCLK)
			{
				int Item;
				char buf[256];
				Item = (int)SendMessage(optionsList,
					LB_GETCURSEL, 0, 0L);
				if(Item != LB_ERR)
				{
					SendMessage(optionsList, LB_GETTEXT, Item, (LPARAM)buf);
					argv[0] = buf;
				}
			}
			else if(HIWORD(lParam) == LBN_SELCHANGE)
			{
				int Item;
				char buf[256];
				Item = (int)SendMessage(optionsList, LB_GETCURSEL, 0, 0L);
				if(Item != LB_ERR)
				{
					SendMessage(optionsList, LB_GETTEXT, Item, (LPARAM)buf);
					argv[0] = buf;
				}
			}
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(DlgOptions, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam)==1020)
		{   //Fullscreen
			HWND hwndCheck = GetDlgItem(DlgOptions, 1020);
			LRESULT res = SendMessage (hwndCheck, BM_GETCHECK, 0, 0);
			if(res == BST_CHECKED)
			{
				SendMessage((HWND)1021, BM_GETCHECK, 0,0);
				argv[1] = "-f";
			}
		}
		if(LOWORD(wParam)==1021)
		{   //Windowed
			HWND hwndCheck = GetDlgItem(DlgOptions, 1021);
			LRESULT res = SendMessage (hwndCheck, BM_GETCHECK, 0, 0);
			if(res == BST_CHECKED)
			{
				SetWindowText(DlgOptions, "Windowed");
				argv[1] = "-w";
			}
		}
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==IDC_BUTTON1))
		{ 
			int confirm;
			confirm = MessageBox(DlgOptions,"Are u sure?","Save settings",MB_YESNO|MB_ICONQUESTION);
			if(confirm == IDYES)
			{
				EndDialog(DlgOptions, 0);
			}
		}
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==IDC_BUTTON2)) 
		{
			EndDialog(DlgOptions, 0);
		}
		break;
		 }
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Records(HWND DlgStat, UINT message, WPARAM wParam, LPARAM lParam)
{
	vector<Stat> V;
	vector<Stat>::iterator iter;
	HWND hwndList;
	int i = 0;
	switch(message)
	{
	case WM_INITDIALOG:
		V = ReadFromFile(FILE_NAME);
		hwndList = GetDlgItem(DlgStat, IDC_LIST2);
		iter = V.begin();
		while(iter!=V.end())
		{
			int y = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
				(LPARAM)PrintToTextField(iter).c_str());
			SendMessage(hwndList, LB_SETITEMDATA, y, (LPARAM)i);
			iter++;
			i++;
		}
		SetFocus(hwndList);
		return (INT_PTR)TRUE;
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		if((HIWORD(wParam)==0) && (LOWORD(wParam) == IDOK))
		{
			EndDialog(DlgStat,	LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if((HIWORD(wParam)==0) && (LOWORD(wParam)==IDCANCEL))
		{
			int Reset = MessageBox(DlgStat, "Do u want reset stats?", "Reset Stat", MB_YESNO|MB_ICONQUESTION);
			if(Reset == IDYES){
				/*
				�������� ����� ����������
				���������� ������� ���������� (���������)
				*/
				DeleteFile("../stat.txt");
				V.clear();
			}
		}
	}
	return (INT_PTR)FALSE;
}

void Game(int argc, char **argv)
{
	oglgfx *maingfx;
	oglgfx *gfx = new oglgfx();
	snakegame *maingame;
	snakegame* game = new snakegame(1);
	game->addrand();
	game->addrand();
	game->addrand();
	game->gfx = gfx;
	game->ctls[0] = (snakectl*) gfx;
	game->init();
	gfx->init(argc, argv);
}

DWORD WINAPI ThreadProcSound(LPVOID lpParameter)
{
	list<string>pl;
	pl = ReadConfigFromFile(PLAYLIST);
	list<string>::iterator iter = pl.begin();
	while(iter != pl.end()){
		PlaySound((LPCSTR)iter->c_str(), NULL, SND_FILENAME);
		PlaySound(NULL, 0, 0);
		iter++;
	}
	return TRUE;
}