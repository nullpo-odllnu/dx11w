#include "Asset.h"

#include "../Core.h"

namespace dx
{
	class Asset::Impl
	{
	public:
		std::map<unsigned int, VertexBuffer> m_vertexBufferDict;
		std::map<unsigned int, IndexBuffer> m_indexBufferDict;
		std::map<unsigned int, ConstantBuffer> m_constantBufferDict;
		std::map<unsigned int, VertexShader> m_vertexShaderDict;
		std::map<unsigned int, PixelShader> m_pixelShaderDict;
		std::map<unsigned int, InputLayout> m_inputLayoutDict;
		std::map<unsigned int, RasterizerState> m_rasterizerStateDict;
		std::map<unsigned int, BlendState> m_blendStateDict;
		std::map<unsigned int, DepthState> m_depthStateDict;
		std::map<unsigned int, Texture2D> m_texture2DDict;

		std::map<unsigned int, RenderState> m_renderStateDict;
	};

	Asset::Asset()
	{
		m_impl = std::make_unique<Asset::Impl>();
	}

	VertexBuffer* Asset::getVertexBuffer(unsigned int id)
	{
		if (m_impl->m_vertexBufferDict.find(id) == m_impl->m_vertexBufferDict.end())
		{
			m_impl->m_vertexBufferDict.insert(std::make_pair(id, VertexBuffer()));
		}
		return &m_impl->m_vertexBufferDict[id];
	}
	IndexBuffer* Asset::getIndexBuffer(unsigned int id)
	{
		if (m_impl->m_indexBufferDict.find(id) == m_impl->m_indexBufferDict.end())
		{
			m_impl->m_indexBufferDict.insert(std::make_pair(id, IndexBuffer()));
		}
		return &m_impl->m_indexBufferDict[id];
	}
	ConstantBuffer* Asset::getConstantBuffer(unsigned int id)
	{
		if (m_impl->m_constantBufferDict.find(id) == m_impl->m_constantBufferDict.end())
		{
			m_impl->m_constantBufferDict.insert(std::make_pair(id, ConstantBuffer()));
		}
		return &m_impl->m_constantBufferDict[id];
	}
	VertexShader* Asset::getVertexShader(unsigned int id)
	{
		if (m_impl->m_vertexShaderDict.find(id) == m_impl->m_vertexShaderDict.end())
		{
			m_impl->m_vertexShaderDict.insert(std::make_pair(id, VertexShader()));
		}
		return &m_impl->m_vertexShaderDict[id];
	}
	PixelShader* Asset::getPixelShader(unsigned int id)
	{
		if (m_impl->m_pixelShaderDict.find(id) == m_impl->m_pixelShaderDict.end())
		{
			m_impl->m_pixelShaderDict.insert(std::make_pair(id, PixelShader()));
		}
		return &m_impl->m_pixelShaderDict[id];
	}
	InputLayout* Asset::getInputLayout(unsigned int id)
	{
		if (m_impl->m_inputLayoutDict.find(id) == m_impl->m_inputLayoutDict.end())
		{
			m_impl->m_inputLayoutDict.insert(std::make_pair(id, InputLayout()));
		}
		return &m_impl->m_inputLayoutDict[id];
	}
	RasterizerState* Asset::getRasterizerState(unsigned int id)
	{
		if (m_impl->m_rasterizerStateDict.find(id) == m_impl->m_rasterizerStateDict.end())
		{
			m_impl->m_rasterizerStateDict.insert(std::make_pair(id, RasterizerState()));
		}
		return &m_impl->m_rasterizerStateDict[id];
	}
	BlendState* Asset::getBlendState(unsigned int id)
	{
		if (m_impl->m_blendStateDict.find(id) == m_impl->m_blendStateDict.end())
		{
			m_impl->m_blendStateDict.insert(std::make_pair(id, BlendState()));
		}
		return &m_impl->m_blendStateDict[id];
	}
	DepthState* Asset::getDepthState(unsigned int id)
	{
		if (m_impl->m_depthStateDict.find(id) == m_impl->m_depthStateDict.end())
		{
			m_impl->m_depthStateDict.insert(std::make_pair(id, DepthState()));
		}
		return &m_impl->m_depthStateDict[id];
	}
	Texture2D* Asset::getTexture2D(unsigned int id)
	{
		if (m_impl->m_texture2DDict.find(id) == m_impl->m_texture2DDict.end())
		{
			m_impl->m_texture2DDict.insert(std::make_pair(id, Texture2D()));
		}
		return &m_impl->m_texture2DDict[id];
	}

	RenderState* Asset::getRenderState(unsigned int id)
	{
		if (m_impl->m_renderStateDict.find(id) == m_impl->m_renderStateDict.end())
		{
			m_impl->m_renderStateDict.insert(std::make_pair(id, RenderState()));
		}
		return &m_impl->m_renderStateDict[id];
	}

	RenderState::RenderState() : 
		m_inputLayoutID (0),
		m_indexBufferID (0),
		m_vertexShaderID (0),
		m_pixelShaderID (0),
		m_primitiveTopology (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
		m_rasterizerStateID (0),
		m_blendStateID (0),
		m_depthStateID (0),
		m_createViewportFromRenderTarget (true),
		m_depthStencilViewID (0)
	{
	}

	void Asset::begin(Object<ID3D11DeviceContext> *deviceContext, unsigned int renderStateID)
	{
		auto renderState = getRenderState(renderStateID);

		if (renderState->m_inputLayoutID != 0)
		{
			auto inputLayout = getInputLayout(renderState->m_inputLayoutID);
			inputLayout->set(deviceContext);
		}
		if (renderState->m_vertexBufferIDList.empty() != false)
		{
			// D3D11_STANDARD_VERTEX_ELEMENT_COUNT(32)準拠
			ID3D11Buffer* bufferList[32];
			unsigned int vertexSizeList[32];
			unsigned int offsetList[32];
			ZeroMemory(offsetList, sizeof(offsetList));

			unsigned int bufferSize = static_cast<unsigned int>(renderState->m_vertexBufferIDList.size());
			for (unsigned int i = 0; i < bufferSize; i++)
			{
				auto vertexBuffer = getVertexBuffer(renderState->m_vertexBufferIDList[i]);
				bufferList[i] = vertexBuffer->handle();
				vertexSizeList[i] = vertexBuffer->getStructSize();
			}

			deviceContext->handle()->IASetVertexBuffers(0, bufferSize, bufferList, vertexSizeList, offsetList);
		}
		if (renderState->m_indexBufferID != 0)
		{
			auto indexBuffer = getIndexBuffer(renderState->m_indexBufferID);
			setIndexBuffer(deviceContext, indexBuffer);
		}
		if (renderState->m_constantBufferIDList.empty() != false)
		{
			// D3D11_COMMON_SHADER_TEMP_REGISTER_COUNT(4096)よりは少なめ
			ID3D11Buffer* bufferList[128];

			unsigned int bufferSize = static_cast<unsigned int>(renderState->m_constantBufferIDList.size());
			for (unsigned int i = 0; i < bufferSize; i++)
			{
				auto constantBuffer = getConstantBuffer(renderState->m_constantBufferIDList[i]);
				bufferList[i] = constantBuffer->handle();
			}

			// シェーダがセットされている場合にのみ定数バッファ群を渡す
			if (renderState->m_vertexShaderID != 0)
			{
				deviceContext->handle()->VSSetConstantBuffers(0, bufferSize, bufferList);
			}
			if (renderState->m_pixelShaderID != 0)
			{
				deviceContext->handle()->PSSetConstantBuffers(0, bufferSize, bufferList);
			}
		}
		if (renderState->m_vertexShaderID != 0)
		{
			auto vertexShader = getVertexShader(renderState->m_vertexShaderID);
			vertexShader->set(deviceContext);
		}
		if (renderState->m_pixelShaderID != 0)
		{
			auto pixelShader = getPixelShader(renderState->m_pixelShaderID);
			pixelShader->set(deviceContext);
		}
		setPrimitiveTopology(deviceContext, renderState->m_primitiveTopology);
		if (renderState->m_rasterizerStateID != 0)
		{
			auto rasterizerState = getRasterizerState(renderState->m_rasterizerStateID);
			rasterizerState->set(deviceContext);
		}
		if (renderState->m_blendStateID != 0)
		{
			auto blendState = getBlendState(renderState->m_blendStateID);
			blendState->set(deviceContext);
		}
		if (renderState->m_depthStateID != 0)
		{
			auto depthState = getDepthState(renderState->m_depthStateID);
			depthState->set(deviceContext);
		}
		// レンダーターゲット群からビューポートを作成する
		if (renderState->m_createViewportFromRenderTarget)
		{
			// pixel shader output slot(8)準拠
			D3D11_VIEWPORT viewportList[8];
			ZeroMemory(viewportList, sizeof(viewportList));

			if (renderState->m_renderTargetViewIDList.empty() != false)
			{
				auto renderTargetSize = static_cast<unsigned int>(renderState->m_renderTargetViewIDList.size());
				for (unsigned int i = 0; i < renderTargetSize; i++)
				{
					auto index = renderState->m_renderTargetViewIDList[i];
					// -1の場合はバックバッファ参照
					if (index == -1)
					{
						viewportList[i] = Viewport(Core::getInstance()->getWindowSize());
					}
					else
					{
						auto texture2D = getTexture2D(index);
						viewportList[i] = texture2D->getViewport();
					}
				}
			}

			deviceContext->handle()->RSSetViewports(8, viewportList);
		}
		// pixel shader output slot(8)準拠
		ID3D11RenderTargetView *renderTargetViewList[8];
		ZeroMemory(renderTargetViewList, sizeof(renderTargetViewList));
		ID3D11DepthStencilView *depthStencilView = nullptr;
		if (renderState->m_renderTargetViewIDList.empty() != false)
		{
			auto renderTargetSize = static_cast<unsigned int>(renderState->m_renderTargetViewIDList.size());
			for (unsigned int i = 0; i < renderTargetSize; i++)
			{
				auto index = renderState->m_renderTargetViewIDList[i];
				// -1の場合ばバックバッファ参照
				if (index == -1)
				{
					renderTargetViewList[i] = Core::getInstance()->getBackbufferRenderTargetView()->handle();
				}
				else
				{
					auto texture2D = getTexture2D(index);
					renderTargetViewList[i] = texture2D->getRenderTargetView()->handle();
				}
			}
		}
		if (renderState->m_depthStencilViewID != 0)
		{
			// -1の場合はバックバッファ参照
			if (renderState->m_depthStencilViewID == -1)
			{
				depthStencilView = Core::getInstance()->getBackbufferDepthStencilView()->handle();
			}
			else
			{
				auto texture2D = getTexture2D(renderState->m_depthStencilViewID);
				depthStencilView = texture2D->getDepthStencilView()->handle();
			}
		}
		deviceContext->handle()->OMSetRenderTargets(8, renderTargetViewList, depthStencilView);
	}

	void Asset::end(Object<ID3D11DeviceContext>* deviceContext)
	{
		ID3D11RenderTargetView* renderTargetViewList[8];
		ZeroMemory(renderTargetViewList, sizeof(renderTargetViewList));

		deviceContext->handle()->OMSetRenderTargets(8, renderTargetViewList, nullptr);
	}

	static GlobalAsset* instance = nullptr;
	class GlobalAsset::Impl
	{
		public:
			bool init()
			{
				printd(_T("[GlobalAsset init sequence]\n"));
				
				printd(_T("createConstantBuffer\n"));
				if (createConstantBuffer() == false)
				{
					return false;
				}
				printd(_T("createRasaterizerState\n"));
				if (createRasterizerState() == false)
				{
					return false;
				}
				printd(_T("createBlendState\n"));
				if (createBlendState() == false)
				{
					return false;
				}
				printd(_T("createDepthState\n"));
				if (createDepthstate() == false)
				{
					return false;
				}

				printd(_T("createRenderState\n"));
				if (createRenderState() == false)
				{
					return false;
				}

				printd(_T("[GlobalAsset init end]\n"));
				return true;
			}
			bool createConstantBuffer()
			{
				auto device = Core::getInstance()->getDevice();

				auto constantBuffer = instance->getConstantBuffer(GLOBAL_ASSET_CONSTANT_BUFFER_VIEW_PROJECTION);
				if (constantBuffer->create(device, sizeof(viewProjection), 1, nullptr, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE) == false)
				{
					return false;
				}

				return true;
			}
			bool createRasterizerState()
			{
				auto device = Core::getInstance()->getDevice();

				auto rasterizerState = instance->getRasterizerState(GLOBAL_ASSET_RASTERIZER_STATE_CCW_CULL_BACK);
				if (rasterizerState->create(device) == false)
				{
					return false;
				}

				return true;
			}
			bool createBlendState()
			{
				auto device = Core::getInstance()->getDevice();

				auto blendState = instance->getBlendState(GLOBAL_ASSET_BLEND_STATE_RT_ALL_BASIC_ALPHA);
				if (blendState->create(device, {BlendParam::getBasicAlphaBlend()}) == false)
				{
					return false;
				}

				return true;
			}
			bool createDepthstate()
			{
				auto device = Core::getInstance()->getDevice();

				auto depthState = instance->getDepthState(GLOBAL_ASSET_DEPTH_STATE_BASIC_3D);
				if (depthState->create(device) == false)
				{
					return false;
				}

				return true;
			}
			bool createRenderState()
			{
				auto renderState = instance->getRenderState(GLOBAL_ASSET_RENDER_STATE_OPAQUE_BACKBUFFER);
				renderState->m_rasterizerStateID = GLOBAL_ASSET_RASTERIZER_STATE_CCW_CULL_BACK;
				renderState->m_blendStateID = GLOBAL_ASSET_BLEND_STATE_RT_ALL_BASIC_ALPHA;
				renderState->m_depthStateID = GLOBAL_ASSET_DEPTH_STATE_BASIC_3D;
				renderState->m_renderTargetViewIDList = {-1}; // バックバッファ参照
				renderState->m_depthStencilViewID = -1; // バックバッファ参照

				return true;
			}
	};

	GlobalAsset* GlobalAsset::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new GlobalAsset();
		}
		return instance;
	}
	void GlobalAsset::deleteInstance()
	{
		SAFE_DELETE(instance);
	}

	GlobalAsset::GlobalAsset()
	{
		m_impl = std::make_unique<GlobalAsset::Impl>();
	}

	bool GlobalAsset::init()
	{
		return m_impl->init();
	}
}
