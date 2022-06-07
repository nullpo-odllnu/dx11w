#pragma once

// VirtualKeyCode不足分
#define VK_0 (0x30)
#define VK_1 (VK_0 + 1)
#define VK_2 (VK_0 + 2)
#define VK_3 (VK_0 + 3)
#define VK_4 (VK_0 + 4)
#define VK_5 (VK_0 + 5)
#define VK_6 (VK_0 + 6)
#define VK_7 (VK_0 + 7)
#define VK_8 (VK_0 + 8)
#define VK_9 (VK_0 + 9)
#define VK_A (0x41)
#define VK_B (VK_A + 1)
#define VK_C (VK_A + 2)
#define VK_D (VK_A + 3)
#define VK_E (VK_A + 4)
#define VK_F (VK_A + 5)
#define VK_G (VK_A + 6)
#define VK_H (VK_A + 7)
#define VK_I (VK_A + 8)
#define VK_J (VK_A + 9)
#define VK_K (VK_A + 10)
#define VK_L (VK_A + 11)
#define VK_M (VK_A + 12)
#define VK_N (VK_A + 13)
#define VK_O (VK_A + 14)
#define VK_P (VK_A + 15)
#define VK_Q (VK_A + 16)
#define VK_R (VK_A + 17)
#define VK_S (VK_A + 18)
#define VK_T (VK_A + 19)
#define VK_U (VK_A + 20)
#define VK_V (VK_A + 21)
#define VK_W (VK_A + 22)
#define VK_X (VK_A + 23)
#define VK_Y (VK_A + 24)
#define VK_Z (VK_A + 25)

// ALTキー
#define VK_ALT VK_MENU
// Enterキー
#define VK_ENTER VK_RETURN

namespace dx
{
	class Input
	{
		public:
			// ------ シングルトン
			static Input* getInstance();
			static void deleteInstance();

			void update(HWND window);

			// ------ マウス
			unsigned int getMousePositionX() const;
			unsigned int getMousePositionY() const;
			int getMouseMoveX() const;
			int getMouseMoveY() const;
			bool getMouseTrigger(unsigned char virtualKeyCode);
			bool getMousePress(unsigned char virtualKeyCode);
			bool getMouseRelease(unsigned char virtualKeyCode);
			int getMouseWheelMove() const;
			// Windowsイベントから取得したものを格納
			void setMouseWheelMove(int wheelMove);

			// ------ キーボード
			bool getKeyboardTrigger(unsigned char virtualKeyCode);
			bool getKeyboardPress(unsigned char virtualKeyCode);
			bool getKeyboardRelease(unsigned char virtualKeyCode);

		private:
			Input();
			Input(const Input &input);
			Input& operator=(const Input& input);

			class InputImpl;
			std::unique_ptr<InputImpl> m_impl;
	};
} // namespace dx
