#include "TriangleRenderer.h"
#include <iostream>
#include "GlmWrap.h"
#include "Entity.h"
#include "Transform.h"
#include "Camera.h"

namespace gepEngine
{
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
		r.projection(Camera::GetMainCam()->GetProjection());
		r.view(Camera::GetMainCam()->GetView());
		r.render();
	}
}