#pragma once

namespace dx
{
	class RasterizerState : public Object<ID3D11RasterizerState>
	{
		public:
			RasterizerState();

			// �����v����\�ʂƂ��A�w�ʂ̓J�����O����
			bool create(Object<ID3D11Device> &device,
				D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID,
				D3D11_CULL_MODE cullMode = D3D11_CULL_BACK,
				bool frontCounterClockwise = true,
				bool multiSample = false,
				bool antiAliasedLine = false);

			void set(Object<ID3D11DeviceContext> &deviceContext);
	};
}
