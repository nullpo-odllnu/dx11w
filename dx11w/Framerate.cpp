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
		// システムのタイマー最小精度を取得、設定
		timeGetDevCaps(&timeCaps, sizeof(TIMECAPS));
		timeBeginPeriod(timeCaps.wPeriodMin);

		m_impl = std::make_unique<Framerate::Impl>();
	}
	Framerate::~Framerate()
	{
		// 設定したタイマー最小精度を元に戻す
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
		// カウントが0(起動時 or フレームレート周期を一周した)
		// フレーム周期最初の時間を記録
		if (m_impl->m_count == 0)
		{
			m_impl->m_start = timeGetTime();
		}
		// フレームレート周期を一周した場合は平均フレームレートを計算
		if (m_impl->m_count == m_impl->m_selected)
		{
			unsigned int time = timeGetTime();
			// 0除算回避
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
		// 0除算回避
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
