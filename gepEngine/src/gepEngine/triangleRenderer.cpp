#include "triangleRenderer.h"

namespace gepEngine
{
	TriangleRenderer::TriangleRenderer() :
		m_renderer(1080, 720),
		m_shader("data/shaders/basic.vert", "data/shaders/basic.frag")
		{ }

	void TriangleRenderer::onInitialize()
	{
		m_mesh.loadQuad();
	}

	void TriangleRenderer::onDisplay()
	{
		m_renderer.shader(&m_shader);
		m_renderer.mesh(&m_mesh);

		m_renderer.render();
	}
}