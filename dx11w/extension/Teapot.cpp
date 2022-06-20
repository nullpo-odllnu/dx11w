#include "Teapot.h"

namespace dx
{
	Teapot::Teapot() : Mesh()
	{
	}
	Teapot::~Teapot()
	{
	}

	void Teapot::create(unsigned int tessellation)
	{
		std::vector<DirectX::VertexPositionNormalTexture> vertex;
		std::vector<uint16_t> index;

		DirectX::GeometricPrimitive::CreateTeapot(vertex, index, 1.0f, tessellation, false);
		storeDirectXTKPrimitive(vertex, index);
	}
}
