#pragma once

namespace dx
{
	class Framerate
	{
		public:
			// �C���X�^���X�擾
			static Framerate* getInstance();
			// �C���X�^���X���
			static void deleteInstance();

			// �t���[�����[�g��ݒ�
			void set(unsigned int framePerSecond);
			// �X�V
			void update();
			// �t���[�����[�g�p�̒���
			void offset();

			// ���݂̃t���[�����[�g�擾
			double getPresentFramerate() const;
			// �w�肵���t���[�����[�g�擾
			double getOrderedFramerate() const;
			// ���݂̃t���[�����[�g����1�t���[��������̎��Ԑ���[s]���擾
			double getDeltaTime() const;

		private:
			Framerate();
			~Framerate();
			Framerate(const Framerate& framerate);
			Framerate& operator=(const Framerate& framerate);

			class Impl;
			std::unique_ptr<Impl> m_impl;
	};
}
