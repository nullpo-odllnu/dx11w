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
			// ------ コンストラクタ
			float3();
			float3(float src);
			float3(float x, float y, float z = 0.0f);
			float3(int x, int y, int z);
			float3(const float2 &vector, float z = 0.0f);
			float3(const float3 &vector);
			float3(const XMFLOAT3 &value);

			// ------ float配列型変換
			operator float*();

			// ------ 代入演算子
			float3& operator =  (float src);
			float3& operator =  (const float3 &vector);

			// ------ 加算演算子
			float3  operator +  (float src);
			float3  operator +  (const float3 &vector);
			float3& operator += (float src);
			float3& operator += (const float3 &vector);
			
			// ------ 減算演算子
			float3  operator -  (float src);
			float3  operator -  (const float3 &vector);
			float3& operator -= (float src);
			float3& operator -= (const float3 &vector);

			// ------ 乗算演算子
			float3  operator *  (float src);
			float3  operator *  (const float3 &vector);
			float3  operator *  (const float4x4 &matrix);
			float3& operator *= (float src);
			float3& operator *= (const float3 &vector);
			float3& operator *= (const float4x4 &matrix);

			// ------ 除算演算子
			float3  operator /  (float src);
			float3  operator /  (const float3 &vector);
			float3& operator /= (float src);
			float3& operator /= (const float3 &vector);
	};

	// ベクトル長
	float length(const float3 &vector);

	// 正規化
	float3 normalize(const float3 &vector);
	
	// 内積
	float dot(const float3 &vec1, const float3 &vec2);
	
	// 外積
	float3 cross(const float3 &vec1, const float3 &vec2);

	// 上方ベクトル
	float3 vectorUp();

	// 前方ベクトル
	float3 vectorFront();

	// XMVECTORに流し込む
	XMVECTOR loadfloat3(const float3 &vector);
	// XMVECTORからfloat3に格納する
	float3 storefloat3(const XMVECTOR &vector);
} // namespace dx
