#ifndef GEPENGINE_TRIANGLERENDERER_H
#define GEPENGINE_TRIANGLERENDERER_H


#include "component.h"
#include <rend/rend.h>

namespace gepEngine
{
	struct TriangleRenderer : Component
	{
		TriangleRenderer();

	private:
		rend::Shader m_shader;
		rend::Mesh m_mesh;

		void OnDisplay();
	};
}
#endif