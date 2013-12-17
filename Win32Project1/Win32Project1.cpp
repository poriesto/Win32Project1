// Win32Project1.cpp: определяет точку входа для приложения.
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
#define ID_BT1 100    /* идентификатор для кнопочки внутри главного окна */
#define ID_BT2 200
#define ID_BT3 300
#define ID_LIST 120

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HBRUSH g_brush[2];
int argc = 2; 
char *argv[] = {"GLUT_RGB", "-f"};
// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Options(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Records(HWND, UINT, WPARAM, LPARAM);
void Game(int argc, char **argv);
void Audio(void);
DWORD WINAPI ThreadProcSound(LPVOID lpParameter);
void BitMap(HDC hdc, LPCSTR  Path, int x, int y, int Width, int Height, DWORD Param);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;
	
	g_brush[0] = (HBRUSH)GetStockObject( WHITE_BRUSH );
    g_brush[1] = (HBRUSH)GetStockObject( BLACK_BRUSH );
	
	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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

//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//   КОММЕНТАРИИ:
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
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

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
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
	PAINTSTRUCT ps;
	PAINTSTRUCT ps1;
	HDC hdc;
	HDC hdc1;
	RECT rec1;
	RECT rectGame;
	GetClientRect(hWnd, &rec1);
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	int index = 0;
	static HWND hGame;
	static HWND hOptions;
	static HWND hExit;
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		CreateWindow("button","Start Game",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2,100,30,hWnd,(HMENU)ID_BT1,NULL,NULL);
		CreateWindow("button","Options",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+30,100,30,hWnd,(HMENU)ID_BT2,NULL,NULL);
		CreateWindow("button","Exit",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+60,100,30,hWnd,(HMENU)ID_BT3,NULL,NULL);
		hGame = GetDlgItem(hWnd, ID_BT1);
		hOptions = GetDlgItem(hWnd, ID_BT2);
		hExit = GetDlgItem(hWnd, ID_BT3);
		 hdc = BeginPaint(hWnd, &ps);
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
			Exit = MessageBox(hWnd, "Do u want exit from this beateful game?", "Exit from game", MB_YESNO|MB_ICONQUESTION);
			if(Exit == IDYES){
				DestroyWindow(hWnd);
			}
		// Разобрать выбор в меню:
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
		hdc1 = BeginPaint(hGame, &ps1);
		GetClientRect(hGame, &rectGame);
	
		// TODO: добавьте любой код отрисовки...
		FillRect(ps1.hdc, &ps1.rcPaint, g_brush[index]);
		CreateThread(NULL, 0,ThreadProcSound,NULL,0,NULL);
		EndPaint(hGame, &ps1);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		//Написать модуль анимации для лаунчера
		GetClientRect(hWnd, &rec1);
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
	break;
	case WM_SETCURSOR:
		{
			if((HWND) wParam == hGame)
			{
				if (GetFocus() != hGame) {
					SetFocus(hGame);
					
					//MessageBox(hWnd, "FOCUSED", "dsfhskd",MB_OK);
					index = 0;
					g_brush[0] = (HBRUSH)GetStockObject( BLACK_BRUSH );
					InvalidateRect(hGame, &rectGame, TRUE);
					UpdateWindow(hGame);
				}
				
			}
			else
			{
				g_brush[0] = (HBRUSH)GetStockObject( WHITE_BRUSH );
				SetFocus(hWnd);
			}
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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
				MessageBox(DlgOptions, "Мало памяти",
					"Ошибка", MB_OK|MB_ICONERROR);
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
				удаление файла статистики
				деаллокейт вектора статистики (обнуление)
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
		PlaySound((LPCSTR)iter->c_str(), NULL, SND_FILENAME|SND_SYSTEM);
		PlaySound(NULL, 0, 0);
		iter++;
	}
	//PlaySound("E:\\1.wav", NULL, SND_ALIAS);
	return 0;
}