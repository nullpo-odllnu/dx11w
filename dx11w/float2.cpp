#include "float2.h"

#include "float4x4.h"

namespace dx
{
	float2::float2() : 
		XMFLOAT2(0.0f, 0.0f)
	{
	}
	float2::float2(float x) : 
		XMFLOAT2(x, x)
	{
	}
	float2::float2(float x, float y) : 
		XMFLOAT2(x, y)
	{
	}
	float2::float2(const float2 &vector) : 
		XMFLOAT2(vector.x, vector.y) 
	{
	}
	float2::float2(int x, int y) : 
		XMFLOAT2((float)x, (float)y)
	{
	}
	float2::float2(const XMFLOAT2 &value) :
		XMFLOAT2(value)
	{
	}

	float2& float2::operator = (float src)
	{
		this->x = src;
		this->y = src;

		return *this;
	}
	float2& float2::operator = (const float2 &data)
	{
		this->x = data.x;
		this->y = data.y;

		return *this;
	}

	float2 float2::operator + (float src)
	{
		return float2(this->x + src, this->y + src);
	}
	float2 float2::operator + (const float2 &vector)
	{
		return float2(this->x + vector.x, this->y + vector.y);
	}
	float2& float2::operator += (float src)
	{
		this->x += src;
		this->y += src;

		return *this;
	}
	float2& float2::operator += (const float2 &vector)
	{
		this->x += vector.x;
		this->y += vector.y;

		return *this;
	}

	float2 float2::operator - (float src)
	{
		return float2(this->x - src, this->y - src);
	}
	float2 float2::operator - (const float2 &vector)
	{
		return float2(this->x - vector.x, this->y - vector.y);
	}
	float2& float2::operator -= (float src)
	{
		this->x -= src;
		this->y -= src;

		return *this;
	}
	float2& float2::operator -= (const float2 &vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;

		return *this;
	}

	float2 float2::operator * (float src)
	{
		return float2(this->x * src, this->y * src);
	}
	float2 float2::operator * (const float2 &vector)
	{
		return float2(this->x * vector.x, this->y * vector.y);
	}
	float2 float2::operator * (const float4x4 &matrix)
	{
		return storefloat2(XMVector2Transform(loadfloat2(*this), loadfloat4x4(matrix)));
	}
	float2& float2::operator *= (float src)
	{
		this->x *= src;
		this->y *= src;

		return *this;
	}
	float2& float2::operator *= (const float2 &vector)
	{
		this->x *= vector.x;
		this->y *= vector.y;

		return *this;
	}
	float2& float2::operator *= (const float4x4 &matrix)
	{
		*this = storefloat2(XMVector2Transform(loadfloat2(*this), loadfloat4x4(matrix)));
		return *this;
	}

	float2 float2::operator / (float src)
	{
		return float2(this->x / src, this->y / src);
	}
	float2 float2::operator / (const float2 &vector)
	{
		return float2(this->x / vector.x, this->y / vector.y);
	}
	float2& float2::operator /= (float src)
	{
		this->x /= src;
		this->y /= src;
		return *this;
	}
	float2& float2::operator /= (const float2 &vector)
	{
		this->x /= vector.x;
		this->y /= vector.y;
		return *this;
	}

	float length(const float2 &vector)
	{
		return storefloat2(XMVector2Length(loadfloat2(vector))).x;
	}

	float2 normalize(const float2 &vector)
	{
		return storefloat2(XMVector2Normalize(loadfloat2(vector)));
	}

	float dot(const float2 &vec1, const float2 &vec2)
	{
		return storefloat2(XMVector2Dot(loadfloat2(vec1), loadfloat2(vec2))).x;
	}

	XMVECTOR loadfloat2(const float2 &vector)
	{
		return XMLoadFloat2(&vector);
	}
	float2 storefloat2(const XMVECTOR &vector)
	{
		float2 ret;
		XMStoreFloat2(&ret, vector);
		return ret;
	}

	float2::operator float * ()
	{
		return &x;
	}
} // naemspace dx
