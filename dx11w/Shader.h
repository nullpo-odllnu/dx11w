#pragma once

namespace dx
{
	template <typename Type>
	class Shader : public Object<Type>
	{
		protected:
			Object<ID3DBlob> m_shaderBlob;
			Object<ID3DBlob> m_errorBlob;

		public:
			Shader() : Object<Type>()
			{
			}
			virtual ~Shader()
			{
			}

			// ファイルからコンパイル
			// optionは旧書式の禁止と列優先(高速化のため)
			bool compileFromFile(const tstring &shaderFilepath, 
				const std::string &functionName,
				const std::string &profile,
#ifdef _DEBUG
				unsigned int options = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_DEBUG
#else
				unsigned int options = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR
#endif
				)
			{
				auto result = D3DX11CompileFromFile(shaderFilepath.c_str(), nullptr, nullptr,
					functionName.c_str(), profile.c_str(), options, 0, nullptr, 
					m_shaderBlob.pointer(), m_errorBlob.pointer(), nullptr);
				if (FAILED(result))
				{
					auto errorMessage(static_cast<TCHAR*>(m_errorBlob.handle()->GetBufferPointer()));
					printd(errorMessage);
					m_errorBlob.release();
					DXTRACE_ERR_MSGBOX(L"d3dx11compilefromfile", result);

					return false;
				}
				return true;
			}
			// メモリからコンパイル
			// optionは旧書式の禁止と列優先(高速化のため)
			HRESULT compileFromMemory(const TCHAR *shaderCode, 
				const std::string &functionName,
				const std::string &profile,
#ifdef _DEBUG
				unsigned int options = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_DEBUG
#else
				unsigned int options = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR
#endif
				)
			{
				auto result = D3DX11CompileFromMemory(shaderCode, _tcslen(shaderCode), nullptr, nullptr, nullptr,
					functionName.c_str(), profile.c_str(), options, 0, nullptr, 
					m_shaderBlob.pointer(), m_errorBlob.pointer, nullptr);
				if (FAILED(result))
				{
					auto errorMessage(static_cast<TCHAR*>(m_errorBlob.handle()->GetBufferPointer()));
					printd(errorMessage);
					m_errorBlob.release();
					DXTRACE_ERR_MSGBOX(L"d3dx11compilefrommemory", result);

					return false;
				}
				return true;
			}

			Object<ID3DBlob>& getShaderBlob()
			{
				return m_shaderBlob;
			}

			virtual bool create(Object<ID3D11Device>& device)
			{
				return true;
			}
			virtual void set(Object<ID3D11DeviceContext> &deviceContext)
			{
			}
	};

	class VertexShader : public Shader<ID3D11VertexShader>
	{
		public:
			bool create(Object<ID3D11Device> &device);
			void set(Object<ID3D11DeviceContext>& deviceContext);
	};

	class PixelShader : public Shader<ID3D11PixelShader>
	{
		public:
			bool create(Object<ID3D11Device>& device);
			void set(Object<ID3D11DeviceContext>& deviceContext);
	};
}
