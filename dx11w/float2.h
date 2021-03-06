#pragma once

#include "Math.h"

namespace dx
{
	class float4x4;

	class float2 : public XMFLOAT2
	{
		public:
			// ------ RXgN^
			float2();
			float2(float x);
			float2(float x, float y);
			float2(int x, int y);
			float2(const float2 &vector);
			float2(const XMFLOAT2 &value);

			// ------ floatzρ^Ο·
			operator float*();

			// ------ γόZq
			float2& operator = (float src);
			float2& operator = (const float2 &data);

			// ------ ΑZZq
			float2  operator +  (float src);
			float2  operator +  (const float2 &vector);
			float2& operator += (float src);
			float2& operator += (const float2 &vector);
			
			// ------ ΈZZq
			float2  operator -  (float src);
			float2  operator -  (const float2 &vector);
			float2& operator -= (float src);
			float2& operator -= (const float2 &vector);

			// ------ ζZZq
			float2  operator *  (float src);
			float2  operator *  (const float2 &vector);
			float2  operator *  (const float4x4 &matrix);
			float2& operator *= (float src);
			float2& operator *= (const float2 &vector);
			float2& operator *= (const float4x4 &matrix);

			// ------ ZZq
			float2  operator /  (float src);
			float2  operator /  (const float2 &vector);
			float2& operator /= (float src);
			float2& operator /= (const float2 &vector);
	};

	// xNg·
	float length(const float2 &vector);

	// ³K»
	float2 normalize(const float2 &vector);

	// ΰΟ
	float dot(const float2 &vector1, const float2 &vector2);

	// XMVECTORΙ¬΅ή
	XMVECTOR loadfloat2(const float2 &vector);
	// XMVECTOR©ηfloat2Ιi[·ι
	float2 storefloat2(const XMVECTOR &vector);
} // namespace dx
