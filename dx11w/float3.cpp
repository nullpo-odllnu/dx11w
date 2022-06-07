#include "float3.h"

#include "float2.h"
#include "float4.h"
#include "float4x4.h"

namespace dx
{
	float3::float3() : 
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	{
	}
	float3::float3(float src) : 
		XMFLOAT3(src, src, src)
	{
	}
	float3::float3(float x, float y, float z) : 
		XMFLOAT3(x, y, z)
	{
	}
	float3::float3(int x, int y, int z) : 
		XMFLOAT3((float)x, (float)y, (float)z)
	{
	}
	float3::float3(const float2 &vector, float z) : 
		XMFLOAT3(vector.x, vector.y, z)
	{
	}
	float3::float3(const float3 &vector) : 
		XMFLOAT3(vector.x, vector.y, vector.z)
	{
	}
	float3::float3(const XMFLOAT3 &value) :
		XMFLOAT3(value)
	{
	}

	float3& float3::operator = (float src)
	{
		this->x = src;
		this->y = src;
		this->z = src;

		return *this;
	}
	float3& float3::operator = (const float3 &vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;

		return *this;
	}

	float3 float3::operator + (float src)
	{
		return float3(this->x + src, this->y + src, this->z + src);
	}
	float3 float3::operator + (const float3 &vector)
	{
		return float3(this->x + vector.x, this->y + vector.y, this->z + vector.z);
	}
	float3& float3::operator += (float src)
	{
		this->x += src;
		this->y += src;
		this->z += src;

		return *this;
	}
	float3& float3::operator += (const float3 &vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		this->z += vector.z;

		return *this;
	}

	float3 float3::operator - (float src)
	{
		return float3(this->x - src, this->y - src, this->z - src);
	}
	float3 float3::operator - (const float3 &vector)
	{
		return float3(this->x - vector.x, this->y - vector.y, this->z - vector.z);
	}
	float3& float3::operator -= (float src)
	{
		this->x -= src;
		this->y -= src;
		this->z -= src;

		return *this;
	}
	float3& float3::operator -= (const float3 &vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		this->z -= vector.z;

		return *this;
	}

	float3 float3::operator * (float src)
	{
		return float3(this->x * src, this->y * src, this->z * src);
	}
	float3 float3::operator * (const float3 &vector)
	{
		return float3(this->x * vector.x, this->y * vector.y, this->z * vector.z);
	}
	float3 float3::operator * (const float4x4 &matrix)
	{
		return storefloat3(XMVector3Transform(loadfloat3(*this), loadfloat4x4(matrix)));
	}
	float3& float3::operator *= (float src)
	{
		this->x *= src;
		this->y *= src;
		this->z *= src;
	
		return *this;
	}
	float3& float3::operator *= (const float3 &vector)
	{
		this->x *= vector.x;
		this->y *= vector.y;
		this->z *= vector.z;
	
		return *this;
	}
	float3& float3::operator *= (const float4x4 &matrix)
	{
		*this = storefloat3(XMVector3Transform(loadfloat3(*this), loadfloat4x4(matrix)));
		return *this;
	}

	float3 float3::operator / (float src)
	{
		return float3(this->x / src, this->y / src, this->z / src);
	}
	float3 float3::operator / (const float3 &vector)
	{
		return float3(this->x / vector.x, this->y / vector.y, this->z / vector.z);
	}
	float3& float3::operator /= (float src)
	{
		this->x /= src;
		this->y /= src;
		this->z /= src;

		return *this;
	}
	float3& float3::operator /= (const float3 &vector)
	{
		this->x /= vector.x;
		this->y /= vector.y;
		this->z /= vector.z;

		return *this;
	}

	float length(const float3 &vector)
	{
		return storefloat3(XMVector3Length(loadfloat3(vector))).x;
	}
	
	float3 normalize(const float3 &vector)
	{
		return storefloat3(XMVector3Normalize(loadfloat3(vector)));
	}
	
	float dot(const float3 &vec1, const float3 &vec2)
	{
		return storefloat3(XMVector3Dot(loadfloat3(vec1), loadfloat3(vec2))).x;
	}
	
	float3 cross(const float3 &vec1, const float3 &vec2)
	{
		return storefloat3(XMVector3Cross(loadfloat3(vec1), loadfloat3(vec2)));
	}	

	float3 vectorUp()
	{
		return float3(0.0f, 1.0f, 0.0f);
	}

	float3 vectorFront()
	{
		return float3(0.0f, 0.0f, 1.0f);
	}

	XMVECTOR loadfloat3(const float3 &vector)
	{
		return XMLoadFloat3(&vector);
	}
	float3 storefloat3(const XMVECTOR &vector)
	{
		float3 ret;
		XMStoreFloat3(&ret, vector);
		return ret;
	}

	float3::operator float * ()
	{
		return &x;
	}
} // namespace dx
