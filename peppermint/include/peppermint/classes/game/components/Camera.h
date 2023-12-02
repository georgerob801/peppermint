#ifndef PPMINT_COMPONENT_CAMERA_H
#define PPMINT_COMPONENT_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <peppermint/classes/game/Component.h>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component for storing camera data.
			/// </summary>
			class Camera : public Component {
			public:
				/// <summary>
				/// A vector representing the up direction relative to the camera.
				/// </summary>
				vec3 up;
				/// <summary>
				/// A vector representing the forwards direction relative to the camera.
				/// </summary>
				vec3 front;
				/// <summary>
				/// A vector representing the right direction relative to the camera.
				/// </summary>
				vec3 right;

				/// <summary>
				/// The orthographic view scale of the camera.
				/// </summary>
				float viewScale = 1.0f;

				/// <summary>
				/// Create a new Camera.
				/// </summary>
				Camera();

				/// <summary>
				/// Get the camera's view matrix based on its position and rotation.
				/// </summary>
				/// <returns></returns>
				mat4 getViewMatrix();
				/// <summary>
				/// Update the up, front, and right vectors based on the camera's current position and rotation.
				/// </summary>
				void updateCameraVectors();

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				/// <summary>
				/// A vector representing the up direction in the world.
				/// </summary>
				vec3 worldUp;
			};
		}
	}
}

#endif