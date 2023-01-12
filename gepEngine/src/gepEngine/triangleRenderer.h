#ifndef GEPENGINE_TRIANGLERENDERER_H
#define GEPENGINE_TRIANGLERENDERER_H


#include "Component.h"
#include <rend/rend.h>

namespace gepEngine
{
	struct TriangleRenderer : Component
	{
		/**
		 * @brief Constructor
		*/
		TriangleRenderer();

	private:
		rend::Shader m_shader;
		rend::Mesh m_mesh;

		void OnDisplay();
	};
}
#endif