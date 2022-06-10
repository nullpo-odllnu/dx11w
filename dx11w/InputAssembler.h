#pragma once

namespace dx
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexShader;

	void setIndexBuffer(Object<ID3D11DeviceContext> &deviceContext,
		IndexBuffer &indexBuffer,
		DXGI_FORMAT indexFormat = DXGI_FORMAT_R32_UINT);

	#define INPUT_ELEMENT(semanticsName, semanticsIndex, format, inputSlotIndex, dataOffset, dataType, instanceNo) {semanticsName, semanticsIndex, format, inputSlotIndex, dataOffset, dataType, instanceNo}
	#define INPUT_ELEMENT_POSITION_XYZ(semanticsIndex, inputSlotIndex) INPUT_ELEMENT("POSITION", semanticsIndex, DXGI_FORMAT_R32G32B32_FLOAT, inputSlotIndex, 0, D3D11_INPUT_PER_VERTEX_DATA, 0)
	#define INPUT_ELEMENT_TEXCOORD_UV(semanticsIndex, inputSlotIndex) INPUT_ELEMENT("TEXCOORD", semanticsIndex, DXGI_FORMAT_R32G32_FLOAT, inputSlotIndex, 0, D3D11_INPUT_PER_VERTEX_DATA, 0)

	class InputLayout : public Object<ID3D11InputLayout>
	{
		public:
			InputLayout();

			bool create(Object<ID3D11Device> &device, std::vector<D3D11_INPUT_ELEMENT_DESC> &inputElementDescriptionList, VertexShader &vertexShader);

			void set(Object<ID3D11DeviceContext> &deviceContext);
	};
	
	void setPrimitiveTopology(Object<ID3D11DeviceContext> &deviceContext,
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
