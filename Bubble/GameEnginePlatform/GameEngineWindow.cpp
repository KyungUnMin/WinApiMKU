#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>

HWND                       GameEngineWindow::HWnd = nullptr;
HDC                          GameEngineWindow::WindowBackBufferHdc = nullptr;
                                
float4                       GameEngineWindow::WindowSize = { 800, 600 };
float4                       GameEngineWindow::WindowPos = { 100, 100 };
float4                       GameEngineWindow::ScreenSize = { 800, 600 };

GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;

bool IsWindowUpdate = true;


//�޼����� ���� �ݹ� �Լ�
LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_MOUSEMOVE:
    {
        break;
    }
    case WM_SETFOCUS:
    {
        break;
    }
    case WM_ACTIVATE:
    {
        break;
    }
    case WM_KILLFOCUS:
    {
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}



GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{

}



void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    //������ Ŭ������ ����� ���� ���� ����
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    //�޼��� ó�� �ݹ�
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;

    //ū ������ ����
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    //����(�޴���) ����
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowDefault";

    //���� ������ ����
    wcex.hIconSm = nullptr;

    //����ó��
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }


    //������ â �����
    HWnd = CreateWindow(
        "GameEngineWindowDefault",
        _TitleName.data(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT
        , 0, CW_USEDEFAULT, 0
        , nullptr, nullptr, _hInstance, nullptr);


    //����ó��
    if (nullptr == HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    WindowBackBufferHdc = GetDC(HWnd);

    //������ â ����
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    //������ ũ�� ����(���ο��� ������ۿ� �̹��� ����)
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    //������ �����HDC�� ImageŬ������ ����
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, ScreenSize.half(), ScreenSize);
}


//���� ������ �����ϴ� �κ�
//�ݹ� ����� �̿��ؼ� ������ ������ �κ��� �и�
int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    while (IsWindowUpdate)
    {
        //�޼����� �ִٸ� �޼��� ó��
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (nullptr != _Loop)
            {
                _Loop();
            }
            continue;
        }

        if (nullptr != _Loop)
        {
            _Loop();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }


    if (nullptr != BackBufferImage)
    {
        //������ �����HDC�� Image��ü delete
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        //������ۿ� �̹��� delete
        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };
    ScreenSize = _Size;

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);


    //�̹����� �ٽ��ѹ� �������ϴ� ���
    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    //���� ���۸� �� �̹��� ����
    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);
}


void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}