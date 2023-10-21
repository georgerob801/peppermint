#ifndef PPMINT_RENDER_STACK_H
#define PPMINT_RENDER_STACK_H

#include <peppermint/classes/rendering/Shader.h>
#include <peppermint/classes/rendering/Mesh.h>
#include <vector>

namespace peppermint {
	namespace rendering {
		struct RenderItem {
			Shader* shader;
			Mesh* mesh;
		};

		class RenderStack {
		public:
			std::vector<RenderItem> renderItems;
			
			void processRenderItems();
		};
	}
}

#endif