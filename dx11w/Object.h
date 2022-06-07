#pragma once

namespace dx
{
	template <typename Type>
	class Object
	{
		protected:
			Type *m_object;

		public:
			Object() : m_object(nullptr)
			{
			}

			virtual ~Object()
			{
				release();
			}

			Type* handle()
			{
				return m_object;
			}
			Type** pointer()
			{
				return &m_object;
			}

			void release()
			{
				if (m_object != nullptr)
				{
					m_object->Release();
				}
			}
	};
}
