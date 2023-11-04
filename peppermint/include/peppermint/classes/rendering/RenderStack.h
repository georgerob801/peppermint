#ifndef PPMINT_RENDER_STACK_H
#define PPMINT_RENDER_STACK_H

#include <peppermint/classes/rendering/Shader.h>
#include <peppermint/classes/rendering/Mesh.h>
#include <peppermint/classes/game/GameObject.h>
#include <vector>

namespace peppermint {
	namespace rendering {
		struct RenderItem {
			Shader* shader = nullptr;
			peppermint::game::GameObject* go = nullptr;
			Mesh* mesh = nullptr;
			vec2 uvOffset = vec2(0.0f, 0.0f);
			int textureToUse = 0;
		};

		class RenderStack {
		public:
			std::vector<RenderItem> renderItems;
			
			void processRenderItems();
		};
	}
}

#endif