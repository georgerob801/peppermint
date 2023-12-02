#ifndef PPMINT_COMPONENT_TRANSFORM_H
#define PPMINT_COMPONENT_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <peppermint/classes/game/Component.h>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component for storing position, rotation, and scale of GameObjects.
			/// </summary>
			class Transform : public Component {
			public:
				/// <summary>
				/// Vector containing local position.
				/// </summary>
				vec3 position;
				/// <summary>
				/// Vector containing local rotation in euler angles.
				/// </summary>
				vec3 rotation;
				/// <summary>
				/// Vector containing local scale.
				/// </summary>
				vec3 scale;

				/// <summary>
				/// Pointer to the Transform component that is this component's parent.
				/// </summary>
				Transform* parent = nullptr;

				/// <summary>
				/// Create a new Transform component.
				/// </summary>
				Transform();

				/// <summary>
				/// Gets the scale of this Transform relative to the world.
				/// </summary>
				/// <returns>A vector of this Transform's scale with all parent scales applied.</returns>
				vec3 getGlobalScale();
				/// <summary>
				/// Gets the rotation of this Transform relative to the world.
				/// </summary>
				/// <returns>A vector of this Transform's rotation with all parent rotations applied.</returns>
				vec3 getGlobalRotation();
				/// <summary>
				/// Gets the position of this Transform relative to the world.
				/// </summary>
				/// <returns>A vector of this Transform's position wiht all parent positions applied.</returns>
				vec3 getGlobalPosition();

				/// <summary>
				/// Get the transform matrix of this Transform for rendering.
				/// </summary>
				/// <returns>This Transform's transform matrix.</returns>
				mat4 getMatrix();

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			};
		}
	}
}

#endif