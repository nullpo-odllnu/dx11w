#pragma once

#include "RasterizerState.h"
#include "float2.h"
#include "float4.h"

namespace dx
{
	template <typename Type>
	class Texture
	{
		public:
			Texture() : 
				m_mipmapLevels (0), m_bindFlags (0),
				m_width (0), m_height (0)
			{
			}

			// 2次元テクスチャリソースとして作成
			// シェーダリソースとして作るなら
			// 　　bindFlags = D3D11_BIND_SHADER_RESOURCE
			// レンダーターゲットとして作るなら
			// 　　bindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET
			// 深度バッファとして作るなら
			// 　　bindFlags = D3D11_BIND_DEPTH_STENCIL
			bool createTexture2D(Object<ID3D11Device> &device,
				unsigned int width, unsigned int height,
				DXGI_FORMAT format,
				unsigned int bindFlags,
				D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
				unsigned int cpuAccessFlags = 0,
				unsigned int mipLevel = 1,
				unsigned int sampleCount = 1,
				unsigned int sampleQuality = 0)
			{
				if (m_resource.handle() != nullptr)
				{
					dx::printd(_T("texture already exist\n"));
					return false;
				}

				D3D11_TEXTURE2D_DESC textureDescription;
				m_format = format;
				m_bindFlags = bindFlags;
				m_mipmapLevels = mipLevel;
				m_width = width;
				m_height = height;

				textureDescription.Width = m_width;
				textureDescription.Height = m_height;
				textureDescription.MipLevels = m_mipmapLevels;
				textureDescription.ArraySize = 1;
				textureDescription.Format = m_format;
				textureDescription.SampleDesc.Count = sampleCount;
				textureDescription.SampleDesc.Quality = sampleQuality;
				textureDescription.Usage = usage;
				textureDescription.BindFlags = m_bindFlags;
				textureDescription.CPUAccessFlags = cpuAccessFlags;
				textureDescription.MiscFlags = 0;

				auto result = device.handle()->CreateTexture2D(&textureDescription, nullptr, m_resource.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createtexture2d"), result);
					return false;
				}
				return true;
			}
			// 画像ファイルからシェーダリソースビュー作成
			bool createShaderResourceViewFromFile(Object<ID3D11Device> &device, const tstring &filePath)
			{
				if (m_shaderResourceView.handle() != nullptr)
				{
					dx::printd(_T("shader resource view already exist\n"));
					return false;
				}

				auto result = D3DX11CreateShaderResourceViewFromFile(device.handle(),
					filePath.c_str(),
					nullptr, nullptr, 
					m_shaderResourceView.pointer(),
					nullptr);

				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("D3DX11CreateShaderResourceViewFromFile"), result);
					return false;
				}
				else
				{
					m_shaderResourceView.handle()->GetResource(m_resource.pointer());
					D3D11_TEXTURE2D_DESC textureDescription;
					m_resource->GetDesc(&textureDescription);
					m_bindFlags = textureDescription.BindFlags;
					m_format = textureDescription.Format;
					m_mipmapLevels = textureDescription.MipLevels;
					m_width = textureDescription.Width;
					m_height = textureDescription.Height;
				}
				return true;
			}
			// メモリからシェーダリソースビュー作成
			bool createShaderResourceViewFromMemory(Object<ID3D11Device> &device, void *data, unsigned int size)
			{
				if (m_shaderResourceView.handle() != nullptr)
				{
					dx::printd(_T("shader resource view already exist.\n"));
				}
				auto result = D3DX11CreateShaderResourceViewFromMemory(device.handle(), data, size, 
					nullptr, nullptr, m_shaderResourceView.pointer(), nullptr);

				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("D3DX11CreateShaderResourceViewFromMemory"), result);
					return false;
				}
				else
				{
					m_shaderResourceView.handle()->GetResource(m_resource.pointer());
					D3D11_TEXTURE2D_DESC textureDescription;
					m_resource->GetDesc(&textureDescription);
					m_bindFlags = textureDescription.BindFlags;
					m_format = textureDescription.Format;
					m_mipmapLevels = textureDescription.MipLevels;
					m_width = textureDescription.Width;
					m_height = textureDescription.Height;
				}

				return true;
			}

			// 作成済みテクスチャからシェーダリソースビューを作成
			bool createShaderResourceViewFromCreatedTexture2D(Object<ID3D11Device> &device)
			{
				if (m_shaderResourceView.handle() != nullptr)
				{
					dx::printd(_T("shader resource view already exist\n"));
					return false;
				}
				// シェーダリソースとしてバインドしていないものは許可しない
				if ((m_bindFlags & D3D11_BIND_SHADER_RESOURCE) == 0)
				{
					dx::printd(_T("Texture2D must be have D3D11_BIND_SHADER_RESOURCE flag\n"));
					return false;
				}
				D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDescription;
				shaderResourceViewDescription.Format = m_format;
				shaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				shaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
				shaderResourceViewDescription.Texture2D.MipLevels = m_mipmapLevels;
				
				auto result = device.handle()->CreateShaderResourceView(m_resource.handle(), &shaderResourceViewDescription, m_shaderResourceView.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createshaderresourceview"), result);
					return false;
				}
				return true;
			}
			// 作成済みテクスチャからレンダーターゲットビューを作成
			bool createRenderTargetViewFromCreatedTexture2D(Object<ID3D11Device> &device)
			{
				if (m_renderTargetView.handle() != nullptr)
				{
					dx::printd(_T("render target view already exist\n"));
					return false;
				}
				// レンダーターゲットとしてバインドしていないものは許可しない
				if ((m_bindFlags & D3D11_BIND_RENDER_TARGET) == 0)
				{
					dx::printd(_T("Texture2D must be have D3D11_BIND_RENDER_TARGET flag\n"));
					return false;
				}
				D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescription;
				renderTargetViewDescription.Format = m_format;
				renderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				renderTargetViewDescription.Texture2D.MipSlice = 0;

				auto result = device.handle()->CreateRenderTargetView(m_resource.handle(), &renderTargetViewDescription, m_renderTargetView.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createrendertargetview"), result);
					return false;
				}
				return true;
			}
			// 作成済みテクスチャから深度バッファ作成
			bool createDepthStencilViewFromCreatedTexture2D(Object<ID3D11Device> &device)
			{
				if (m_depthStencilView.handle() != nullptr)
				{
					dx::printd(_T("depth stencil view already exist\n"));
					return false;
				}
				// 深度バッファとしてバインドしていないものは許可しない
				if ((m_bindFlags & D3D11_BIND_DEPTH_STENCIL) == 0)
				{
					dx::printd(_T("Texture2D must be have D3D11_BIND_DEPTH_STENCIL flag\n"));
					return false;
				}
				D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription;
				depthStencilViewDescription.Format = m_format;
				depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilViewDescription.Flags = 0;
				depthStencilViewDescription.Texture2D.MipSlice = 0;

				auto result = device.handle()->CreateDepthStencilView(m_resource.handle(), &depthStencilViewDescription, m_depthStencilView.pointer());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("device::createdepthstencilview"), result);
					return false;
				}
				return true;
			}

			Object<Type>& getTextureResource() const
			{
				return m_resource;
			}
			Object<ID3D11ShaderResourceView>& getShaderResourceView() const
			{
				return m_shaderResourceView;
			}
			Object<ID3D11RenderTargetView>& getRenderTargetView() const
			{
				return m_renderTargetView;
			}
			Object<ID3D11DepthStencilView>& getDepthStencilView() const
			{
				return m_depthStencilView;
			}
			unsigned int getWidth() const
			{
				return m_width;
			}
			unsigned int getHeight() const
			{
				return m_height;
			}
			float2 getSize() const
			{
				return float2(static_cast<float>(m_width), static_cast<float>(m_height));
			}
			Viewport getViewport()
			{
				return Viewport(m_width, m_height);
			}
			// 1ピクセルあたりのUV推移量取得
			float2 getDeltaCoord() const
			{
				return float2(1.0f / static_cast<float>(m_width), 1.0f / static_cast<float>(m_height));
			}

			// レンダーターゲットビュークリア
			void clearRenderTargetView(Object<ID3D11DeviceContext> &deviceContext, float4 clearColor = float4(0.0f))
			{
				if (m_renderTargetView.handle() == nullptr)
				{
					return;
				}
				deviceContext.handle()->ClearRenderTargetView(m_renderTargetView.handle(), clearColor);
			}
			// 深度バッファビューのクリア
			void clearDepthStencilView(Object<ID3D11DeviceContext> &deviceContext, float clearDepthValue = 1.0f, unsigned int clearFlag = D3D11_CLEAR_DEPTH)
			{
				if (m_depthStencilView.handle() == nullptr)
				{
					return;
				}
				deviceContext.handle()->ClearDepthStencilView(m_depthStencilView.handle(), clearFlag, clearDepthValue, 0);
			}

			// ファイル出力
			bool writeTextureToFile(Object<ID3D11DeviceContext> &deviceContext, const tstring &filePath, D3DX11_IMAGE_FILE_FORMAT fileFormat = D3DX11_IFF_JPG)
			{
				auto result = D3DX11SaveTextureToFile(deviceContext.handle(), m_resource.handle(), fileFormat, filePath.c_str());
				if (FAILED(result))
				{
					DXTRACE_ERR_MSGBOX(_T("D3DX11SaveTextureToFile"), result);
					return false;
				}
				return true;
			}

		private:			
			Object<Type> m_resource;
			Object<ID3D11ShaderResourceView> m_shaderResourceView;
			Object<ID3D11RenderTargetView> m_renderTargetView;
			Object<ID3D11DepthStencilView> m_depthStencilView;

			DXGI_FORMAT m_format;
			unsigned int m_mipmapLevels;
			unsigned int m_bindFlags;

			unsigned int m_width;
			unsigned int m_height;
	};

	typedef dx::Texture<ID3D11Texture2D> Texture2D;
}
