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
			/// <summary>
			/// Component that renders a player tileset. Supports both stationary and moving states in all 4 directions.
			/// </summary>
			class BasicPlayerRenderer : public TilesetRenderer, public TilesetAnimationStateInformation {
			public:
				/// <summary>
				/// Create a new BasicPlayerRenderer.
				/// </summary>
				/// <param name="width">The desired width of the player tileset.</param>
				/// <param name="height">The desired height of the player tileset.</param>
				BasicPlayerRenderer(unsigned int width, unsigned int height);

				/// <summary>
				/// The PlayerController that controls the player this component is attached to. Used to determine animation state.
				/// </summary>
				PlayerController* pc;

				/// <summary>
				/// The TilesetAnimation to play when the player is moving up. Frame 0 is shown when the player is stationary.
				/// </summary>
				TilesetAnimation* up;
				/// <summary>
				/// The TilesetAnimation to play when the player is moving down. Frame 0 is shown when the player is stationary.
				/// </summary>
				TilesetAnimation* down;
				/// <summary>
				/// The TilesetAnimation to play when the player is moving left. Frame 0 is shown when the player is stationary.
				/// </summary>
				TilesetAnimation* left;
				/// <summary>
				/// The TilesetAnimation to play when the player is moving right. Frame 0 is shown when the player is stationary.
				/// </summary>
				TilesetAnimation* right;

				/// <summary>
				/// The start time of the last animation played.
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