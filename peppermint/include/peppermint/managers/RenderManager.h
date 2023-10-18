#ifndef PPMINT_RENDER_MANAGER_H
#define PPMINT_RENDER_MANAGER_H

#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/RenderStack.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace peppermint::rendering;
using namespace peppermint::game::components;

using namespace glm;

namespace peppermint {
	namespace managers {
		class RenderManager {
		public:
			int status;

			Camera* activeCamera;

			RenderStack* activeRenderStack;

			vec4 backgroundColour;

			RenderManager();
			~RenderManager();

			void renderFrame();
		private:

		};
	}
}

#endif