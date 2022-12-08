#include "triangleRenderer.h"
#include <iostream>
#include "glmWrap.h"
#include "entity.h"
#include "transform.h"

namespace gepEngine
{
	//yes
	TriangleRenderer::TriangleRenderer() :
		m_shader("../resources/shaders/basic.vert", "../resources/shaders/basic.frag")
		{
			m_mesh.loadTriangle();
		}

	void TriangleRenderer::OnDisplay()
	{
		rend::Renderer r(720, 720);
		mat4 model = m_entity.lock()->GetTransform()->GetModel();

		r.model(model);
		r.shader(&m_shader);
		r.mesh(&m_mesh);
		r.render();
	}
}