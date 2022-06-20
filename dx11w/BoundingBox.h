#pragma once

#include "float3.h"

namespace dx
{
	class BoundingBox : public DirectX::BoundingBox
	{
		public:
			BoundingBox();
			// �ŏ� / �ő���W����o�E���f�B���O�{�b�N�X�쐬
			BoundingBox(const float3 &min, const float3 &max);
			BoundingBox(const BoundingBox &box);

			// ���͍��W���͂��悤�ȃo�E���f�B���O�{�b�N�X���č\�z����
			void add(const float3 &point);
			void add(const std::vector<float3> &pointList);
			// ���̓o�E���f�B���O�{�b�N�X���͂��悤�ɍč\�z����
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
