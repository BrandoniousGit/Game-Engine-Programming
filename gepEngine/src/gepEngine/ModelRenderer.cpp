#include "ModelRenderer.h"
#include <iostream>
#include "GlmWrap.h"
#include "Entity.h"
#include "Transform.h"


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
		r.projection(rend::perspective(45.0f, 1.0f, 0.01f, 100.0f));
		r.texture(&m_texture);
		//r.mesh(&m_mesh);
		r.render();
	}
}