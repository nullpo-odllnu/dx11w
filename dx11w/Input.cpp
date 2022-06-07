#include "Input.h"

namespace dx
{
	static Input *instance = nullptr;

	class Input::InputImpl
	{
		public:
			BYTE m_prevKeyboardState[256];
			BYTE m_currentKeyboardState[256];

			struct MouseInput
			{
				unsigned int x;
				unsigned int y;
			};
			MouseInput m_prevMouseInput;
			MouseInput m_currentMouseInput;

			int m_mouseWheel;
			int m_mouseWheelUpdate;

			InputImpl()
			{
				ZeroMemory(&m_prevKeyboardState, sizeof(m_prevKeyboardState));
				ZeroMemory(&m_currentKeyboardState, sizeof(m_currentKeyboardState));
				ZeroMemory(&m_prevMouseInput, sizeof(MouseInput));
				ZeroMemory(&m_currentMouseInput, sizeof(MouseInput));
				m_mouseWheel = 0;
				m_mouseWheelUpdate = 0;
			}

			void updateKeyState()
			{
				for (int i = 0; i < 256; i++)
				{
					m_prevKeyboardState[i] = m_currentKeyboardState[i];
					m_currentKeyboardState[i] = ((GetAsyncKeyState(i) & 0x8000) != 0) ? 1 : 0;
				}
			}
	};

	Input::Input()
	{
		m_impl = std::make_unique<InputImpl>();
	}

	void Input::update(HWND window)
	{
		// キーボード
		m_impl->updateKeyState();

		// マウス
		memcpy(&m_impl->m_prevMouseInput, &m_impl->m_currentMouseInput, sizeof(InputImpl::MouseInput));
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(window, &point);
		m_impl->m_currentMouseInput.x = point.x;
		m_impl->m_currentMouseInput.y = point.y;

		m_impl->m_mouseWheelUpdate = m_impl->m_mouseWheel;
		m_impl->m_mouseWheel = 0;
	}

	unsigned int Input::getMousePositionX() const
	{
		return m_impl->m_currentMouseInput.x;
	}
	unsigned int Input::getMousePositionY() const
	{
		return m_impl->m_currentMouseInput.y;
	}
	bool Input::getMouseTrigger(unsigned char virtualKeyCode)
	{
		switch (virtualKeyCode)
		{
			case VK_LBUTTON:
			case VK_RBUTTON:
			case VK_MBUTTON:
				return (m_impl->m_currentKeyboardState[virtualKeyCode] == 1) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 0);
			default:
				return false;
		}
	}
	bool Input::getMousePress(unsigned char virtualKeyCode)
	{
		switch (virtualKeyCode)
		{
			case VK_LBUTTON:
			case VK_RBUTTON:
			case VK_MBUTTON:
				return (m_impl->m_currentKeyboardState[virtualKeyCode] == 1) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 1);
			default:
				return false;
		}
	}
	bool Input::getMouseRelease(unsigned char virtualKeyCode)
	{
		switch (virtualKeyCode)
		{
			case VK_LBUTTON:
			case VK_RBUTTON:
			case VK_MBUTTON:
				return (m_impl->m_currentKeyboardState[virtualKeyCode] == 0) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 1);
			default:
				return false;
		}
	}
	int Input::getMouseWheelMove() const
	{
		return m_impl->m_mouseWheelUpdate;
	}
	void Input::setMouseWheelMove(int wheelMove)
	{
		m_impl->m_mouseWheel = wheelMove / WHEEL_DELTA;
	}
	int Input::getMouseMoveX() const
	{
		return m_impl->m_currentMouseInput.x - m_impl->m_prevMouseInput.x;
	}
	int Input::getMouseMoveY() const
	{
		return m_impl->m_currentMouseInput.y - m_impl->m_prevMouseInput.y;
	}

	bool Input::getKeyboardTrigger(unsigned char virtualKeyCode)
	{
		return (m_impl->m_currentKeyboardState[virtualKeyCode] == 1) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 0);
	}
	bool Input::getKeyboardPress(unsigned char virtualKeyCode)
	{
		return (m_impl->m_currentKeyboardState[virtualKeyCode] == 1) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 1);
	}
	bool Input::getKeyboardRelease(unsigned char virtualKeyCode)
	{
		return (m_impl->m_currentKeyboardState[virtualKeyCode] == 0) && (m_impl->m_prevKeyboardState[virtualKeyCode] == 1);
	}

	Input* Input::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Input();
		}
		return instance;
	}
	void Input::deleteInstance()
	{
		SAFE_DELETE(instance);
	}
} // namespace dx
