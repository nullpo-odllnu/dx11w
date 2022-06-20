#pragma once

namespace dx
{
	class RasterizerState : public Object<ID3D11RasterizerState>
	{
		public:
			RasterizerState();

			// 反時計回りを表面とし、背面はカリングする
			bool create(Object<ID3D11Device> &device,
				D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID,
				D3D11_CULL_MODE cullMode = D3D11_CULL_BACK,
				bool frontCounterClockwise = true,
				bool multiSample = false,
				bool antiAliasedLine = false);

			void set(Object<ID3D11DeviceContext> &deviceContext);
	};

	class float2;

	class Viewport : public D3D11_VIEWPORT
	{
		public:
			Viewport();
			Viewport(unsigned int width, unsigned int height);
			Viewport(const float2 &size);
	};
}
