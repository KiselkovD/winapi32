#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

// �������� ��������� Windows
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void LoadImages();

// ��� ������ � ���������� ����������
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int what_win =1;

HWND hEdit, hImgControl;
HBITMAP hImg;

int WINAPI WinMain (HINSTANCE hThisInstance,//���������� ���������� ����������
                     HINSTANCE hPrevInstance,// � Win32 �� ������������
                     LPSTR lpszArgument, // ����� ��� ������� ���� � ������ ��������� ������
                     int nCmdShow) // ����� ����������� ����
{
    HWND hwnd;               // ���������� ����� ����
    MSG messages;            // ����� ����������� ��������� � ����������
    WNDCLASSEX wincl;        // ��������� ������ ��� �������� ������

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;        // ��� ������� ���������� ������
    //wincl.style = CS_DBLCLKS;                 // Catch double-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);

    //������������ ������ �� ��������� � ��������� ����
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 // ��� ����
    wincl.cbClsExtra = 0;                      // ������� ������ ������ ����� ������ ����
    wincl.cbWndExtra = 0;                      // ��������� ��� ��������� ����
    // ������������ ���� Windows �� ��������� � �������� ���� ����
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    // ��������������� ����� ����, � ���� ��� �� �������, ������� �� ���������
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,                   // ����������� ����������� ��� ��������
           szClassName,
           _T("Code::Blocks Template Windows App"),       // ���������
           WS_OVERLAPPEDWINDOW, // ����� ������ ��������� � �����, ���� ���� ����, ������ ���������, ���������� �����, ������ ������������, ������ ������������
           CW_USEDEFAULT,       // ���������� �������
           CW_USEDEFAULT,       // ��� ���� ������������� �� ������
           544,                 // ������
           375,                 // ������
           HWND_DESKTOP,        // ���� �������� �������� ����� ��� �������� �����
           NULL,                // ��� ����
           hThisInstance,       // ���������� ���������� ���������
           NULL                 // ��� ������ � �������� ����
           );
    ShowWindow (hwnd, nCmdShow);
    //messages = {0};
    // ������ ����� ���������
    while (GetMessage (&messages, NULL, 0, 0))
    {
        // �������������� ��������� ����������� ������ � ���������� ���������
        TranslateMessage(&messages);
        // ��������� ��������� WindowProcedure
        DispatchMessage(&messages);
    }

    // ������������ �������� ��������� ����� 0 - ��������, ������� ��� PostQuitMessage()
    return messages.wParam;
}


// ��� ������� ���������� �������� Windows DispatchMessage()

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  // ������������ ���������
    {
        case WM_CREATE:
            LoadImages();
            AddControls(hwnd);

            break;
        switch (what_win)
        {
            case 1:
                case WM_COMMAND:
                    switch(wParam)
                    {
                    case 1:
                        break;
                    }
                    break;
                break;
        }
        case WM_DESTROY:
            PostQuitMessage (0);       // ��������� WM_QUIT � ������� ���������
            break;
        default:                      // ��� ���������, �������� �� �� ����������
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

//CreateWindowEx (0,szClassName,_T("C"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,544,375,HWND_DESKTOP,NULL,hThisInstance,NULL);

void AddControls(HWND hwnd)//������� ��� ������ ����
{
    switch (what_win)
    {
        case 1:
            CreateWindowEx(0,_T("Static"),_T("e"),WS_VISIBLE | WS_CHILD | ES_CENTER,0,0,60,20,hwnd,NULL,NULL,NULL);//data_main[i*EV_PART_COUNT+4],WS_VISIBLE | WS_CHILD | ES_CENTER,80,60,60,20,hWnd,NULL,NULL,NULL);
            CreateWindowEx(0,_T("Edit")  ,_T("e"),WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE /*| WS_VSCROLL*/,0,20,60,100,hwnd,NULL,NULL,NULL); //������ ���������� (����� ����� ������ ��� �������/���������)
            CreateWindowEx(0,_T("Button"),_T("e"),WS_VISIBLE | WS_CHILD,63,23,80,100,hwnd,(HMENU)1,NULL,NULL);
            hEdit = CreateWindowEx(0,_T("Combobox"), _T("combobox"),WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,60,0,80,100,hwnd,NULL,NULL,NULL);
            hImgControl = CreateWindowEx(0,_T("Static"),NULL,WS_VISIBLE | WS_CHILD | SS_BITMAP,200,10,0,0,hwnd,NULL,NULL,NULL); //����������� (����� ����� ������ ��� ���������)
            SendMessageW(hImgControl,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hImg);//��� ����� �������� � �������� �����������
            break;
    }
}

void LoadImages()
{
    //wchar_t buffer[30]=L"1";
    //wcscpy_s(buffer,30,L"img\\");
    //wcscat_s(buffer,30-ARRAYSIZE(L"img\\"),_T("1.bmp"));
    hImg = (HBITMAP)LoadImageA(NULL,_T("1.bmp"),IMAGE_BITMAP,180,230,LR_LOADFROMFILE);//data_main[i*EV_PART_COUNT+3],IMAGE_BITMAP,180,230,LR_LOADFROMFILE);//�������� ����������� (����� ����� ������ ��� �������)
}
