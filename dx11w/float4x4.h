#pragma once

#include "Math.h"

namespace dx
{
	class float2;
	class float3;
	class float4;

	class float4x4 : public XMFLOAT4X4
	{
		public:
			// ------ コンストラクタ
			float4x4();

			// ------ 単位行列
			void setIdentity();

			// ------ スケーリング行列セット
			void setScaling(float scale);
			void setScaling(float x, float y, float z);
			void setScaling(const float2 &scale);
			void setScaling(const float3 &scale);

			// ------ 回転行列セット
			void setRotationX(float radian);
			void setRotationY(float radian);
			void setRotationZ(float radian);
			// クォータニオン(軸 + 回転角rad)
			void setRotation(const float3 &axisvector, float radian);
			// クォータニオン(初期方向、目標方向)
			void setRotation(const float3 &startVector, const float3 &endVector);
			// クォータニオン(初期方向、目標方向、回転角)
			void setRotation(const float3 &startVector, const float3 &endVector, float radian);

			// ------ 平行移動行列セット
			// 2Dの時は現在のビューポートを使用して左上を原点として計算
			void setTranslation2D(float x, float y, unsigned int screenWidth, unsigned int screenHeight);
			void setTranslation2D(const float2 &translate, unsigned int screenWidth, unsigned int screenHeight);
			void setTranslation3D(float x, float y, float z);
			void setTranslation3D(const float3 &translate);

			// ビュー行列セット
			void setViewMatrix(const float3 &lookCoord, const float3 &lookAt, const float3 &lookUp);

			// プロジェクション行列セット
			void setProjection2D(unsigned int width, unsigned int height);
			void setProjection3D(float fovRadian, float aspect, float zNear, float zFar);

			// ビューポート行列作成
			// プロジェクション座標→ワールド座標変換に必要
			void setViewPort(unsigned int width, unsigned int height);

			// 逆行列取得
			float4x4 getInverse() const;

			// 転置行列取得
			float4x4 getTranspose() const;

			// ------ アクセス演算子
			float operator () (int row, int col);
			const float operator() (int row, int col) const;

			// ------ 乗算演算子
			float4x4 operator  *  (float4x4 &vector);
			float4x4& operator *= (float4x4 &vector);

			// ------ 代入演算子
			float4x4 operator = (const float4x4& matrix);
			float4x4& operator = (float4x4 &matrix);
			//float4x4& operator = (float4x4 *matrix);

		private:
			// クォータニオンによる回転変換
			// http://www015.upp.so-net.ne.jp/notgeld/quaternion.html
			void setQuaternionRotation(const float3 &axis, float sine, float cosine);
	};

	// XMMATRIXに流し込む
	XMMATRIX loadfloat4x4(const float4x4 &matrix);
	// XMMATRIXからfloat4x4に格納する
	float4x4 storefloat4x4(const XMMATRIX &matrix);
} // namespace dx
