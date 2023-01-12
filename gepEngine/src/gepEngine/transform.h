#include "Component.h"
#include <rend/rend.h>
#include "GlmWrap.h"

namespace gepEngine
{
	/**
 * Component providing position information of the Entity.
 */
	struct Transform : Component
	{
	public:
		/**
		* Generate the model matrix based on the position, rotation and
		* scale.
		*
		* \return The generated model matrix
		*/
		rend::mat4 GetModel();

		/**
		 * @brief Sets the position of a transform
		 * @param _position 
		*/
		void SetPosition(const vec3& _position) { m_position = _position; }
		/**
		 * @brief Sets the rotation of a transform
		 * @param _rotation
		*/
		void SetRotation(const vec3& _rotation) { m_rotation = _rotation; }
		/**
		 * @brief Sets the scale of a transform
		 * @param _scale
		*/
		void SetScale(const vec3& _scale) { m_scale = _scale; }

		/**
		 * @brief Adds to the current transforms position
		 * @param _position 
		*/
		void AddPosition(const vec3& _position) { m_position += _position; }
		/**
		 * @brief Adds to the current transforms rotation
		 * @param _rotation 
		*/
		void AddRotation(const vec3& _rotation) { m_rotation += _rotation; }
		/**
		 * @brief Adds to the current transforms scale
		 * @param _scale 
		*/
		void AddScale(const vec3& _scale) { m_scale += _scale; }

		/**
		 * @brief Returns the position of a transform
		 * @return 
		*/
		const vec3 GetPosition() { return m_position; }
		/**
		 * @brief Returns the rotation of a transform
		 * @return
		*/
		const vec3 GetRotation() { return m_rotation; }
		/**
		 * @brief Returns the scale of a transform
		 * @return
		*/
		const vec3 GetScale() { return m_scale; }

	private:
		vec3 m_position = vec3(0.0f); ///< X, Y, Z location of Entity
		vec3 m_rotation = vec3(0.0f); ///< Rotation of Entity in euler angles
		vec3 m_scale = vec3(1.0f); ///< Scale of Entity
	};
}