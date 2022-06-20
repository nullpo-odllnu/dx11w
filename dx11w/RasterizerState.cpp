#include "RasterizerState.h"

#include "float2.h"

namespace dx
{
	RasterizerState::RasterizerState() : Object<ID3D11RasterizerState>()
	{
	}

	bool RasterizerState::create(Object<ID3D11Device> *device, 
		D3D11_FILL_MODE fillMode,
		D3D11_CULL_MODE cullMode,
		bool frontCounterClockwise,
		bool multisample,
		bool antiAliasedLine)
	{
		if (m_object != nullptr)
		{
			dx::printd(_T("rasterizer state already exists"));
			return false;
		}

		D3D11_RASTERIZER_DESC rasterizerDescription;
		rasterizerDescription.FillMode = fillMode;
		rasterizerDescription.CullMode = cullMode;
		rasterizerDescription.FrontCounterClockwise = frontCounterClockwise;
		rasterizerDescription.DepthBias = 0;
		rasterizerDescription.DepthBiasClamp = 0.0f;
		rasterizerDescription.SlopeScaledDepthBias = 0.0f;
		rasterizerDescription.DepthClipEnable = false;
		rasterizerDescription.ScissorEnable = false;
		rasterizerDescription.MultisampleEnable = multisample;
		rasterizerDescription.AntialiasedLineEnable = antiAliasedLine;

		auto result = device->handle()->CreateRasterizerState(&rasterizerDescription, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createrasterizerstate"), result);
			return false;
		}
		return true;
	}
	
	void RasterizerState::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		deviceContext->handle()->RSSetState(handle());
	}

	Viewport::Viewport() : 
		D3D11_VIEWPORT()
	{
		TopLeftX = 0.0f;
		TopLeftY = 0.0f;
		MinDepth = 0.0f;
		MaxDepth = 1.0f;
	}
	Viewport::Viewport(unsigned int width, unsigned int height) : D3D11_VIEWPORT()
	{
		TopLeftX = 0.0f;
		TopLeftY = 0.0f;
		Width = static_cast<float>(width);
		Height = static_cast<float>(height);
		MinDepth = 0.0f;
		MaxDepth = 1.0f;
	}
	Viewport::Viewport(const float2& size) : D3D11_VIEWPORT()
	{
		TopLeftX = 0.0f;
		TopLeftY = 0.0f;
		Width = size.x;
		Height = size.y;
		MinDepth = 0.0f;
		MaxDepth = 1.0f;
	}
}
