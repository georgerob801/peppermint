#ifndef PPMINT_TILESET_ANIMATION_H
#define PPMINT_TILESET_ANIMATION_H

#include <glm/glm.hpp>
#include <peppermint/classes/Asset.h>

using namespace glm;

namespace peppermint {
	namespace game {
		/// <summary>
		/// Class for storing information regarding tileset animations.
		/// </summary>
		class TilesetAnimation : public Asset {
		public:
			/// <summary>
			/// Create a new TilesetAnimation.
			/// </summary>
			TilesetAnimation() : Asset(ASSET_TYPE::TILESET_ANIMATION) { }

			/// <summary>
			/// The frame to start on.
			/// </summary>
			int start = 0;
			/// <summary>
			/// The amount of frames to progress every step.
			/// </summary>
			int step = 1;
			/// <summary>
			/// The frame to end on.
			/// </summary>
			int end = 1;

			/// <summary>
			/// The time taken for each step.
			/// </summary>
			double stepTime = 1.0;

			/// <summary>
			/// The initial UV offset of this animation.
			/// </summary>
			vec2 uvStartOffset = vec2(0.0f, 0.0f);
			/// <summary>
			/// The amount to offset UV coordinates by each step.
			/// </summary>
			vec2 uvStepOffset = vec2(0.0f, 0.0f);
			/// <summary>
			/// The initial texture set offset of this animation.
			/// </summary>
			int texStartOffset = 0;
			/// <summary>
			/// The amount to offset the texture set index by each step.
			/// </summary>
			int texStepOffset = 0;

			/// <summary>
			/// Get the step of the animation at a given time.
			/// </summary>
			/// <param name="time">The time since the start of the animation.</param>
			/// <returns>The step this animation would be at.</returns>
			virtual int stepAtTime(double time);
			/// <summary>
			/// Get the texture set offset this animation would be at at the specified step.
			/// </summary>
			/// <param name="step">The step to get the texture set offset for.</param>
			/// <returns>The texture set offset at the specified step.</returns>
			int getTextureOffsetAtStep(int step);
			/// <summary>
			/// Get the UV offset at the specified step.
			/// </summary>
			/// <param name="step">The step to get the UV offset for.</param>
			/// <returns>The UV offset at the specified step.</returns>
			vec2 getUVOffsetAtStep(int step);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
		};
	}
}

#endif