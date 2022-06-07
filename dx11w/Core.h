#pragma once

namespace dx
{
	class float2;
	class float4;

	class CoreParam
	{
		public:
			unsigned int width;
			unsigned int height;
			HWND windowHandle;
			bool windowed;
			DXGI_FORMAT depthBufferFormat;
			unsigned int sampleCount;
			unsigned int sampleQuality;

			CoreParam() :
				width(640), height(480),
				windowHandle(nullptr), windowed(true),
				depthBufferFormat(DXGI_FORMAT_D16_UNORM),
				sampleCount(1), sampleQuality(0)
			{
			}
	};

	enum DEVICELOST_REASON
	{
		DEVICE_OK,
		DEVICE_WAS_LOST_NEED_TO_RESET, // �v���Z�b�g
		DEVICE_WAS_LOST_NEED_TO_APPLICATION_QUIT, // �v�A�v����~
	};

	enum RENDERER_STATE
	{
		RENDERER_STATE_OK,
		RENDERER_STATE_STANDBY,
	};

	class Core
	{
		public:
			~Core();

			// ------ �V���O���g��
			static Core* getInstance();
			static void deleteInstance();

			// ------ �����ݒ�
			bool init(const CoreParam &coreParam);

			// ------ �`�F�b�N
			DEVICELOST_REASON checkDeviceLost() const;
			RENDERER_STATE checkRendererState() const;
			
			// ------ �����o�ϐ��擾
			Object<ID3D11Device> getDevice() const;
			Object<ID3D11DeviceContext> getImmediateContext() const;
			Object<ID3D11RenderTargetView> getBackbufferRenderTargetView() const;
			Object<ID3D11DepthStencilView> getBackbufferDepthStencilView() const;
			float2 getWindosSize() const;

			// ------ �`��R�}���h
			void clearRenderTargetView(Object<ID3D11RenderTargetView> &renderTargetView, float4& clearColor) const;
			void clearDepthStencilView(Object<ID3D11DepthStencilView>& depthStencilView,
				D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_DEPTH,
				float clearDepthValue = 1.0f) const;
			// �`���(�����_�[�^�[�Q�b�g / �[�x)���o�b�N�o�b�t�@�ɖ߂�
			void resetBackbuffer() const;
			// �o�b�N�o�b�t�@�N���A
			void cleaBackbuffer(const float4 &clearColor, float clearDepth = 1.0f) const;
			void present() const;

			// ------ �E�B���h�E����
			void quit();
			void resize(unsigned int resizeWidth, unsigned int resizeHeight);
			void switchWindow();

		private:
			Core();
			Core(const Core&);
			Core& operator=(const Core&);

			class CoreImpl;
			std::unique_ptr<CoreImpl> m_impl;
	};
}