#include "triangleRenderer.h"
#include <iostream>
#include "glmWrap.h"
#include "entity.h"
#include "transform.h"

namespace gepEngine
{
	TriangleRenderer::TriangleRenderer() :
		m_renderer(1080, 720),
		m_shader("../data/shaders/basic.vert", "../data/shaders/basic.frag")
		{ }

	void TriangleRenderer::OnInitialize()
	{
		m_mesh.loadTriangle();
	}

	void TriangleRenderer::OnDisplay()
	{
		mat4 model = m_entity.lock()->getTransform()->getModel();

		m_renderer.model(model);

		m_renderer.shader(&m_shader);
		m_renderer.mesh(&m_mesh);

		m_renderer.render();
	}
}