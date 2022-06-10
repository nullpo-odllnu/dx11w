#include "Buffer.h"

namespace dx
{
	Buffer::Buffer() : 
		Object<ID3D11Buffer>(),
		m_bindFlags(0),
		m_structSize(0),
		m_structNum(0)
		{
		}
	Buffer::~Buffer()
	{
	}

	bool Buffer::create(Object<ID3D11Device> &device, unsigned int structSize, unsigned int structNum, void *bufferData, D3D11_USAGE usage, unsigned int cpuAccessFlags)
	{
		// Šù‚Éì¬Ï‚Ý‚Ìê‡Aì¬Ž¸”s‚Æ‚·‚é
		if (m_object != nullptr)
		{
			dx::printd(_T("buffer already exists"));
			return false;
		}

		m_structSize = structSize;
		m_structNum = structNum;

		D3D11_BUFFER_DESC bufferDescription;
		bufferDescription.Usage = usage;
		bufferDescription.ByteWidth = m_structSize * m_structNum;
		bufferDescription.BindFlags = m_bindFlags;
		bufferDescription.CPUAccessFlags = cpuAccessFlags;
		bufferDescription.MiscFlags = 0;
		bufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subResourceData;
		if (bufferData != nullptr)
		{
			subResourceData.pSysMem = bufferData;
			subResourceData.SysMemPitch = 0;
			subResourceData.SysMemSlicePitch = 0;
		}

		HRESULT result = device.handle()->CreateBuffer(&bufferDescription, 
			bufferData != nullptr ? &subResourceData : nullptr, pointer());
		if (FAILED(result))
		{
			DXTRACE_ERR_MSGBOX(L"device::createbuffer", result);
			return false;
		}
		return true;
	}

	bool ConstantBuffer::set(Object<ID3D11DeviceContext> &deviceContext, void* bufferData, unsigned int bufferSize)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		auto result = deviceContext.handle()->Map(handle(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
		if (FAILED(result))
		{
			printd(_T("devicecontext::map"));
			return false;
		}

		memcpy_s(mappedSubresource.pData, bufferSize, bufferData, bufferSize);

		deviceContext.handle()->Unmap(handle(), 0);

		return true;
	}

	unsigned int Buffer::getStructSize() const
	{
		return m_structSize;
	}
	unsigned int Buffer::getStructNum() const
	{
		return m_structNum;
	}

	VertexBuffer::VertexBuffer()
	{
		m_bindFlags = D3D11_BIND_VERTEX_BUFFER;
	}

	IndexBuffer::IndexBuffer()
	{
		m_bindFlags = D3D11_BIND_INDEX_BUFFER;
	}

	ConstantBuffer::ConstantBuffer()
	{
		m_bindFlags = D3D11_BIND_CONSTANT_BUFFER;
	}
} // namespace dx
