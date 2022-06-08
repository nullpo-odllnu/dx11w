#pragma once

namespace dx
{
	class Framerate
	{
		public:
			// インスタンス取得
			static Framerate* getInstance();
			// インスタンス解放
			static void deleteInstance();

			// フレームレートを設定
			void set(unsigned int framePerSecond);
			// 更新
			void update();
			// フレームレート用の調整
			void offset();

			// 現在のフレームレート取得
			double getPresentFramerate() const;
			// 指定したフレームレート取得
			double getOrderedFramerate() const;
			// 現在のフレームレートから1フレームあたりの時間推移[s]を取得
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
