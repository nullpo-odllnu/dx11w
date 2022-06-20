#pragma once

#include "float3.h"

namespace dx
{
	class BoundingBox : public DirectX::BoundingBox
	{
		public:
			BoundingBox();
			// 最小 / 最大座標からバウンディングボックス作成
			BoundingBox(const float3 &min, const float3 &max);
			BoundingBox(const BoundingBox &box);

			// 入力座標を囲うようなバウンディングボックスを再構築する
			void add(const float3 &point);
			void add(const std::vector<float3> &pointList);
			// 入力バウンディングボックスを囲うように再構築する
			void add(const BoundingBox &boundingBox);

			void clear();

			float3 getSize() const;
			float3 getCenter() const;
			float getRadius() const;
			float3 getMin() const;
			float3 getMax() const;

		private:
			float3 m_min;
			float3 m_max;
	};
}
