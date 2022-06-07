#pragma once

#include "Math.h"

namespace dx
{
	class float4x4;

	class float2 : public XMFLOAT2
	{
		public:
			// ------ �R���X�g���N�^
			float2();
			float2(float x);
			float2(float x, float y);
			float2(int x, int y);
			float2(const float2 &vector);
			float2(const XMFLOAT2 &value);

			// ------ float�z��^�ϊ�
			operator float*();

			// ------ ������Z�q
			float2& operator = (float src);
			float2& operator = (const float2 &data);

			// ------ ���Z���Z�q
			float2  operator +  (float src);
			float2  operator +  (const float2 &vector);
			float2& operator += (float src);
			float2& operator += (const float2 &vector);
			
			// ------ ���Z���Z�q
			float2  operator -  (float src);
			float2  operator -  (const float2 &vector);
			float2& operator -= (float src);
			float2& operator -= (const float2 &vector);

			// ------ ��Z���Z�q
			float2  operator *  (float src);
			float2  operator *  (const float2 &vector);
			float2  operator *  (const float4x4 &matrix);
			float2& operator *= (float src);
			float2& operator *= (const float2 &vector);
			float2& operator *= (const float4x4 &matrix);

			// ------ ���Z���Z�q
			float2  operator /  (float src);
			float2  operator /  (const float2 &vector);
			float2& operator /= (float src);
			float2& operator /= (const float2 &vector);
	};

	// �x�N�g����
	float length(const float2 &vector);

	// ���K��
	float2 normalize(const float2 &vector);

	// ����
	float dot(const float2 &vector1, const float2 &vector2);

	// XMVECTOR�ɗ�������
	XMVECTOR loadfloat2(const float2 &vector);
	// XMVECTOR����float2�Ɋi�[����
	float2 storefloat2(const XMVECTOR &vector);
} // namespace dx
