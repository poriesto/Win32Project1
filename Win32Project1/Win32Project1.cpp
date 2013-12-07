// Win32Project1.cpp: определяет точку входа для приложения.
//
#include "stdafx.h"
#include "Win32Project1.h"
#include "StatModule.h"
#define FILE_NAME "../stat.txt"
#define MAX_LOADSTRING 100
#define WIN32_LEAN_AND_MEAN
#define ID_MYBUTTON 1    /* идентификатор для кнопочки внутри главного окна */
#define ID_BT 2
#define ID_BT1 3
// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
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
   hWnd = CreateWindow(szWindowClass, "СУПИРЗМИЙКА", WS_OVERLAPPEDWINDOW,
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rec1;
	GetClientRect(hWnd, &rec1);
	switch (message)
	{
	case WM_CREATE:
		CreateWindow("button","Start Game",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2,100,20,hWnd,(HMENU)ID_MYBUTTON,NULL,NULL);
		CreateWindow("button","Options",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+20,100,20,hWnd,(HMENU)ID_BT,NULL,NULL);
		CreateWindow("button","Exit",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+40,100,20,hWnd,(HMENU)ID_BT1,NULL,NULL);
		return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		int Exit;
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_MYBUTTON)) 
				Game(argc, argv);
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT)) 
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Options);
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT1)) 
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
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		//Написать модуль анимации для лаунчера
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
	list<string>Cfg;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_CREATE:
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(DlgOptions, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam)==1020)
		{
			HWND hwndCheck = GetDlgItem(DlgOptions, 1020);
			LRESULT res = SendMessage (hwndCheck, BM_GETCHECK, 0, 0);
			if(res == BST_CHECKED)
			{
				SetWindowText(DlgOptions, "Checked");
				argv[1] = "-f";
			}
		}
		if(LOWORD(wParam)==1021)
		{
			HWND hwndCheck = GetDlgItem(DlgOptions, 1021);
			LRESULT res = SendMessage (hwndCheck, BM_GETCHECK, 0, 0);
			if(res == BST_CHECKED)
			{
				SetWindowText(DlgOptions, "Checked");
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