#pragma once

#include "Mesh.h"

namespace dx
{
	class Teapot : public Mesh
	{
		public:
			Teapot();
			~Teapot();

			// �T�C�Y1��utah teapot���쐬����
			void create(unsigned int tessellation = 32);
	};
}
