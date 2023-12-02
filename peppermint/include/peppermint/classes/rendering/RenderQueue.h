#ifndef PPMINT_RENDER_STACK_H
#define PPMINT_RENDER_STACK_H

#include <peppermint/classes/rendering/Shader.h>
#include <peppermint/classes/rendering/Mesh.h>
#include <peppermint/classes/game/GameObject.h>
#include <vector>

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Struct containing information about a thing to render.
		/// </summary>
		struct RenderItem {
			/// <summary>
			/// A pointer to the Shader to use.
			/// </summary>
			Shader* shader = nullptr;
			/// <summary>
			/// A pointer to the thing's GameObject.
			/// </summary>
			peppermint::game::GameObject* go = nullptr;
			/// <summary>
			/// A pointer to the Mesh to use.
			/// </summary>
			Mesh* mesh = nullptr;
			/// <summary>
			/// The global UV offset to use.
			/// </summary>
			vec2 uvOffset = vec2(0.0f, 0.0f);
			/// <summary>
			/// The index fo the texture set to use.
			/// </summary>
			int textureToUse = 0;
			/// <summary>
			/// A pointer to the WorldManager this thing came from.
			/// </summary>
			void* fromWorld = nullptr;
		};

		class RenderQueue {
		public:
			/// <summary>
			/// A vector of the items that require rendering.
			/// </summary>
			std::vector<RenderItem> renderItems;
		};
	}
}

#endif