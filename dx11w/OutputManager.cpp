#include "OutputManager.h"

namespace dx
{
	BlendParam::BlendParam() :
		enable(false),
		srcBlend(D3D11_BLEND_ONE),
		destBlend(D3D11_BLEND_ZERO),
		blendOp(D3D11_BLEND_OP_ADD),
		srcBlendAlpha(D3D11_BLEND_ONE),
		destBlendAlpha(D3D11_BLEND_ZERO),
		blendOpAlpha(D3D11_BLEND_OP_ADD),
		writeMask(D3D11_COLOR_WRITE_ENABLE_ALL)
	{
	}
	BlendParam BlendParam::getBasicAlphaBlend()
	{
		BlendParam blendParam;

		blendParam.enable = true;
		blendParam.srcBlend = D3D11_BLEND_SRC_ALPHA;
		blendParam.destBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendParam.blendOp = D3D11_BLEND_OP_ADD;

		blendParam.srcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendParam.destBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		blendParam.blendOpAlpha = D3D11_BLEND_OP_ADD;

		blendParam.writeMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return blendParam;
	}
	BlendParam BlendParam::getNoneAlphaBlend()
	{
		BlendParam ret;
		return ret;
	}
	BlendParam BlendParam::getAddAlphaBlend()
	{
		BlendParam blendParam;

		blendParam.enable = true;
		blendParam.srcBlend = D3D11_BLEND_SRC_ALPHA;
		blendParam.destBlend = D3D11_BLEND_ONE;
		blendParam.blendOp = D3D11_BLEND_OP_ADD;

		blendParam.srcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendParam.destBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		blendParam.blendOpAlpha = D3D11_BLEND_OP_ADD;

		blendParam.writeMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return blendParam;
	}

	BlendState::BlendState() : Object<ID3D11BlendState>()
	{
	}
	bool BlendState::create(Object<ID3D11Device> *device, std::vector<BlendParam> &blendParamList, bool alphaToCoverage)
	{
		if (m_object != nullptr)
		{
			dx::printd(_T("blend state already existts"));
			return false;
		}

		D3D11_BLEND_DESC blendDescription;
		ZeroMemory(&blendDescription, sizeof(D3D11_BLEND_DESC));
		
		blendDescription.AlphaToCoverageEnable = alphaToCoverage;
		// このフラグは
		// 　　true : 8枚それぞれに設定したブレンディング設定を使用する
		// 　　false : RT8枚全て0番目のブレンディング設定を使用する
		blendDescription.IndependentBlendEnable = blendParamList.size() == 1 ? false : true;
		for (unsigned int i = 0; i < blendParamList.size(); i++)
		{
			blendDescription.RenderTarget[i].BlendEnable = blendParamList[i].enable;
			blendDescription.RenderTarget[i].SrcBlend = blendParamList[i].srcBlend;
			blendDescription.RenderTarget[i].DestBlend = blendParamList[i].destBlend;
			blendDescription.RenderTarget[i].BlendOp = blendParamList[i].blendOp;
			blendDescription.RenderTarget[i].SrcBlendAlpha = blendParamList[i].srcBlendAlpha;
			blendDescription.RenderTarget[i].DestBlendAlpha = blendParamList[i].destBlendAlpha;
			blendDescription.RenderTarget[i].BlendOpAlpha = blendParamList[i].blendOpAlpha;
			blendDescription.RenderTarget[i].RenderTargetWriteMask = blendParamList[i].writeMask;
		}
		auto result = device->handle()->CreateBlendState(&blendDescription, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createblendstate"), result);
			return false;
		}
		return true;
	}
	void BlendState::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		float blendFactor[] =
		{
			0.0f, 0.0f, 0.0f, 0.0f,
		};
		deviceContext->handle()->OMSetBlendState(handle(), blendFactor, 0xffffffff);
	}

	DepthState::DepthState() : 
	Object<ID3D11DepthStencilState>()
	{
	}
	bool DepthState::create(Object<ID3D11Device> *device, bool enable, D3D11_DEPTH_WRITE_MASK depthWriteMask, D3D11_COMPARISON_FUNC comparisonFunction)
	{
		if (m_object != nullptr)
		{
			dx::printd(_T("depth state already exists"));
			return false;
		}

		D3D11_DEPTH_STENCIL_DESC depthStencilDescription;
		depthStencilDescription.DepthEnable = enable;
		depthStencilDescription.DepthWriteMask = depthWriteMask;
		depthStencilDescription.DepthFunc = comparisonFunction;
		depthStencilDescription.StencilEnable = false;
		depthStencilDescription.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		depthStencilDescription.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		depthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		auto result = device->handle()->CreateDepthStencilState(&depthStencilDescription, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createdepthstencilstate"), result);
			return false;
		}
		return true;
	}
	void DepthState::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		deviceContext->handle()->OMSetDepthStencilState(handle(), 0);
	}
}
