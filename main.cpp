#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

// Объявить процедуру Windows
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void LoadImages();

// имя класса в глобальную переменную
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int what_win =1;

HWND hEdit, hImgControl;
HBITMAP hImg;

int WINAPI WinMain (HINSTANCE hThisInstance,//дескриптор экземпляра приложения
                     HINSTANCE hPrevInstance,// в Win32 не используется
                     LPSTR lpszArgument, // нужен для запуска окна в режиме командной строки
                     int nCmdShow) // режим отображения окна
{
    HWND hwnd;               // уникальный номер окна
    MSG messages;            // Здесь сохраняются сообщения к приложению
    WNDCLASSEX wincl;        // Структура данных для оконного класса

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;        // Эта функция вызывается окнами
    //wincl.style = CS_DBLCLKS;                 // Catch double-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);

    //Использовать значок по умолчанию и указатель мыши
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 // нет меню
    wincl.cbClsExtra = 0;                      // Никаких лишних байтов после класса окна
    wincl.cbWndExtra = 0;                      // структура или экземпляр окна
    // Использовать цвет Windows по умолчанию в качестве фона окна
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    // Зарегистрируйте класс окна, и если это не удастся, выйдите из программы
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,                   // Расширенные возможности для вариации
           szClassName,
           _T("Code::Blocks Template Windows App"),       // заголовок
           WS_OVERLAPPEDWINDOW, // имеет строку заголовка и рамку, есть меню окна, строка заголовка, размернуая рамка, кнопка сворачивания, кнопка максимизации
           CW_USEDEFAULT,       // определяет позицию
           CW_USEDEFAULT,       // где окно заканчивается на экране
           544,                 // ширина
           375,                 // высота
           HWND_DESKTOP,        // Окно является дочерним окном для рабочего стола
           NULL,                // нет меню
           hThisInstance,       // Обработчик экземпляра программы
           NULL                 // Нет данных о создании окна
           );
    ShowWindow (hwnd, nCmdShow);
    //messages = {0};
    // Запуск цикла сообщений
    while (GetMessage (&messages, NULL, 0, 0))
    {
        // Преобразование сообщений виртуальных клавиш в символьные сообщения
        TranslateMessage(&messages);
        // Отправить сообщение WindowProcedure
        DispatchMessage(&messages);
    }

    // Возвращаемое значение программы равно 0 - значение, которое дал PostQuitMessage()
    return messages.wParam;
}


// Эта функция вызывается функцией Windows DispatchMessage()

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  // обрабатывать сообщения
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
            PostQuitMessage (0);       // отправить WM_QUIT в очередь сообщений
            break;
        default:                      // для сообщений, которыми мы не занимаемся
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

//CreateWindowEx (0,szClassName,_T("C"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,544,375,HWND_DESKTOP,NULL,hThisInstance,NULL);

void AddControls(HWND hwnd)//создаем все внутри окна
{
    switch (what_win)
    {
        case 1:
            CreateWindowEx(0,_T("Static"),_T("e"),WS_VISIBLE | WS_CHILD | ES_CENTER,0,0,60,20,hwnd,NULL,NULL,NULL);//data_main[i*EV_PART_COUNT+4],WS_VISIBLE | WS_CHILD | ES_CENTER,80,60,60,20,hWnd,NULL,NULL,NULL);
            CreateWindowEx(0,_T("Edit")  ,_T("e"),WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE /*| WS_VSCROLL*/,0,20,60,100,hwnd,NULL,NULL,NULL); //первая информация (здесь можно менять его размеры/положение)
            CreateWindowEx(0,_T("Button"),_T("e"),WS_VISIBLE | WS_CHILD,63,23,80,100,hwnd,(HMENU)1,NULL,NULL);
            hEdit = CreateWindowEx(0,_T("Combobox"), _T("combobox"),WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,60,0,80,100,hwnd,NULL,NULL,NULL);
            hImgControl = CreateWindowEx(0,_T("Static"),NULL,WS_VISIBLE | WS_CHILD | SS_BITMAP,200,10,0,0,hwnd,NULL,NULL,NULL); //изображение (здесь можно менять его положение)
            SendMessageW(hImgControl,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hImg);//для связи создания и загрузки изображения
            break;
    }
}

void LoadImages()
{
    //wchar_t buffer[30]=L"1";
    //wcscpy_s(buffer,30,L"img\\");
    //wcscat_s(buffer,30-ARRAYSIZE(L"img\\"),_T("1.bmp"));
    hImg = (HBITMAP)LoadImageA(NULL,_T("1.bmp"),IMAGE_BITMAP,180,230,LR_LOADFROMFILE);//data_main[i*EV_PART_COUNT+3],IMAGE_BITMAP,180,230,LR_LOADFROMFILE);//загрузка изображения (здесь можно менять его размеры)
}
