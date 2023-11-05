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
			class Camera : public Component {
			public:
				vec3 up;
				vec3 front;
				vec3 right;

				float viewScale = 1.0f;

				Camera();

				mat4 getViewMatrix();
				void updateCameraVectors();

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				vec3 worldUp;
			};
		}
	}
}

#endif