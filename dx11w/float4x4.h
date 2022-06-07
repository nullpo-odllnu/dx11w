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
			// ------ �R���X�g���N�^
			float4x4();

			// ------ �P�ʍs��
			void setIdentity();

			// ------ �X�P�[�����O�s��Z�b�g
			void setScaling(float scale);
			void setScaling(float x, float y, float z);
			void setScaling(const float2 &scale);
			void setScaling(const float3 &scale);

			// ------ ��]�s��Z�b�g
			void setRotationX(float radian);
			void setRotationY(float radian);
			void setRotationZ(float radian);
			// �N�H�[�^�j�I��(�� + ��]�prad)
			void setRotation(const float3 &axisvector, float radian);
			// �N�H�[�^�j�I��(���������A�ڕW����)
			void setRotation(const float3 &startVector, const float3 &endVector);
			// �N�H�[�^�j�I��(���������A�ڕW�����A��]�p)
			void setRotation(const float3 &startVector, const float3 &endVector, float radian);

			// ------ ���s�ړ��s��Z�b�g
			// 2D�̎��͌��݂̃r���[�|�[�g���g�p���č�������_�Ƃ��Čv�Z
			void setTranslation2D(float x, float y, unsigned int screenWidth, unsigned int screenHeight);
			void setTranslation2D(const float2 &translate, unsigned int screenWidth, unsigned int screenHeight);
			void setTranslation3D(float x, float y, float z);
			void setTranslation3D(const float3 &translate);

			// �r���[�s��Z�b�g
			void setViewMatrix(const float3 &lookCoord, const float3 &lookAt, const float3 &lookUp);

			// �v���W�F�N�V�����s��Z�b�g
			void setProjection2D(unsigned int width, unsigned int height);
			void setProjection3D(float fovRadian, float aspect, float zNear, float zFar);

			// �r���[�|�[�g�s��쐬
			// �v���W�F�N�V�������W�����[���h���W�ϊ��ɕK�v
			void setViewPort(unsigned int width, unsigned int height);

			// �t�s��擾
			float4x4 getInverse() const;

			// �]�u�s��擾
			float4x4 getTranspose() const;

			// ------ �A�N�Z�X���Z�q
			float operator () (int row, int col);
			const float operator() (int row, int col) const;

			// ------ ��Z���Z�q
			float4x4 operator  *  (float4x4 &vector);
			float4x4& operator *= (float4x4 &vector);

			// ------ ������Z�q
			float4x4 operator = (const float4x4& matrix);
			float4x4& operator = (float4x4 &matrix);
			//float4x4& operator = (float4x4 *matrix);

		private:
			// �N�H�[�^�j�I���ɂ���]�ϊ�
			// http://www015.upp.so-net.ne.jp/notgeld/quaternion.html
			void setQuaternionRotation(const float3 &axis, float sine, float cosine);
	};

	// XMMATRIX�ɗ�������
	XMMATRIX loadfloat4x4(const float4x4 &matrix);
	// XMMATRIX����float4x4�Ɋi�[����
	float4x4 storefloat4x4(const XMMATRIX &matrix);
} // namespace dx
