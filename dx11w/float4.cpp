#include "float4.h"

#include "float2.h"
#include "float3.h"
#include "float4x4.h"

namespace dx
{
	float4::float4() : 
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	{
	}
	float4::float4(float src) : 
		XMFLOAT4(src, src, src, src)
	{
	}
	float4::float4(float x, float y, float z, float w) : 
		XMFLOAT4(x, y, z, w)
	{
	}
	float4::float4(const float2 &vector, float z, float w) : 
		XMFLOAT4(vector.x, vector.y, z, w)
	{
	}
	float4::float4(const float3 &vector, float w) : 
		XMFLOAT4(vector.x, vector.y, vector.z, w)
	{
	}
	float4::float4(const float4 &vector) : 
		XMFLOAT4(vector.x, vector.y, vector.z, vector.w)
	{
	}
	float4::float4(const XMFLOAT4 &value) :
		XMFLOAT4(value)
	{
	}

	float4& float4::operator = (float src)
	{
		this->x = src;
		this->y = src;
		this->z = src;
		this->w = src;

		return *this;
	}
	float4& float4::operator = (const float4 &data)
	{
		this->x = data.x;
		this->y = data.y;
		this->z = data.z;
		this->w = data.w;

		return *this;
	}

	float4 float4::operator + (float src)
	{
		return float4(this->x + src, this->y + src, this->z + src, this->w + src);
	}
	float4 float4::operator + (const float4 &vector)
	{
		return float4(this->x + vector.x, this->y + vector.y, this->z + vector.z, this->w + vector.w);
	}
	float4& float4::operator += (float src)
	{
		this->x += src;
		this->y += src;
		this->z += src;
		this->w += src;

		return *this;
	}
	float4& float4::operator += (const float4 &vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		this->z += vector.z;
		this->w += vector.w;

		return *this;
	}
			
	float4 float4::operator - (float src)
	{
		return float4(this->x - src, this->y - src, this->z - src, this->w - src);
	}
	float4 float4::operator - (const float4 &vector)
	{
		return float4(this->x - vector.x, this->y - vector.y, this->z - vector.z, this->w - vector.w);
	}
	float4& float4::operator -= (float src)
	{
		this->x -= src;
		this->y -= src;
		this->z -= src;
		this->w -= src;

		return *this;
	}
	float4& float4::operator -= (const float4 &vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		this->z -= vector.z;
		this->w -= vector.w;

		return *this;
	}

	float4 float4::operator * (float src)
	{
		return float4(this->x * src, this->y * src, this->z * src, this->w * src);
	}
	float4 float4::operator * (const float4 &vector)
	{
		return float4(this->x * vector.x, this->y * vector.y, this->z * vector.z, this->w * vector.w);
	}
	float4 float4::operator * (const float4x4 &matrix)
	{
		return storefloat4(XMVector4Transform(loadfloat4(*this), loadfloat4x4(matrix)));
	}
	float4& float4::operator *= (float src)
	{
		this->x *= src;
		this->y *= src;
		this->z *= src;
		this->w *= src;

		return *this;
	}
	float4& float4::operator *= (const float4 &vector)
	{
		this->x *= vector.x;
		this->y *= vector.y;
		this->z *= vector.z;
		this->w *= vector.w;

		return *this;
	}
	float4& float4::operator *= (const float4x4 &matrix)
	{
		*this = storefloat4(XMVector4Transform(loadfloat4(*this), loadfloat4x4(matrix)));
		return *this;
	}

	float4 float4::operator / (float src)
	{
		return float4(this->x / src, this->y / src, this->z / src, this->w / src);
	}
	float4 float4::operator / (const float4 &vector)
	{
		return float4(this->x / vector.x, this->y / vector.y, this->z / vector.z, this->w / vector.w);
	}
	float4& float4::operator /= (float src)
	{
		this->x /= src;
		this->y /= src;
		this->z /= src;
		this->w /= src;

		return *this;
	}
	float4& float4::operator /= (const float4 &vector)
	{
		this->x /= vector.x;
		this->y /= vector.y;
		this->z /= vector.z;
		this->w /= vector.w;

		return *this;
	}

	XMVECTOR loadfloat4(const float4 &vector)
	{
		return XMLoadFloat4(&vector);
	}
	float4 storefloat4(const XMVECTOR &vector)
	{
		float4 ret;
		XMStoreFloat4(&ret, vector);
		return ret;
	}

	float4::operator float * ()
	{
		return &x;
	}
} // namespace dx
