#include "Framerate.h"

namespace dx
{
	static Framerate *instance = nullptr;
	static TIMECAPS timeCaps;

	class Framerate::Impl
	{
		public:
			unsigned int m_selected;
			unsigned int m_count;
			unsigned int m_start;
			double m_average;

			Impl() : 
				m_selected(0),
				m_count(0),
				m_start(0),
				m_average(0.0)
			{
			}
	};

	Framerate::Framerate()
	{
		// �V�X�e���̃^�C�}�[�ŏ����x���擾�A�ݒ�
		timeGetDevCaps(&timeCaps, sizeof(TIMECAPS));
		timeBeginPeriod(timeCaps.wPeriodMin);

		m_impl = std::make_unique<Framerate::Impl>();
	}
	Framerate::~Framerate()
	{
		// �ݒ肵���^�C�}�[�ŏ����x�����ɖ߂�
		timeEndPeriod(timeCaps.wPeriodMin);
	}

	void Framerate::set(unsigned int framePerSecond)
	{
		m_impl->m_selected = framePerSecond;
		m_impl->m_count = 0;
		m_impl->m_average = 0.0;
	}
	void Framerate::update()
	{
		// �J�E���g��0(�N���� or �t���[�����[�g�������������)
		// �t���[�������ŏ��̎��Ԃ��L�^
		if (m_impl->m_count == 0)
		{
			m_impl->m_start = timeGetTime();
		}
		// �t���[�����[�g��������������ꍇ�͕��σt���[�����[�g���v�Z
		if (m_impl->m_count == m_impl->m_selected)
		{
			unsigned int time = timeGetTime();
			// 0���Z���
			if (m_impl->m_selected != 0)
			{
				m_impl->m_average = 1000.0 / ((time - m_impl->m_start) / static_cast<double>(m_impl->m_selected));
			}

			m_impl->m_count = 0;
			m_impl->m_start = time;
		}
		m_impl->m_count++;
	}
	void Framerate::offset()
	{
		int processTime = timeGetTime() - m_impl->m_start;
		int waitTime = 0;
		// 0���Z���
		if (m_impl->m_selected != 0)
		{
			waitTime = m_impl->m_count * 1000 / m_impl->m_selected - processTime;
		}
		if (waitTime > 0)
		{
			Sleep(waitTime);
		}
	}

	double Framerate::getPresentFramerate() const
	{
		return m_impl->m_average;
	}
	double Framerate::getOrderedFramerate() const
	{
		return static_cast<double>(m_impl->m_selected);
	}
	double Framerate::getDeltaTime() const
	{
		if (m_impl->m_average == 0.0)
		{
			return 0.0;
		}
		return 1.0 / m_impl->m_average;
	}

	Framerate* Framerate::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Framerate();
		}
		return instance;
	}
	void Framerate::deleteInstance()
	{
		SAFE_DELETE(instance);
	}
} // namespace dx
