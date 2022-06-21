#include <Core.h>
#include <Input.h>
#include <Framerate.h>

#include <extension/Asset.h>

#include <float4.h>

// �R�[���o�b�N�֐�
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
		case WM_MOUSEWHEEL:
			{
				int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
				auto input = dx::Input::getInstance();
				input->setMouseWheelMove(wheelDelta);
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
	LPCTSTR title, unsigned int width, unsigned int height)
{
	// �E�B���h�E�쐬
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
	// + 1����̂�WNDCLASSEX�̎d�l
	window.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	window.lpszMenuName = nullptr;
	window.lpszClassName = title;
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
		title, title,
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
const unsigned int fps = 60;
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

	auto framerate = dx::Framerate::getInstance();
	framerate->set(fps);

	auto globalAssset = dx::GlobalAsset::getInstance();
	if (globalAssset->init() == false)
	{
		core->quit();
	}
}

void update()
{
	auto core = dx::Core::getInstance();
	auto input = dx::Input::getInstance();

	input->update(core->getWindowHandle());

	core->cleaBackbuffer(dx::float4(0.0f, 0.0f, 1.0f));
	core->present();

	// �I������
	if (input->getKeyboardRelease(VK_ESCAPE))
	{
		core->quit();
	}

	auto framerate = dx::Framerate::getInstance();
	framerate->update();
	framerate->offset();

	core->setWindowTitle(dx::format(_T("dx11w_draw %.3f"), framerate->getPresentFramerate()));
}

void end()
{
	dx::Core::deleteInstance();
	dx::Input::deleteInstance();
	dx::Framerate::deleteInstance();
	dx::GlobalAsset::deleteInstance();
}

int WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPTSTR commandline, int commandShow)
{
	setlocale(LC_ALL, "");

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	auto title = _T("dx11w_draw");
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
