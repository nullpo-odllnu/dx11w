#pragma once

#include "Mesh.h"

namespace dx
{
	class Teapot : public Mesh
	{
		public:
			Teapot();
			~Teapot();

			// ƒTƒCƒY1‚Ìutah teapot‚ğì¬‚·‚é
			void create(unsigned int tessellation = 32);
	};
}
