#include "Shader.h"

namespace dx
{
	bool VertexShader::create(Object<ID3D11Device> *device)
	{
		if (m_object != nullptr)
		{
			printd(_T("vertex shader already exists"));
			return false;
		}

		auto result = device->handle()->CreateVertexShader(
			m_shaderBlob.handle()->GetBufferPointer(), m_shaderBlob.handle()->GetBufferSize(),
			nullptr, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createvertexshader"), result);
			return false;
		}

		return true;
	}
	void VertexShader::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		deviceContext->handle()->VSSetShader(handle(), nullptr, 0);
	}

	bool PixelShader::create(Object<ID3D11Device> *device)
	{
		if (m_object != nullptr)
		{
			printd(_T("pixel shader already exists"));
			return false;
		}

		auto result = device->handle()->CreatePixelShader(
			m_shaderBlob.handle()->GetBufferPointer(), m_shaderBlob.handle()->GetBufferSize(),
			nullptr, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(_T("device::createpixelshader"), result);
			return false;
		}

		return true;
	}
	void PixelShader::set(Object<ID3D11DeviceContext> *deviceContext)
	{
		deviceContext->handle()->PSSetShader(handle(), nullptr, 0);
	}
}
