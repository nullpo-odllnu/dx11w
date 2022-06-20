#include "Mesh.h"

namespace dx
{
	Mesh::Mesh() : 
		m_vertexNum (0),
		m_indexNum(0),
		m_meshFrontType (MESH_FRONT_COUNTERCLOCKWISE)
	{
	}
	Mesh::~Mesh()
	{
	}
	
	const std::vector<float3>& Mesh::getPosition() const
	{
		return m_position;
	}
	const std::vector<float3>& Mesh::getNormal() const
	{
		return m_normal;
	}
	const std::vector<float2>& Mesh::getTexCoord() const
	{
		return m_texCoord;
	}
	const std::vector<unsigned int>& Mesh::getIndex() const
	{
		return m_index;
	}

	unsigned int Mesh::getVertexNum() const
	{
		return m_vertexNum;
	}
	unsigned int Mesh::getIndexNum() const
	{
		return m_indexNum;
	}

	MESH_FRONT_TYPE Mesh::getMeshFrontType() const
	{
		return m_meshFrontType;
	}
	void Mesh::setMeshFrontType(MESH_FRONT_TYPE meshFrontType)
	{
		m_meshFrontType = meshFrontType;
	}

	void Mesh::storeDirectXTKPrimitive(std::vector<DirectX::VertexPositionNormalTexture> &positionNormalTexture, std::vector<uint16_t> &index)
	{
		m_vertexNum = static_cast<unsigned int>(positionNormalTexture.size());
		for (auto iterator = positionNormalTexture.begin(); iterator != positionNormalTexture.end(); ++iterator)
		{
			m_position.push_back(iterator->position);
			m_normal.push_back(iterator->normal);
			m_texCoord.push_back(iterator->textureCoordinate);
		}

		m_indexNum = static_cast<unsigned int>(index.size());
		for (unsigned int i = 0; i < m_indexNum; i += 3)
		{
			if (m_meshFrontType == MESH_FRONT_COUNTERCLOCKWISE)
			{
				m_index.push_back(index[i + 2]);
				m_index.push_back(index[i + 1]);
				m_index.push_back(index[i + 0]);
			}
			else
			{
				m_index.push_back(index[i + 0]);
				m_index.push_back(index[i + 1]);
				m_index.push_back(index[i + 2]);
			}
		}
	}

	void Mesh::calcBoundingBox()
	{
		m_boundingBox.clear();

		for (auto iterator = m_position.begin(); iterator != m_position.end(); ++iterator)
		{
			m_boundingBox.add(*iterator);
		}
	}
	BoundingBox Mesh::getBoundingBox()
	{
		return m_boundingBox;
	}
}
