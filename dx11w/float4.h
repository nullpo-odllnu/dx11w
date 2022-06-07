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
			// ------ ƒRƒ“ƒXƒgƒ‰ƒNƒ^
			float4();
			float4(float src);
			float4(float x, float y, float z, float w = 1.0f);
			float4(const float2 &vector, float z = 0.0f, float w = 1.0f);
			float4(const float3 &vector, float w = 1.0f);
			float4(const float4 &vector);
			float4(const XMFLOAT4 &value);

			// ------ float”z—ñŒ^•ÏŠ·
			operator float*();

			// ------ ‘ã“ü‰‰Zq
			float4& operator =  (float src);
			float4& operator =  (const float4 &data);

			// ------ ‰ÁZ‰‰Zq
			float4  operator +  (float src);
			float4  operator +  (const float4 &vector);
			float4& operator += (float src);
			float4& operator += (const float4 &vector);
			
			// ------ Œ¸Z‰‰Zq
			float4  operator -  (float src);
			float4  operator -  (const float4 &vector);
			float4& operator -= (float src);
			float4& operator -= (const float4 &vector);

			// ------ æZ‰‰Zq
			float4  operator *  (float src);
			float4  operator *  (const float4 &vector);
			float4  operator *  (const float4x4 &matrix);
			float4& operator *= (float src);
			float4& operator *= (const float4 &vector);
			float4& operator *= (const float4x4 &matrix);

			// ------ œZ‰‰Zq
			float4  operator /  (float src);
			float4  operator /  (const float4 &vector);
			float4& operator /= (float src);
			float4& operator /= (const float4 &vector);
	};

	// XMVECTOR‚É—¬‚µ‚Ş
	XMVECTOR loadfloat4(const float4 &vector);
	// XMVECTOR‚©‚çfloat4‚ÉŠi”[‚·‚é
	float4 storefloat4(const XMVECTOR &vector);
} // namespace dx
