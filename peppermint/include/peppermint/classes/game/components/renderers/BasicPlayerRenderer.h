#ifndef PPMINT_COMPONENT_BASIC_PLAYER_RENDERER_H
#define PPMINT_COMPONENT_BASIC_PLAYER_RENDERER_H

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/game/components/PlayerController.h>
#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>
#include <peppermint/classes/game/TilesetAnimation.h>
#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>

namespace peppermint {
	namespace game {
		namespace components {
			class BasicPlayerRenderer : public TilesetRenderer, public TilesetAnimationStateInformation {
			public:
				BasicPlayerRenderer(unsigned int width, unsigned int height);

				PlayerController* pc;

				TilesetAnimation* up;
				TilesetAnimation* down;
				TilesetAnimation* left;
				TilesetAnimation* right;

				double animationStart = 0;

				void start();
				void loop();
			private:

			};
		}
	}
}

#endif