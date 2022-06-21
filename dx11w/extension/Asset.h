#pragma once

#include "../Buffer.h"
#include "../Shader.h"
#include "../InputAssembler.h"
#include "../RasterizerState.h"
#include "../OutputManager.h"
#include "../Texture.h"

#include "../float4x4.h"


namespace dx
{
	class RenderState
	{
		public:
			RenderState();
			
			unsigned int m_inputLayoutID;
			std::vector<unsigned int> m_vertexBufferIDList;
			unsigned int m_indexBufferID;
			std::vector<unsigned int> m_constantBufferIDList;
			unsigned int m_vertexShaderID;
			unsigned int m_pixelShaderID;
			D3D11_PRIMITIVE_TOPOLOGY m_primitiveTopology;
			unsigned int m_rasterizerStateID;
			unsigned int m_blendStateID;
			unsigned int m_depthStateID;
			bool m_createViewportFromRenderTarget;
			// std::vector<unsigned int> m_viewportIDList;
			std::vector<int> m_renderTargetViewIDList; // 参照先はTexture2D　-1の場合はバックバッファ参照
			int m_depthStencilViewID; // 参照先はTexture2D　-1の場合はバックバッファ参照
	};

	class Asset
	{
		public:
			Asset();

			VertexBuffer* getVertexBuffer(unsigned int id);
			IndexBuffer* getIndexBuffer(unsigned int id);
			ConstantBuffer* getConstantBuffer(unsigned int id);
			VertexShader* getVertexShader(unsigned int id);
			PixelShader* getPixelShader(unsigned int id);
			InputLayout* getInputLayout(unsigned int id);
			RasterizerState* getRasterizerState(unsigned int id);
			BlendState* getBlendState(unsigned int id);
			DepthState* getDepthState(unsigned int id);
			Texture2D* getTexture2D(unsigned int id);

			RenderState* getRenderState(unsigned int id);

			void begin(Object<ID3D11DeviceContext> *deviceContext, unsigned int renderStateID);
			void end(Object<ID3D11DeviceContext> *deviceContext);

		private:
			Asset(const Asset &asset);
			Asset& operator = (const Asset &asset);

			class Impl;
			std::unique_ptr<Impl> m_impl;
	};

	enum GLOBAL_ASSET
	{
		// ----------------- InputLayout -----------------
		GLOBAL_ASSET_INPUT_LAYOUT = 1000000,

		GLOBAL_ASSET_INPUT_LAYOUT_RESERVED,

		// ----------------- VertexBuffer -----------------
		GLOBAL_ASSET_VERTEX_BUFFER = GLOBAL_ASSET_INPUT_LAYOUT + 1000000,

		GLOBAL_ASSET_VERTEX_BUFFER_RESERVED,

		// ----------------- IndexBuffer -----------------
		GLOBAL_ASSET_INDEX_BUFFER = GLOBAL_ASSET_VERTEX_BUFFER + 1000000,

		GLOBAL_ASSET_INDEX_BUFFER_RESERVED,

		// ----------------- ConstantBuffer -----------------
		GLOBAL_ASSET_CONSTANT_BUFFER = GLOBAL_ASSET_INDEX_BUFFER + 1000000,
		GLOBAL_ASSET_CONSTANT_BUFFER_VIEW_PROJECTION, // ビュー、プロジェクション行列
		GLOBAL_ASSET_CONSTANT_BUFFER_RESERVED,

		// ----------------- VertexShader -----------------
		GLOBAL_ASSET_VERTEX_SHADER = GLOBAL_ASSET_CONSTANT_BUFFER + 1000000,

		GLOBAL_ASSET_VERTEX_SHADER_RESERVED,

		// ----------------- PixelShader -----------------
		GLOBAL_ASSET_PIXEL_SHADER = GLOBAL_ASSET_VERTEX_SHADER + 1000000,

		GLOBAL_ASSET_PIXEL_SHADER_RESERVED,

		// ----------------- RasterizerState -----------------
		GLOBAL_ASSET_RASTERIZER_STATE = GLOBAL_ASSET_PIXEL_SHADER + 1000000,
		GLOBAL_ASSET_RASTERIZER_STATE_CCW_CULL_BACK, // 反時計回りを表面とし、裏面をカリング
		GLOBAL_ASSET_RASTERIZER_STATE_RESERVED,

		// ----------------- BlendState -----------------
		GLOBAL_ASSET_BLEND_STATE = GLOBAL_ASSET_RASTERIZER_STATE + 1000000,
		GLOBAL_ASSET_BLEND_STATE_RT_ALL_BASIC_ALPHA, // すべてのレンダーターゲットを対象に、標準的なアルファブレンド
		GLOBAL_ASSET_BLEND_STATE_RESERVED,

		// ----------------- DepthState -----------------
		GLOBAL_ASSET_DEPTH_STATE = GLOBAL_ASSET_BLEND_STATE + 1000000,
		GLOBAL_ASSET_DEPTH_STATE_BASIC_3D, // 標準3D空間用　深度テストあり / 深度書き込みあり
		GLOBAL_ASSET_DEPTH_STATE_RESERVED,


		// ----------------- RenderState -----------------
		GLOBAL_ASSET_RENDER_STATE = GLOBAL_ASSET_DEPTH_STATE + 1000000,
		GLOBAL_ASSET_RENDER_STATE_OPAQUE_BACKBUFFER, // 不透明を想定、バックバッファを対象
		GLOBAL_ASSET_RENDER_STATE_RESERVED,
	};

	struct viewProjection
	{
		float4x4 view;
		float4x4 projection;
	};

	class GlobalAsset : public Asset
	{
		public:
			static GlobalAsset* getInstance();
			static void deleteInstance();

			bool init();

		private:
			GlobalAsset();
			GlobalAsset(const GlobalAsset &asset);
			GlobalAsset& operator=(const GlobalAsset &asset);

			class Impl;
			std::unique_ptr<Impl> m_impl;
	};
}
