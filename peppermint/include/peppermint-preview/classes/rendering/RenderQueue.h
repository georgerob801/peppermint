#ifndef PPMINT_RENDER_STACK_H
#define PPMINT_RENDER_STACK_H

#include <peppermint-preview/classes/rendering/Shader.h>
#include <peppermint-preview/classes/rendering/Mesh.h>
#include <peppermint-preview/classes/game/GameObject.h>
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
			/// The index of the texture set to use.
			/// </summary>
			int textureToUse = 0;
			/// <summary>
			/// A pointer to the WorldManager this thing came from.
			/// </summary>
			void* fromWorld = nullptr;
		};

		struct TextRenderItem : public RenderItem {
			/// <summary>
			/// The colour to render the text.
			/// </summary>
			vec3 colour;
			/// <summary>
			/// The textures to use to render the text.
			/// </summary>
			vector<Texture*> textures;
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