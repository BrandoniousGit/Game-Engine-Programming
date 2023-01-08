#include "ModelRenderer.h"
#include <iostream>
#include "GlmWrap.h"
#include "Entity.h"
#include "Transform.h"
#include "Camera.h"


namespace gepEngine
{
	ModelRenderer::ModelRenderer() :
		m_shader("../resources/shaders/basic.vert", "../resources/shaders/basic.frag"),
		m_texture("../resources/textures/Maxwell_Diffuse.bmp")
	{
		m_mesh.loadTriangle();
		m_model = new rend::Model("../resources/models/Maxwell.obj");
	}
	void ModelRenderer::OnDisplay()
	{
		rend::ModelRenderer r(720, 720);
		mat4 model = m_entity.lock()->GetTransform()->GetModel();

		((rend::Renderer*)(&r))->model(model);
		//((rend::ModelRenderer*)(&r))->model(m_model);

		r.shader(&m_shader);
		r.model(m_model);
		r.depthTest(true);
		r.backfaceCull(true);
		//r.blend(true);
		r.projection(Camera::GetMainCam()->GetProjection());
		r.view(Camera::GetMainCam()->GetView());
		r.texture(&m_texture);
		//r.mesh(&m_mesh);
		r.render();
	}
}