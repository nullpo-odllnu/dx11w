#include <Core.h>
#include <float4.h>

// コールバック関数
LRESULT CALLBACK windowProcess(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT paintStruct;
			auto paint = BeginPaint(windowHandle, &paintStruct);
			EndPaint(windowHandle, &paintStruct);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(windowHandle, message, wParam, lParam);
		}

	return 0;
}

HWND createWindow(HINSTANCE instance, int commandShow,
	const tstring &title, unsigned int width, unsigned int height)
{
	auto titleString = reinterpret_cast<LPCTSTR>(title.c_str());

	// ウィンドウ作成
	// https://msdn.microsoft.com/ja-jp/windows/desktop/ms633577?f=255&MSPPError=-2147217396
	// http://www-higashi.ist.osaka-u.ac.jp/~k-maeda/vcpp/sec1-3wnddetail.html
	WNDCLASSEX window;
	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc = windowProcess;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = instance;
	window.hIcon = nullptr;
	window.hCursor = nullptr;
	// + 1するのはWNDCLASSEXの仕様
	window.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	window.lpszMenuName = nullptr;
	window.lpszClassName = titleString;
	window.hIconSm = nullptr;
	if (RegisterClassEx(&window) == 0)
	{
		return nullptr;
	}

	RECT rect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	// http://tokovalue.jp/function/AdjustWindowRect.htm
	if (AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE) == 0)
	{
		return nullptr;
	}

	// http://wisdom.sakura.ne.jp/system/winapi/win32/win7.html
	auto windowHandle = CreateWindow(
		titleString, titleString,
		WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom,
		nullptr, nullptr, instance, nullptr);
	if (windowHandle == nullptr)
	{
		return nullptr;
	}

	ShowWindow(windowHandle, commandShow);

	return windowHandle;
}

const unsigned int width = 900;
const unsigned int height = 540;
const tstring title = _T("dx11w_draw");
HWND window = nullptr;

void begin()
{
	auto param = dx::CoreParam();
	param.width = width;
	param.height = height;
	param.windowHandle = window;
	auto core = dx::Core::getInstance();

	if (core->init(param) == false)
	{
		core->quit();
	}
}

void update()
{
	auto core = dx::Core::getInstance();

	core->cleaBackbuffer(dx::float4(0.0f, 0.0f, 1.0f));
	core->present();
}

void end()
{
	dx::Core::deleteInstance();
}

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR commandline, int commandShow)
{
	setlocale(LC_ALL, "");

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	window = createWindow(instance, commandShow, title, width, height);

	begin();

	MSG message = { 0 };
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			update();
		}
	}

	end();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return static_cast<int>(message.wParam);
}
