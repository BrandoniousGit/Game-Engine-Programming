#ifndef GEPENGINE_MESHRENDERER_H
#define GEPENGINE_MESHRENDERER_H

#include "Component.h"
#include "Model.h"
#include "Texture.h"
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
		void SetTexture(std::shared_ptr<Texture> _texture);
		/**
		 * @brief Sets the model on a given meshrenderer
		 * @param _model 
		*/
		void SetModel(std::shared_ptr<Model> _model);

	private:
		std::shared_ptr<Model> m_model;
		rend::Shader m_shader;
		std::shared_ptr<Texture> m_texture;
		rend::ModelRenderer m_renderer;

		void OnDisplay();
	};
}
#endif