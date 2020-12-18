#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <d2d1.h>
#include <list>

#include "resource.h"

struct EllipseX {
    D2D1_ELLIPSE shape;
    D2D1_COLOR_F color;
};

enum Mode {
    DrawMode,
    SelectMode,
    DragMode
};

ID2D1Factory *pFactory = NULL;
ID2D1HwndRenderTarget *pRenderTarget = NULL;
ID2D1SolidColorBrush *pBrush = NULL;
ID2D1SolidColorBrush *pStroke = NULL;
D2D1_POINT_2F ptMouse;
float dpiScaleX = 1.0;
float dpiScaleY = 1.0;
Mode mode = DrawMode;
size_t nextColor = 0;
HCURSOR hCursor;

std::list<EllipseX> ellipses;
std::list<EllipseX>::iterator selection = ellipses.end();

D2D1::ColorF::Enum colors[] = { D2D1::ColorF::Yellow, D2D1::ColorF::Salmon, D2D1::ColorF::LimeGreen };


void DrawEllipse(D2D1_ELLIPSE e, D2D1_COLOR_F color) {
    pBrush->SetColor(color);
    pRenderTarget->FillEllipse(e, pBrush);
    pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
    pRenderTarget->DrawEllipse(e, pBrush, 1.0);
}

BOOL HitTestEllipse(D2D1_ELLIPSE e, float x, float y) {
    const float rx = e.radiusX;
    const float ry = e.radiusY;
    const float dx = x - e.point.x;
    const float dy = y - e.point.y;
    const float d = ((dx * dx) / (rx * rx)) + ((dy * dy) / (ry * ry));

    return d < 1.0f;
}

void InsertEllipse(float x, float y) {
    EllipseX e;
    e.shape.point = ptMouse = D2D1::Point2F(x, y);
    e.shape.radiusX = e.shape.radiusY = 2.0f;
    e.color = D2D1::ColorF(colors[nextColor]);

    nextColor = (nextColor + 1) % ARRAYSIZE(colors);

    selection = ellipses.insert(
        ellipses.end(),
        e
    );
}

void MoveSelection(float x, float y) {
    if (mode == SelectMode && selection != ellipses.end()) {
        selection->shape.point.x += x;
        selection->shape.point.y += y;
    }
}

void SetMode(Mode m) {
    mode = m;

    LPWSTR cursor;
    switch (mode) {
        case DrawMode:
            cursor = IDC_CROSS;
            break;

        case SelectMode:
            cursor = IDC_HAND;
            break;

        case DragMode:
            cursor = IDC_SIZEALL;
            break;
    }

    hCursor = LoadCursor(NULL, cursor);
    SetCursor(hCursor);
}

LRESULT CALLBACK WndProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

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

    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL1));

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {

        if (!TranslateAccelerator(hWnd, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
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
    FLOAT dpiX, dpiY;
    int pixelX, pixelY;
    POINT pt;

    switch (message) {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
            return -1;
        }
        ptMouse = D2D1::Point2F(0, 0);
        pFactory->GetDesktopDpi(&dpiX, &dpiY);
        dpiScaleX = dpiX / 96.0f;
        dpiScaleY = dpiY / 96.0f;

        SetMode(DrawMode);

        return 0;

    case WM_LBUTTONDOWN:
        pixelX = GET_X_LPARAM(lParam);
        pixelY = GET_Y_LPARAM(lParam);
        dpiX = (float) pixelX / dpiScaleX;
        dpiY = (float) pixelY / dpiScaleY;

        pt = {pixelX, pixelY};

        if (mode == DrawMode) {
            if (DragDetect(hWnd, pt)) {
                SetCapture(hWnd);
                InsertEllipse(dpiX, dpiY);
            }
        } else {
            selection = ellipses.end();
            for (auto i = ellipses.begin(); i != ellipses.end(); ++i) {
                if (HitTestEllipse(i->shape, dpiX, dpiY)) {
                    selection = i;
                    break;
                }
            }

            if (selection != ellipses.end()) {
                SetCapture(hWnd);
                ptMouse = selection->shape.point;
                ptMouse.x -= dpiX;
                ptMouse.y -= dpiY;

                SetMode(DragMode);
            }
        }

        InvalidateRect(hWnd, NULL, FALSE);

        return 0;

    case WM_LBUTTONUP:
        if (mode == DrawMode && selection != ellipses.end()) {
            selection = ellipses.end();
            InvalidateRect(hWnd, NULL, FALSE);
        } else if (mode == DragMode) {
            SetMode(SelectMode);
        }


        ReleaseCapture();

        return 0;

    case WM_MOUSEMOVE:
        pixelX = GET_X_LPARAM(lParam);
        pixelY = GET_Y_LPARAM(lParam);
        dpiX = (float) pixelX / dpiScaleX;
        dpiY = (float) pixelY / dpiScaleY;

        if (wParam & MK_LBUTTON) {
            if (mode == DrawMode) {
                const float rx = (dpiX - ptMouse.x) * 0.5;
                const float ry = (dpiY - ptMouse.y) * 0.5;
                float cx = ptMouse.x + rx;
                float cy = ptMouse.y + ry;

                selection->shape = D2D1::Ellipse(D2D1::Point2F(cx, cy), rx, ry);
            } else if (mode == DragMode) {
                selection->shape.point.x = dpiX + ptMouse.x;
                selection->shape.point.y = dpiY + ptMouse.y;
            }

            InvalidateRect(hWnd, NULL, FALSE);
        }

        return 0;

    case WM_SETCURSOR:

        if (LOWORD(lParam) == HTCLIENT) {
            SetCursor(hCursor);
            return 0;
        }

        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_BACK:
        case VK_DELETE:
            if (mode == SelectMode && selection != ellipses.end()) {
                ellipses.erase(selection);
                selection = ellipses.end();
                SetMode(SelectMode);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
        case VK_LEFT:
            MoveSelection(-1, 0);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case VK_RIGHT:
            MoveSelection(1, 0);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case VK_UP:
            MoveSelection(0, -1);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case VK_DOWN:
            MoveSelection(0, 1);
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        }

        return 0;

    case WM_COMMAND:
        
        switch (LOWORD(wParam)) {
        case ID_DRAW_MODE:
            SetMode(DrawMode);
            break;

        case ID_SELECT_MODE:
            SetMode(SelectMode);
            break;

        case ID_TOGGLE_MODE:
            if (mode == DrawMode) {
                SetMode(SelectMode);
            } else {
                SetMode(DrawMode);
            }
            break;
        
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
        }

        // OnPaint
        if (SUCCEEDED(hr)) {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pRenderTarget->BeginDraw();
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

            for (auto i = ellipses.begin(); i != ellipses.end(); ++i) {
                DrawEllipse(i->shape, i->color);
            }

            if (selection != ellipses.end()) {
                pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
                pRenderTarget->DrawEllipse(selection->shape, pBrush, 2.0);
            }

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