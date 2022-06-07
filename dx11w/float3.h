#pragma once

#include "Math.h"

namespace dx
{
	class float2;
	class float4;
	class float4x4;

	class float3 : public XMFLOAT3
	{
		public:
			// ------ �R���X�g���N�^
			float3();
			float3(float src);
			float3(float x, float y, float z = 0.0f);
			float3(int x, int y, int z);
			float3(const float2 &vector, float z = 0.0f);
			float3(const float3 &vector);
			float3(const XMFLOAT3 &value);

			// ------ float�z��^�ϊ�
			operator float*();

			// ------ ������Z�q
			float3& operator =  (float src);
			float3& operator =  (const float3 &vector);

			// ------ ���Z���Z�q
			float3  operator +  (float src);
			float3  operator +  (const float3 &vector);
			float3& operator += (float src);
			float3& operator += (const float3 &vector);
			
			// ------ ���Z���Z�q
			float3  operator -  (float src);
			float3  operator -  (const float3 &vector);
			float3& operator -= (float src);
			float3& operator -= (const float3 &vector);

			// ------ ��Z���Z�q
			float3  operator *  (float src);
			float3  operator *  (const float3 &vector);
			float3  operator *  (const float4x4 &matrix);
			float3& operator *= (float src);
			float3& operator *= (const float3 &vector);
			float3& operator *= (const float4x4 &matrix);

			// ------ ���Z���Z�q
			float3  operator /  (float src);
			float3  operator /  (const float3 &vector);
			float3& operator /= (float src);
			float3& operator /= (const float3 &vector);
	};

	// �x�N�g����
	float length(const float3 &vector);

	// ���K��
	float3 normalize(const float3 &vector);
	
	// ����
	float dot(const float3 &vec1, const float3 &vec2);
	
	// �O��
	float3 cross(const float3 &vec1, const float3 &vec2);

	// ����x�N�g��
	float3 vectorUp();

	// �O���x�N�g��
	float3 vectorFront();

	// XMVECTOR�ɗ�������
	XMVECTOR loadfloat3(const float3 &vector);
	// XMVECTOR����float3�Ɋi�[����
	float3 storefloat3(const XMVECTOR &vector);
} // namespace dx
