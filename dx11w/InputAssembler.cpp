#include "InputAssembler.h"
#include "Buffer.h"
#include "Shader.h"

namespace dx
{
	void setIndexBuffer(Object<ID3D11DeviceContext> *deviceContext, IndexBuffer *indexBuffer, DXGI_FORMAT indexFormat)
	{
		deviceContext->handle()->IASetIndexBuffer(indexBuffer->handle(), indexFormat, 0);
	}

	InputLayout::InputLayout() : Object<ID3D11InputLayout>()
	{
	}

	bool InputLayout::create(Object<ID3D11Device> *device, std::vector<D3D11_INPUT_ELEMENT_DESC> &inputElementDescriptionList, VertexShader &vertexShader)
	{
		if (m_object != nullptr)
		{
			printd(_T("input layout already exists"));
			return false;
		}

		auto shaderBlob = vertexShader.getShaderBlob();
		auto result = device->handle()->CreateInputLayout(inputElementDescriptionList.data(),
			static_cast<unsigned int>(inputElementDescriptionList.size()),
			shaderBlob->handle()->GetBufferPointer(),
			shaderBlob->handle()->GetBufferSize(),
			pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createinputlayout"), result);
			return false;
		}
		return true;
	}

	void InputLayout::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		deviceContext->handle()->IASetInputLayout(handle());
	}

	void setPrimitiveTopology(Object<ID3D11DeviceContext> *deviceContext, D3D_PRIMITIVE_TOPOLOGY primitiveTopology)
	{
		deviceContext->handle()->IASetPrimitiveTopology(primitiveTopology);
	}
}
