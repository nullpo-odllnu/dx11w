#pragma once

#include "Math.h"

namespace dx
{
	class float4x4;

	class float2 : public XMFLOAT2
	{
		public:
			// ------ ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			float2();
			float2(float x);
			float2(float x, float y);
			float2(int x, int y);
			float2(const float2 &vector);
			float2(const XMFLOAT2 &value);

			// ------ float”z—ñŒ^•ÏŠ·
			operator float*();

			// ------ ‘ã“ü‰‰Zq
			float2& operator = (float src);
			float2& operator = (const float2 &data);

			// ------ ‰ÁZ‰‰Zq
			float2  operator +  (float src);
			float2  operator +  (const float2 &vector);
			float2& operator += (float src);
			float2& operator += (const float2 &vector);
			
			// ------ Œ¸Z‰‰Zq
			float2  operator -  (float src);
			float2  operator -  (const float2 &vector);
			float2& operator -= (float src);
			float2& operator -= (const float2 &vector);

			// ------ æZ‰‰Zq
			float2  operator *  (float src);
			float2  operator *  (const float2 &vector);
			float2  operator *  (const float4x4 &matrix);
			float2& operator *= (float src);
			float2& operator *= (const float2 &vector);
			float2& operator *= (const float4x4 &matrix);

			// ------ œZ‰‰Zq
			float2  operator /  (float src);
			float2  operator /  (const float2 &vector);
			float2& operator /= (float src);
			float2& operator /= (const float2 &vector);
	};

	// ƒxƒNƒgƒ‹’·
	float length(const float2 &vector);

	// ³‹K‰»
	float2 normalize(const float2 &vector);

	// “àÏ
	float dot(const float2 &vector1, const float2 &vector2);

	// XMVECTOR‚É—¬‚µ‚Ş
	XMVECTOR loadfloat2(const float2 &vector);
	// XMVECTOR‚©‚çfloat2‚ÉŠi”[‚·‚é
	float2 storefloat2(const XMVECTOR &vector);
} // namespace dx
