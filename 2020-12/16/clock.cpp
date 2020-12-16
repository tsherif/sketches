// Compile with -- cl /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" clock.cpp user32.lib d2d1.lib

#include <windows.h>
#include <tchar.h>
#include <d2d1.h>

ID2D1Factory *pFactory = NULL;
ID2D1HwndRenderTarget *pRenderTarget = NULL;
ID2D1SolidColorBrush *pBrush = NULL;
ID2D1SolidColorBrush *pStroke = NULL;
D2D1_ELLIPSE ellipse;

LRESULT CALLBACK WndProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

void DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth) {
    D2D1_POINT_2F endPoint = D2D1::Point2F(ellipse.point.x, ellipse.point.y - (ellipse.radiusY * fHandLength));
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(fAngle, ellipse.point));
    pRenderTarget->DrawLine(ellipse.point, endPoint, pStroke, fStrokeWidth);
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
) {
    WNDCLASSEX wcex = {};
    static TCHAR szWindowClass[] = _T("DesktopApp");
    static TCHAR szTitle[] = _T("Tarek made a CIRCLE with Direct2D!!!");

    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
            _T("Class registration failed!!!"),
            _T("Windows Desktop Guided Tour"),
            NULL
        );

        return 1;
    }

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL,
            _T("Create window failed!!!"),
            _T("Windows Desktop Guided Tour"),
            NULL
        );

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void CalculateLayout() {
    if (!pRenderTarget) {
        return;
    }

    D2D1_SIZE_F size = pRenderTarget->GetSize();
    const float x = size.width / 2;
    const float y = size.height / 2;
    const float r = min(x, y);
    ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), r, r);
}

void DiscardGraphicsResources() {
    if (pRenderTarget) {
        pRenderTarget->Release();
        pRenderTarget = NULL;
    }

    if (pBrush) {
        pBrush->Release();
        pBrush = NULL;
    }

    if (pStroke) {
        pStroke->Release();
        pStroke = NULL;
    }
}

LRESULT CALLBACK WndProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
) {
    HRESULT hr = S_OK;

    switch (message) {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
            return -1;
        }
        return 0;
    case WM_PAINT:
        // CreateGraphicsResources
        if (pRenderTarget == NULL) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
            hr = pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, size),
                &pRenderTarget
            );

            if (SUCCEEDED(hr)) {
                const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
                hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
            }

            if (SUCCEEDED(hr)) {
                const D2D1_COLOR_F color = D2D1::ColorF(0, 0, 0);
                hr = pRenderTarget->CreateSolidColorBrush(color, &pStroke);
            }

            if (SUCCEEDED(hr)) {
                CalculateLayout();
            }
        }

        // OnPaint
        if (SUCCEEDED(hr)) {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pRenderTarget->BeginDraw();
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

            pRenderTarget->FillEllipse(ellipse, pBrush);
            pRenderTarget->DrawEllipse(ellipse, pStroke);

            SYSTEMTIME time;
            GetLocalTime(&time);

            const float fHourAngle = 30.0f * time.wHour + 0.5f * time.wMinute;
            const float fMinuteAngle = 30.0f * time.wMinute;

            DrawClockHand(0.6f, fHourAngle, 6);
            DrawClockHand(0.85f, fMinuteAngle, 4);

            pRenderTarget->SetTransform( D2D1::Matrix3x2F::Identity() );

            hr = pRenderTarget->EndDraw();
            if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
                DiscardGraphicsResources();
            }

            EndPaint(hWnd, &ps);
        }

        return 0;

    case WM_SIZE:
        if (pRenderTarget) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
            pRenderTarget->Resize(size);
            CalculateLayout();
            InvalidateRect(hWnd, NULL, FALSE);
        }

        return 0;

    case WM_DESTROY:
        if (pFactory) {
            pFactory->Release();
            pFactory = NULL;
        }
        DiscardGraphicsResources();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}