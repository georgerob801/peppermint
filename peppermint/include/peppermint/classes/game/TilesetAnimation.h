#ifndef PPMINT_TILESET_ANIMATION_H
#define PPMINT_TILESET_ANIMATION_H

#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace game {
		class TilesetAnimation {
		public:
			int start = 0;
			int step = 1;
			int end = 1;

			double stepTime = 1.0;

			vec2 uvStartOffset = vec2(0.0f, 0.0f);
			vec2 uvStepOffset = vec2(0.0f, 0.0f);
			int texStartOffset = 0;
			int texStepOffset = 0;

			virtual int stepAtTime(double time);
			int getTextureOffsetAtStep(int step);
			vec2 getUVOffsetAtStep(int step);
		private:
		};
	}
}

#endif