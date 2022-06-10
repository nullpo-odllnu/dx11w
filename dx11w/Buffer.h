#pragma once

namespace dx
{
	class Buffer : public Object<ID3D11Buffer>
	{
		public:
			Buffer();
			virtual ~Buffer();

			// バッファ作成
			// バッファ全体のサイズは、structSize x structNumで規定する
			// 定数バッファ等、CPUアクセスを必要とする場合は
			// 　　usageはD3D11_USAGE_DYNAMIC
			// 　　cpuAccessFlagsはD3D11_CPU_ACCESS_WRITE
			bool create(Object<ID3D11Device>& device,
				unsigned int structSize, unsigned int structNum = 1,
				void *bufferData = nullptr,
				D3D11_USAGE usage = D3D11_USAGE_DEFAULT, 
				unsigned int cpuAccessFlags = 0);

			unsigned int getStructSize() const;
			unsigned int getStructNum() const;

		protected:
			unsigned int m_bindFlags;
			unsigned int m_structSize;
			unsigned int m_structNum;
	};

	class VertexBuffer : public Buffer
	{
		public:
			VertexBuffer();
	};

	class IndexBuffer : public Buffer
	{
		public:
			IndexBuffer();
	};

	class ConstantBuffer : public Buffer
	{
		public:
			ConstantBuffer();

			bool set(Object<ID3D11DeviceContext>& deviceContext, void* bufferData, unsigned int bufferSize);
	};
}
