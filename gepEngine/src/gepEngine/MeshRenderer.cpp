#include "MeshRenderer.h"
#include <iostream>
#include "GlmWrap.h"
#include "Entity.h"
#include "Transform.h"
#include "Camera.h"


namespace gepEngine
{
	MeshRenderer::MeshRenderer() :
		m_renderer(720, 720),
		m_shader("../resources/shaders/basic.vert", "../resources/shaders/basic.frag")
	{}

	void MeshRenderer::SetTexture(std::shared_ptr<Texture> _texture)
	{
		m_texture = _texture;
	}

	void MeshRenderer::SetModel(std::shared_ptr<Model> _model)
	{
		m_model = _model;
	}

	void MeshRenderer::OnDisplay()
	{
		mat4 model = m_entity.lock()->GetTransform()->GetModel();

		m_renderer.projection(Camera::GetMainCam()->GetProjection());
		m_renderer.view(Camera::GetMainCam()->GetView());

		((rend::Renderer*)(&m_renderer))->model(model);

		m_renderer.shader(&m_shader);
		m_renderer.model(m_model->m_model.get());
		m_renderer.depthTest(true);
		m_renderer.backfaceCull(true);
		m_renderer.blend(true);

		m_renderer.texture(m_texture->m_texture.get());
		m_renderer.render();
	}
}