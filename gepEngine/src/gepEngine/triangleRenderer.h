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
		rend::Renderer m_renderer;
		void OnInitialize();
		void OnDisplay();
	};
}