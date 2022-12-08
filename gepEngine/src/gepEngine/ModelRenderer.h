#ifndef GEPENGINE_MODELRENDERER_H
#define GEPENGINE_MODELRENDERER_H

#include "component.h"
#include <rend/rend.h>

namespace gepEngine
{
	struct ModelRenderer : Component
	{
		ModelRenderer();

	private:
		rend::Shader m_shader;
		rend::Mesh m_mesh;
		rend::Texture m_texture;
		rend::Model* m_model;

		void OnDisplay();
	};
}
#endif