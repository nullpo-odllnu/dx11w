#include "float4x4.h"

#include "float2.h"
#include "float3.h"
#include "float4.h"

namespace dx
{
	float4x4::float4x4()
	{
		setIdentity();
	}

	void float4x4::setIdentity()
	{
		XMStoreFloat4x4(this, XMMatrixIdentity());
	}

	void float4x4::setScaling(float scale)
	{
		XMStoreFloat4x4(this, XMMatrixScaling(scale, scale, scale));
	}
	void float4x4::setScaling(float x, float y, float z)
	{
		XMStoreFloat4x4(this, XMMatrixScaling(x, y, z));
	}
	void float4x4::setScaling(const float3 &scale)
	{
		XMStoreFloat4x4(this, XMMatrixScaling(scale.x, scale.y, scale.z));
	}
	void float4x4::setScaling(const float2 &scale)
	{
		XMStoreFloat4x4(this, XMMatrixScaling(scale.x, scale.y, 1.0f));
	}

	void float4x4::setRotationX(float radian)
	{
		XMStoreFloat4x4(this, XMMatrixRotationX(radian));
	}
	void float4x4::setRotationY(float radian)
	{
		XMStoreFloat4x4(this, XMMatrixRotationY(radian));
	}
	void float4x4::setRotationZ(float radian)
	{
		XMStoreFloat4x4(this, XMMatrixRotationZ(radian));
	}
	void float4x4::setRotation(const float3 &startVector, const float3 &endVector)
	{
		float d = dot(normalize(startVector), normalize(endVector));

		// ‚Ù‚Ú“¯‚¶Œü‚«‚ðŒü‚¢‚Ä‚¢‚éê‡‚Í‰ñ“]‚µ‚È‚¢
		if (d >= 0.9999f)
		{
			this->setIdentity();
		}
		else{
			float angle = abs(d - 1.0f) * PI;
			float sine = sin(angle / 2.0f);
			float cosine = cos(angle / 2.0f);
			float3 axis = cross(startVector, endVector);

			setQuaternionRotation(axis, sine, cosine);
		}
	}
	void float4x4::setRotation(const float3 &startVector, const float3 &endVector, float angle)
	{
		float d = dot(normalize(startVector), normalize(endVector));

		// ‚Ù‚Ú“¯‚¶Œü‚«‚ðŒü‚¢‚Ä‚¢‚éê‡‚Í‰ñ“]‚µ‚È‚¢
		if (d >= 0.9999f)
		{
			this->setIdentity();
		}
		else
		{
			float sine = sin(angle / 2.0f);
			float cosine = cos(angle / 2.0f);
			float3 axis = cross(startVector, endVector);

			setQuaternionRotation(axis, sine, cosine);
		}
	}
	void float4x4::setRotation(const float3 &axisVector, float angle)
	{
		setQuaternionRotation(axisVector, sin(angle), cos(angle));
	}

	void float4x4::setQuaternionRotation(const float3 &axis, float sine, float cosine){
		float4 tmp(axis.x * sine, axis.y * sine, axis.z * sine, cosine);

		this->_11 = 1.0f - 2.0f  * tmp.y * tmp.y - 2.0f  * tmp.z * tmp.z;
		this->_12 = 2.0f * tmp.x * tmp.y + 2.0f  * tmp.w * tmp.z;
		this->_13 = 2.0f * tmp.x * tmp.z - 2.0f  * tmp.w * tmp.y;
		this->_14 = 0.0f;
		this->_21 = 2.0f * tmp.x * tmp.y - 2.0f  * tmp.w * tmp.z;
		this->_22 = 1.0f - 2.0f  * tmp.x * tmp.x - 2.0f  * tmp.z * tmp.z;
		this->_23 = 2.0f * tmp.y * tmp.z + 2.0f  * tmp.w * tmp.x;
		this->_24 = 0.0f;
		this->_31 = 2.0f * tmp.x * tmp.z + 2.0f  * tmp.w * tmp.y;
		this->_32 = 2.0f * tmp.y * tmp.z - 2.0f  * tmp.w * tmp.x;
		this->_33 = 1.0f - 2.0f  * tmp.x * tmp.x - 2.0f  * tmp.y * tmp.y;
		this->_34 = 0.0f;
		this->_41 = 0.0f;
		this->_42 = 0.0f;
		this->_43 = 0.0f;
		this->_44 = 1.0f;
	}

	void float4x4::setTranslation2D(float x, float y, unsigned int screenWidth, unsigned int screenHeight)
	{
		XMStoreFloat4x4(this, XMMatrixTranslation(x - screenWidth / 2.0f, screenHeight / 2.0f - y, 0.0f));
	}
	void float4x4::setTranslation2D(const float2 &translate, unsigned int screenWidth, unsigned int screenHeight)
	{
		XMStoreFloat4x4(this, XMMatrixTranslation(translate.x - screenWidth / 2.0f, screenHeight / 2.0f - translate.y, 0.0f));
	}

	void float4x4::setTranslation3D(float x, float y, float z)
	{
		XMStoreFloat4x4(this, XMMatrixTranslation(x, y, z));
	}
	void float4x4::setTranslation3D(const float3 &translate)
	{
		XMStoreFloat4x4(this, XMMatrixTranslation(translate.x, translate.y, translate.z));
	}

	void float4x4::setViewMatrix(const float3 &lookCoord, const float3 &lookAt, const float3 &lookUp)
	{
		XMStoreFloat4x4(this, XMMatrixLookAtLH(loadfloat3(lookCoord), loadfloat3(lookAt), loadfloat3(lookUp)));
	}

	void float4x4::setProjection2D(unsigned int width, unsigned int height)
	{
		XMStoreFloat4x4(this, XMMatrixOrthographicLH(static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f));
	}
	void float4x4::setProjection3D(float fovRadian, float aspect, float zNear, float zFar)
	{
		XMStoreFloat4x4(this, XMMatrixPerspectiveFovLH(fovRadian, aspect, zNear, zFar));
	}

	void float4x4::setViewPort(unsigned int width, unsigned int height)
	{
		this->setIdentity();

		_11 = width / 2.0f;
		_22 = -static_cast<int>(height) / 2.0f;
		_41 = width / 2.0f;
		_42 = height / 2.0f;
	}

	float4x4 float4x4::getInverse() const
	{
		return storefloat4x4(XMMatrixInverse(NULL, loadfloat4x4(*this)));
	}

	float4x4 float4x4::getTranspose() const
	{
		return storefloat4x4(XMMatrixTranspose(loadfloat4x4(*this)));
	}

	float float4x4::operator () (int row, int col)
	{
		return m[row][col];
	}

	const float float4x4::operator() (int row, int col) const
	{
		return m[row][col];
	}

	float4x4 float4x4::operator * (float4x4 &matrix)
	{
		float4x4 ret = storefloat4x4(XMMatrixMultiply(loadfloat4x4(*this), loadfloat4x4(matrix)));
		return ret;
	}
	float4x4& float4x4::operator *= (float4x4 &matrix)
	{
		*this = storefloat4x4(XMMatrixMultiply(loadfloat4x4(*this), loadfloat4x4(matrix)));
		return *this;
	}

	float4x4 float4x4::operator = (const float4x4& matrix)
	{
		memcpy_s(this->m, sizeof(this->m), matrix.m, sizeof(matrix.m));
		return *this;
	}
	float4x4& float4x4::operator = (float4x4 &matrix)
	{
		memcpy_s(this->m, sizeof(this->m), matrix.m, sizeof(matrix.m));
		return *this;
	}
	/*
	float4x4& float4x4::operator = (float4x4 *matrix)
	{
		memcpy_s(this->m, sizeof(this->m), matrix->m, sizeof(matrix->m));
		return *this;
	}
	*/

	XMMATRIX loadfloat4x4(const float4x4 &matrix)
	{
		return XMLoadFloat4x4(&matrix);
	}

	float4x4 storefloat4x4(const XMMATRIX &matrix)
	{
		float4x4 ret;
		XMStoreFloat4x4(&ret, matrix);
		return ret;
	}
} // namespace dx
