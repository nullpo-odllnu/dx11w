#include "Core.h"

#include "float2.h"
#include "float4.h"

namespace dx
{
	static Core* coreInstance = nullptr;

	class Core::CoreImpl
	{
		public:
			Object<ID3D11Device> m_device;
			Object<ID3D11DeviceContext> m_immediateContext;
			Object<IDXGISwapChain> m_swapchain;
			Object<IDXGIFactory> m_factory; // ウィンドウ / フルスクリーン切り替え用
			Object<ID3D11RenderTargetView> m_backbufferRenderTargetView;
			Object<ID3D11DepthStencilView> m_backbufferDepthStencilView;

			D3D_FEATURE_LEVEL m_supportFeatureLevel;
			RENDERER_STATE m_rendererState;

			CoreParam m_param;

			CoreImpl()
			{
			}
			
			// 初期化シーケンス
			bool init()
			{
				printd(_T("[core::init sequence]\n"));
				
				printd(_T("createDeviceAndSwapchain\n"));
				if (createDeviceAndSwapchain() == false)
				{
					return false;
				}
				printd(_T("createBackbuffer\n"));
				if (createBackbuffer() == false)
				{
					return false;
				}
				printd(_T("window / fullscreen switch\n"));
				auto result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(m_factory.pointer()));
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("createdxgifactory"), result);
					return false;
				}

				printd(_T("[core::init finished]\n"));

				return true;
			}
			HRESULT createDeviceAndSwapchain_sub(DXGI_SWAP_CHAIN_DESC &swapchainDescription, D3D_DRIVER_TYPE driverType)
			{
				D3D_FEATURE_LEVEL featureLevelList[] = {
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};
				auto featureLevelNum = static_cast<unsigned int>(ARRAYSIZE(featureLevelList));
#ifdef _DEBUG
				unsigned int createDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
				unsigned int createDeviceFlag = 0;
#endif

				return D3D11CreateDeviceAndSwapChain(
					nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlag, featureLevelList, featureLevelNum, D3D11_SDK_VERSION, &swapchainDescription, m_swapchain.pointer(), m_device.pointer(), &m_supportFeatureLevel, m_immediateContext.pointer());
			}
			bool createDeviceAndSwapchain()
			{
				DXGI_SWAP_CHAIN_DESC swapchainDescription;
				ZeroMemory(&swapchainDescription, sizeof(swapchainDescription));
				swapchainDescription.BufferCount = 1;
				swapchainDescription.BufferDesc.Width = m_param.width;
				swapchainDescription.BufferDesc.Height = m_param.height;
				swapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				swapchainDescription.BufferDesc.RefreshRate.Numerator = 60;
				swapchainDescription.BufferDesc.RefreshRate.Denominator = 1;
				swapchainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				swapchainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
				swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapchainDescription.OutputWindow = m_param.windowHandle;
				swapchainDescription.SampleDesc.Count = m_param.sampleCount;
				swapchainDescription.SampleDesc.Quality = m_param.sampleQuality;
				swapchainDescription.Windowed = m_param.windowed;
				swapchainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				// ハードウェアドライバ
				auto result = createDeviceAndSwapchain_sub(swapchainDescription, D3D_DRIVER_TYPE_HARDWARE);
				tstring driverTypeDescription = _T("Driver : Unknown");
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("D3D11CreateDeviceAndSwapchain(Hardware)"), result);
					// WARP(高パフォーマンスソフトウェアドライバ)
					result = createDeviceAndSwapchain_sub(swapchainDescription, D3D_DRIVER_TYPE_WARP);
					if (FAILED(result))
					{
						DXTRACE_ERR_MSGBOX(_T("D3D11CreateDeviceAndSwapchain(WARP)"), result);
						// Reference(ソフトウェアドライバ)
						result = createDeviceAndSwapchain_sub(swapchainDescription, D3D_DRIVER_TYPE_REFERENCE);
						if (FAILED(result))
						{
							DXTRACE_ERR_MSGBOX(_T("D3D11CreateDeviceAndSwapchain(Reference)"), result);
							return false;
						}
						else
						{
							driverTypeDescription = _T("\nDriver : Reference\n");
						}
					}
					else
					{
						driverTypeDescription = _T("\nDriver : WARP\n");
					}
				}
				else
				{
					driverTypeDescription = _T("\nDriver : Hardware\n");
				}
				printd(driverTypeDescription);

				return true;
			}
			bool createBackbuffer()
			{
				Object<ID3D11Texture2D> backbuffer;
				auto result = m_swapchain.handle()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(backbuffer.pointer()));
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("swapchain::getbuffer"), result);
					return false;
				}
				result = m_device.handle()->CreateRenderTargetView(backbuffer.handle(), nullptr, m_backbufferRenderTargetView.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createrendertargetview"), result);
					return false;
				}
				m_immediateContext.handle()->OMSetRenderTargets(1, m_backbufferRenderTargetView.pointer(), nullptr);

				D3D11_VIEWPORT viewportList[1];
				viewportList[0].TopLeftX = 0.0f;
				viewportList[0].TopLeftY = 0.0f;
				viewportList[0].Width = static_cast<float>(m_param.width);
				viewportList[0].Height = static_cast<float>(m_param.height);
				viewportList[0].MinDepth = 0.0f;
				viewportList[0].MaxDepth = 1.0f;
				m_immediateContext.handle()->RSSetViewports(1, viewportList);

				Object<ID3D11Texture2D> depthstencil;
				D3D11_TEXTURE2D_DESC depthstencilDescription;
				depthstencilDescription.Width = m_param.width;
				depthstencilDescription.Height = m_param.height;
				depthstencilDescription.MipLevels = 1;
				depthstencilDescription.ArraySize = 1;
				depthstencilDescription.Format = m_param.depthBufferFormat;
				depthstencilDescription.SampleDesc.Count = m_param.sampleCount;
				depthstencilDescription.SampleDesc.Quality = m_param.sampleQuality;
				depthstencilDescription.Usage = D3D11_USAGE_DEFAULT;
				depthstencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				depthstencilDescription.CPUAccessFlags = 0;
				depthstencilDescription.MiscFlags = 0;
				result = m_device.handle()->CreateTexture2D(&depthstencilDescription, nullptr, depthstencil.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createtexture2d"), result);
					return false;
				}
				D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilViewDescription;
				depthstencilViewDescription.Format = depthstencilDescription.Format;
				depthstencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthstencilViewDescription.Flags = 0;
				depthstencilViewDescription.Texture2D.MipSlice = 0;
				result = m_device.handle()->CreateDepthStencilView(depthstencil.handle(), &depthstencilViewDescription, m_backbufferDepthStencilView.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createdepthstencilview"), result);
					return false;
				}
				m_immediateContext.handle()->OMSetRenderTargets(1, m_backbufferRenderTargetView.pointer(), m_backbufferDepthStencilView.handle());

				return true;
			}

		private:
			CoreImpl(const CoreImpl&);
	};

	Core::Core()
	{
		m_impl = std::make_unique<CoreImpl>();
	}
	Core::~Core()
	{
	}

	Core* Core::getInstance()
	{
		if (coreInstance == nullptr)
		{
			coreInstance = new Core();
		}

		return coreInstance;
	}
	void Core::deleteInstance()
	{
		SAFE_DELETE(coreInstance);
	}

	bool Core::init(const CoreParam& coreParam)
	{
		m_impl->m_param = coreParam;
		return m_impl->init();
	}

	void Core::quit()
	{
		PostQuitMessage(0);
	}
	void Core::setWindowTitle(const tstring& title)
	{
		SetWindowText(m_impl->m_param.windowHandle, title.c_str());
	}

	void Core::clearRenderTargetView(Object<ID3D11RenderTargetView> &renderTargetView, float4 &clearColor) const
	{
		m_impl->m_immediateContext.handle()->ClearRenderTargetView(renderTargetView.handle(), clearColor);
	}
	void Core::clearDepthStencilView(Object<ID3D11DepthStencilView>& depthStencilView, D3D11_CLEAR_FLAG clearFlag, float clearDepthValue) const
	{
		m_impl->m_immediateContext.handle()->ClearDepthStencilView(depthStencilView.handle(), clearFlag, clearDepthValue, 0);
	}
	void Core::cleaBackbuffer(const float4& clearColor, float clearDepth) const
	{
		clearRenderTargetView(m_impl->m_backbufferRenderTargetView, const_cast<float4&>(clearColor));
		clearDepthStencilView(m_impl->m_backbufferDepthStencilView, D3D11_CLEAR_DEPTH, clearDepth);
	}
	void Core::present() const
	{
		auto result = m_impl->m_swapchain.handle()->Present(0, 0);
		// スタンバイモード検知
		if (result == DXGI_STATUS_OCCLUDED)
		{
			m_impl->m_rendererState = RENDERER_STATE_STANDBY;
		}
		else if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("swapchain::present"), result);
		}
	}

	Object<ID3D11Device>* Core::getDevice() const
	{
		return &m_impl->m_device;
	}
	Object<ID3D11DeviceContext>* Core::getImmediateContext() const
	{
		return &m_impl->m_immediateContext;
	}
	Object<ID3D11RenderTargetView>* Core::getBackbufferRenderTargetView() const
	{
		return &m_impl->m_backbufferRenderTargetView;
	}
	Object<ID3D11DepthStencilView>* Core::getBackbufferDepthStencilView() const
	{
		return &m_impl->m_backbufferDepthStencilView;
	}
	float2 Core::getWindowSize() const
	{
		return float2(static_cast<float>(m_impl->m_param.width), static_cast<float>(m_impl->m_param.height));
	}
	HWND Core::getWindowHandle() const
	{
		return m_impl->m_param.windowHandle;
	}
}
