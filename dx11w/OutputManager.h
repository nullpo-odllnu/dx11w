#pragma once

namespace dx
{
	struct BlendParam
	{
		public:
			bool enable;
			D3D11_BLEND srcBlend;
			D3D11_BLEND destBlend;
			D3D11_BLEND_OP blendOp;
			D3D11_BLEND srcBlendAlpha;
			D3D11_BLEND destBlendAlpha;
			D3D11_BLEND_OP blendOpAlpha;
			unsigned int writeMask;

		BlendParam();

		// 標準的なアルファブレンディング
		static BlendParam getBasicAlphaBlend();
		// アルファブレンディングなし
		static BlendParam getNoneAlphaBlend();
		// 加算アルファブレンディング
		static BlendParam getAddAlphaBlend();
	};

	class BlendState : public Object<ID3D11BlendState>
	{
		public:
			BlendState();

			bool create(Object<ID3D11Device> *device, std::vector<BlendParam> &blendParamList, bool alphaToCoverage = false);
			void set(Object<ID3D11DeviceContext> *deviceContext);
	};

	class DepthState : public Object<ID3D11DepthStencilState>
	{
		public:
			DepthState();

			bool create(Object<ID3D11Device> *device, 
				bool enable = true, 
				D3D11_DEPTH_WRITE_MASK depthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
				D3D11_COMPARISON_FUNC comparisonFunction = D3D11_COMPARISON_LESS);
			void set(Object<ID3D11DeviceContext> *deviceContext);
	};
}
