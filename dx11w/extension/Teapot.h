#pragma once

#include "Mesh.h"

namespace dx
{
	class Teapot : public Mesh
	{
		public:
			Teapot();
			~Teapot();

			// サイズ1のutah teapotを作成する
			void create(unsigned int tessellation = 32);
	};
}
