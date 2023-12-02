#ifndef PPMINT_COMPONENT_ANIMATED_TILESET_RENDERER_H
#define PPMINT_COMPONENT_ANIMATED_TILESET_RENDERER_H

#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>
#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>
#include <peppermint/classes/game/TilesetAnimation.h>

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// A tileset renderer that supports tileset animations.
			/// </summary>
			class AnimatedTilesetRenderer : public TilesetRenderer, public TilesetAnimationStateInformation {
			public:
				/// <summary>
				/// Create a new AnimatedTilesetRenderer component.
				/// </summary>
				/// <param name="width">The desired witdh of the tileset.</param>
				/// <param name="height">The desired height of the tileset.</param>
				AnimatedTilesetRenderer(unsigned int width, unsigned int height);

				/// <summary>
				/// A vector containing all the animations this tileset can play.
				/// </summary>
				vector<TilesetAnimation*> animations;

				/// <summary>
				/// The index of the current animation.
				/// </summary>
				unsigned int animationIndex = 0;
				/// <summary>
				/// True/false depending on whether an animation should be running.
				/// </summary>
				bool running = true;

				/// <summary>
				/// The last start time of an animation.
				/// </summary>
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