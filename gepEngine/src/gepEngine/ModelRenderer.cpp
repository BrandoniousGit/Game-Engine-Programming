#include "ModelRenderer.h"
#include <iostream>
#include "glmWrap.h"
#include "entity.h"
#include "transform.h"


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

		r.model(m_model);
		r.texture(&m_texture);
		r.shader(&m_shader);
		//r.mesh(&m_mesh);
		r.depthTest(true);
		r.backfaceCull(true);
		r.blend(true);
		r.render();
	}
}