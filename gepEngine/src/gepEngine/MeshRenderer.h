#ifndef GEPENGINE_MESHRENDERER_H
#define GEPENGINE_MESHRENDERER_H

#include "Component.h"
#include "Models.h"
#include "Textures.h"
#include <rend/rend.h>
#include <string>

namespace gepEngine
{
	struct MeshRenderer : Component
	{
		/**
		 * @brief Constructor
		*/
		MeshRenderer();

		/**
		 * @brief Sets the texture on a given meshrenderer
		 * @param _texture 
		*/
		void SetTexture(std::shared_ptr<Textures> _texture);
		/**
		 * @brief Sets the model on a given meshrenderer
		 * @param _model 
		*/
		void SetModel(std::shared_ptr<Models> _model);

	private:
		rend::Model* m_model;
		rend::Shader m_shader;
		rend::Texture* m_texture;
		rend::ModelRenderer m_renderer;

		void OnDisplay();
	};
}
#endif