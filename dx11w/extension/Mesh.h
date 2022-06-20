#pragma once

#include "../float2.h"
#include "../float3.h"
#include "../BoundingBox.h"
#include <vector>

namespace DirectX
{
	struct VertexPositionNormalTexture;
}
namespace dx
{
	// 頂点座標構成順序
	enum MESH_FRONT_TYPE
	{
		// 時計回り
		MESH_FRONT_CLOCKWISE,
		// 反時計回り
		MESH_FRONT_COUNTERCLOCKWISE,
	};

	class Mesh
	{
		public:
			Mesh();
			virtual ~Mesh();

			const std::vector<float3>& getPosition() const;
			const std::vector<float3>& getNormal() const;
			const std::vector<float2>& getTexCoord() const;
			const std::vector<unsigned int>& getIndex() const;

			unsigned int getVertexNum() const;
			unsigned int getIndexNum() const;

			MESH_FRONT_TYPE getMeshFrontType() const;
			void setMeshFrontType(MESH_FRONT_TYPE meshFrontType);

			void calcBoundingBox();
			BoundingBox getBoundingBox();

		protected:
			unsigned int m_vertexNum;
			std::vector<float3> m_position;
			std::vector<float3> m_normal;
			std::vector<float2> m_texCoord;

			unsigned int m_indexNum;
			std::vector<unsigned int> m_index;

			BoundingBox m_boundingBox;
			
			MESH_FRONT_TYPE m_meshFrontType;

			void storeDirectXTKPrimitive(std::vector<DirectX::VertexPositionNormalTexture> &positionNormalTextureList, std::vector<uint16_t> &index);
	};
}
