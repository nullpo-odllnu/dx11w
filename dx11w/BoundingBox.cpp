#include "BoundingBox.h"

namespace dx
{
	BoundingBox::BoundingBox() : 
		DirectX::BoundingBox()
	{
		clear();
	}
	BoundingBox::BoundingBox(const float3 &min, const float3 &max) :
		DirectX::BoundingBox()
	{
		clear();

		m_min = min;
		m_max = max;
		Center = (m_max + m_min) / 2.0f;
		Extents = m_max - m_min;
	}
	BoundingBox::BoundingBox(const BoundingBox& box) :
		DirectX::BoundingBox()
	{
		m_min = box.m_min;
		m_max = box.m_max;
		Extents = box.Extents;
		Center = box.Center;
	}

	void BoundingBox::add(const float3 &point)
	{

		if (point.x < m_min.x)
		{
			m_min.x = point.x;
		}
		if (point.y < m_min.y)
		{
			m_min.y = point.y;
		}
		if (point.z < m_min.z)
		{
			m_min.z = point.z;
		}
		if (point.x > m_max.x)
		{
			m_max.x = point.x;
		}
		if (point.y > m_max.y)
		{
			m_max.y = point.y;
		}
		if (point.z > m_max.z)
		{
			m_max.z = point.z;
		}

		Center = (m_max + m_min) / 2.0f;
		Extents = m_max - m_min;
	}
	void BoundingBox::add(const std::vector<float3> &pointList)
	{
		for (auto i = pointList.begin(); i != pointList.end(); ++i)
		{
			add(*i);
		}
	}
	void BoundingBox::add(const BoundingBox &boundingBox)
	{
		add(boundingBox.getMin());
		add(boundingBox.getMax());
	}

	void BoundingBox::clear()
	{
		m_min = float3(FLT_MAX);
		m_max = float3(-FLT_MAX);
		Center = float3();
		Extents = float3();
	}

	float3 BoundingBox::getSize() const
	{
		return Extents;
	}
	float3 BoundingBox::getCenter() const 
	{
		return Center;
	}
	float BoundingBox::getRadius() const 
	{
		return length(float3(Extents)) / 2.0f;
	}
	float3 BoundingBox::getMin() const
	{
		return m_min;
	}
	float3 BoundingBox::getMax() const
	{
		return m_max;
	}
}
