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
			// ------ RXgN^
			float3();
			float3(float src);
			float3(float x, float y, float z = 0.0f);
			float3(int x, int y, int z);
			float3(const float2 &vector, float z = 0.0f);
			float3(const float3 &vector);
			float3(const XMFLOAT3 &value);

			// ------ floatzρ^Ο·
			operator float*();

			// ------ γόZq
			float3& operator =  (float src);
			float3& operator =  (const float3 &vector);

			// ------ ΑZZq
			float3  operator +  (float src);
			float3  operator +  (const float3 &vector);
			float3& operator += (float src);
			float3& operator += (const float3 &vector);
			
			// ------ ΈZZq
			float3  operator -  (float src);
			float3  operator -  (const float3 &vector);
			float3& operator -= (float src);
			float3& operator -= (const float3 &vector);

			// ------ ζZZq
			float3  operator *  (float src);
			float3  operator *  (const float3 &vector);
			float3  operator *  (const float4x4 &matrix);
			float3& operator *= (float src);
			float3& operator *= (const float3 &vector);
			float3& operator *= (const float4x4 &matrix);

			// ------ ZZq
			float3  operator /  (float src);
			float3  operator /  (const float3 &vector);
			float3& operator /= (float src);
			float3& operator /= (const float3 &vector);
	};

	// xNg·
	float length(const float3 &vector);

	// ³K»
	float3 normalize(const float3 &vector);
	
	// ΰΟ
	float dot(const float3 &vec1, const float3 &vec2);
	
	// OΟ
	float3 cross(const float3 &vec1, const float3 &vec2);

	// γϋxNg
	float3 vectorUp();

	// OϋxNg
	float3 vectorFront();

	// XMVECTORΙ¬΅ή
	XMVECTOR loadfloat3(const float3 &vector);
	// XMVECTOR©ηfloat3Ιi[·ι
	float3 storefloat3(const XMVECTOR &vector);
} // namespace dx
