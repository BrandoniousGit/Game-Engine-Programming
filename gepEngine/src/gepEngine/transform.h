#include "component.h"
#include <rend/rend.h>
#include "glmWrap.h"

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
		rend::mat4 getModel();
		/**
		* Set the position.
		*
		* \param _position The new position
		*/
		//Setter
		void setPosition(vec3& _position) { m_position = _position; }
		void setRotation(vec3& _rotation) { m_rotation = _rotation; }
		void setScale(vec3& _scale) { m_scale = _scale; }

		//Getters
		vec3 getPosition() { return m_position; }
		vec3 getRotation() { return m_rotation; }
		vec3 getScale() { return m_scale; }

	private:
		void OnTick();

		vec3 m_position = vec3(0.0f); ///< X, Y, Z location of Entity
		vec3 m_rotation = vec3(0.0f); ///< Rotation of Entity in euler angles
		vec3 m_scale = vec3(1.0f); ///< Scale of Entity
	};
}