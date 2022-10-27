#include "component.h"
#include <rend/rend.h>

namespace gepEngine
{
	struct TriangleRenderer : Component
	{
		TriangleRenderer();

	private:
		rend::Renderer m_renderer;
		rend::Shader m_shader;
		rend::Mesh m_mesh;
		void OnInitialize();
		void OnDisplay();
	};
}