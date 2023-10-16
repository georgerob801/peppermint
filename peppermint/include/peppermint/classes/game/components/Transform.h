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
			class Transform : public Component {
			public:
				vec3 position;
				quat rotation;
				vec3 scale;

				Transform();
			private:

			};
		}
	}
}

#endif