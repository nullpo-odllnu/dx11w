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
		DEVICE_WAS_LOST_NEED_TO_RESET, // 要リセット
		DEVICE_WAS_LOST_NEED_TO_APPLICATION_QUIT, // 要アプリ停止
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

			// ------ シングルトン
			static Core* getInstance();
			static void deleteInstance();

			// ------ 初期設定
			bool init(const CoreParam &coreParam);

			// ------ チェック
			DEVICELOST_REASON checkDeviceLost() const;
			RENDERER_STATE checkRendererState() const;
			
			// ------ メンバ変数取得
			Object<ID3D11Device> getDevice() const;
			Object<ID3D11DeviceContext> getImmediateContext() const;
			Object<ID3D11RenderTargetView> getBackbufferRenderTargetView() const;
			Object<ID3D11DepthStencilView> getBackbufferDepthStencilView() const;
			float2 getWindosSize() const;

			// ------ 描画コマンド
			void clearRenderTargetView(Object<ID3D11RenderTargetView> &renderTargetView, float4& clearColor) const;
			void clearDepthStencilView(Object<ID3D11DepthStencilView>& depthStencilView,
				D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_DEPTH,
				float clearDepthValue = 1.0f) const;
			// 描画先(レンダーターゲット / 深度)をバックバッファに戻す
			void resetBackbuffer() const;
			// バックバッファクリア
			void cleaBackbuffer(const float4 &clearColor, float clearDepth = 1.0f) const;
			void present() const;

			// ------ ウィンドウ処理
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