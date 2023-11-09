#ifndef PPMINT_COMPONENT_ANIMATED_TILESET_RENDERER_H
#define PPMINT_COMPONENT_ANIMATED_TILESET_RENDERER_H

#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>
#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>
#include <peppermint/classes/game/TilesetAnimation.h>

namespace peppermint {
	namespace game {
		namespace components {
			class AnimatedTilesetRenderer : public TilesetRenderer, public TilesetAnimationStateInformation {
			public:
				AnimatedTilesetRenderer(unsigned int width, unsigned int height);

				vector<TilesetAnimation*> animations;

				unsigned int animationIndex = 0;
				bool running = true;

				double animationStart = 0;

				void start();
				void loop();

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:

			};
		}
	}
}

#endif