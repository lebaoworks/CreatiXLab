#include <stdio.h>
#include <windows.h>

#define CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
CreateWindowEx(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)

#define ID_INPUT 20
#define ID_PLUS 10
#define ID_MINUS 11
#define ID_MUL 12
#define ID_DIV 13
#define ID_CLR 14
#define ID_CALC 15

//-----------------------------------------------------------------------------//
//------------------------------------CALC-------------------------------------//
//-----------------------------------------------------------------------------//
typedef struct STACK_NODE_DATA
{
    int value;
    struct STACK_NODE_DATA* prev;
} STACK_NODE;


void calc(char* buffer)
{
    int i,j,value,res = 0;
    STACK_NODE* current = 0;
    STACK_NODE* this_node;
    int sign = 0, op = 0;

    //check valid
    for (i=0; buffer[i]!=0; i++)
        if ((buffer[i]<'0' || buffer[i]>'9') && buffer[i]!='+' && buffer[i]!='-' && buffer[i]!='*' && buffer[i]!='/')
        {
            memcpy(buffer,"ERROR!\0",7);
            return;
        }

    for (i=0; buffer[i]!=0;)
    {
        //if mul or div, save and go to next operator
        if (buffer[i] == '*')
        {
            op = 1;
            i++;
            continue;
        }
        if (buffer[i] == '/')
        {
            op = 2;
            i++;
            continue;
        }

        //extract operator
        if (buffer[i] == '+')
        {
            sign = 0;
            i++;
        }
        if (buffer[i] == '-')
        {
            sign = 1;
            i++;
        }

        value = 0;
        for (;buffer[i]>='0' && buffer[i]<='9'; i++)
            value = value*10 + buffer[i]-'0';
        if (sign)
            value *= -1;

        //if op>0 push to stack
        if (!op)
        {
            this_node = malloc(sizeof(STACK_NODE));
            this_node->value = value;
            this_node->prev = current;
            current = this_node;
        }
        else
        {
            if (op==1)
                current->value*=value;
            else
                current->value/=value;
            op = 0;
        }
    }

    //Calculate stack sum
    while (current!=0)
    {
        res += current->value;
        current = current->prev;
    }
    //Change output
    sprintf(buffer, "%d", res);
}

//-----------------------------------------------------------------------------//
//---------------------------------WINDOW-FORM---------------------------------//
//-----------------------------------------------------------------------------//
void AppendText(HWND hwnd, UINT ID, LPSTR str)
{
    char buffer[1024];
    GetDlgItemText(hwnd, ID_INPUT, buffer, sizeof(buffer));
    strcat(buffer,str);
    SetDlgItemText(hwnd, ID_INPUT, buffer);
}
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    char buffer[1024];

    switch(msg)
    {
        case WM_CREATE:
        {
            //hwndInput
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 0, 300, 100, hwnd, (HMENU) ID_INPUT, NULL, 0);

            CreateWindow(TEXT("button"), TEXT("7"), WS_VISIBLE | WS_CHILD, 0,     100,    75,     50, hwnd, (HMENU) 7, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("8"), WS_VISIBLE | WS_CHILD, 75,    100,    75,     50, hwnd, (HMENU) 8, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("9"), WS_VISIBLE | WS_CHILD, 150,   100,    75,     50, hwnd, (HMENU) 9, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("+"), WS_VISIBLE | WS_CHILD, 225,   100,    75,     50, hwnd, (HMENU) ID_PLUS, NULL, NULL);

            CreateWindow(TEXT("button"), TEXT("4"), WS_VISIBLE | WS_CHILD, 0,     150,    75,     50, hwnd, (HMENU) 4, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("5"), WS_VISIBLE | WS_CHILD, 75,    150,    75,     50, hwnd, (HMENU) 5, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("6"), WS_VISIBLE | WS_CHILD, 150,   150,    75,     50, hwnd, (HMENU) 6, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("-"), WS_VISIBLE | WS_CHILD, 225,   150,    75,     50, hwnd, (HMENU) ID_MINUS, NULL, NULL);

            CreateWindow(TEXT("button"), TEXT("1"), WS_VISIBLE | WS_CHILD, 0,     200,    75,     50, hwnd, (HMENU) 1, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("2"), WS_VISIBLE | WS_CHILD, 75,    200,    75,     50, hwnd, (HMENU) 2, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("3"), WS_VISIBLE | WS_CHILD, 150,   200,    75,     50, hwnd, (HMENU) 3, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("*"), WS_VISIBLE | WS_CHILD, 225,   200,    75,     50, hwnd, (HMENU) ID_MUL, NULL, NULL);

            CreateWindow(TEXT("button"), TEXT("0"), WS_VISIBLE | WS_CHILD, 0,     250,    75,     50, hwnd, (HMENU) 0, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("C"), WS_VISIBLE | WS_CHILD, 75,    250,    75,     50, hwnd, (HMENU) ID_CLR, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("="), WS_VISIBLE | WS_CHILD, 150,   250,    75,     50, hwnd, (HMENU) ID_CALC, NULL, NULL);
            CreateWindow(TEXT("button"), TEXT("/"), WS_VISIBLE | WS_CHILD, 225,   250,    75,     50, hwnd, (HMENU) ID_DIV, NULL, NULL);


            break;
        }
        case WM_COMMAND:
        {
            if (LOWORD(wParam)>=0 && LOWORD(wParam<ID_CLR))
            {
                GetDlgItemText(hwnd, LOWORD(wParam), buffer, sizeof(buffer));
                AppendText(hwnd, ID_INPUT, buffer);
                break;
            }
            if (LOWORD(wParam) == ID_CLR)
            {
                SetDlgItemText(hwnd, ID_INPUT, "");
                break;
            }
            if (LOWORD(wParam) == ID_CALC)
            {
                //1: GetWindowText(hwndInput,buffer, sizeof(buffer));
                //2: SendMessage(hwndInput, WM_GETTEXT, sizeof(buffer), buffer);
                GetDlgItemText(hwnd, ID_INPUT,buffer, sizeof(buffer));
                calc(buffer);

                SetDlgItemText(hwnd, ID_INPUT, buffer);
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //Remove console
    FreeConsole();

    //Init window information
    MSG msg;
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszClassName = TEXT("Calc");

    //Register Window
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Cannot register window!","Error",MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //Create Window
    HWND hwnd = CreateWindow(wc.lpszClassName, //Class Name
                             TEXT("Only: A[+B[-C[*D[/E...]]]]"), //Window Name
                             (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME )| WS_VISIBLE, //Style
                             300, //x
                             300, //y
                             305, //width
                             325, //Height
                             NULL, //Parent
                             NULL, //Menu
                             hInstance,
                             0); //Parameter
    if (!hwnd)
    {
        MessageBox(NULL, "Cannot create window!","Error",MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //Loop Get Message
    while( GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

