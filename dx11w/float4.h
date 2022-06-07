#pragma once

#include "Math.h"

namespace dx
{
	class float2;
	class float3;
	class float4x4;
	
	class float4 : public XMFLOAT4
	{	
		public:
			// ------ �R���X�g���N�^
			float4();
			float4(float src);
			float4(float x, float y, float z, float w = 1.0f);
			float4(const float2 &vector, float z = 0.0f, float w = 1.0f);
			float4(const float3 &vector, float w = 1.0f);
			float4(const float4 &vector);
			float4(const XMFLOAT4 &value);

			// ------ float�z��^�ϊ�
			operator float*();

			// ------ ������Z�q
			float4& operator =  (float src);
			float4& operator =  (const float4 &data);

			// ------ ���Z���Z�q
			float4  operator +  (float src);
			float4  operator +  (const float4 &vector);
			float4& operator += (float src);
			float4& operator += (const float4 &vector);
			
			// ------ ���Z���Z�q
			float4  operator -  (float src);
			float4  operator -  (const float4 &vector);
			float4& operator -= (float src);
			float4& operator -= (const float4 &vector);

			// ------ ��Z���Z�q
			float4  operator *  (float src);
			float4  operator *  (const float4 &vector);
			float4  operator *  (const float4x4 &matrix);
			float4& operator *= (float src);
			float4& operator *= (const float4 &vector);
			float4& operator *= (const float4x4 &matrix);

			// ------ ���Z���Z�q
			float4  operator /  (float src);
			float4  operator /  (const float4 &vector);
			float4& operator /= (float src);
			float4& operator /= (const float4 &vector);
	};

	// XMVECTOR�ɗ�������
	XMVECTOR loadfloat4(const float4 &vector);
	// XMVECTOR����float4�Ɋi�[����
	float4 storefloat4(const XMVECTOR &vector);
} // namespace dx
