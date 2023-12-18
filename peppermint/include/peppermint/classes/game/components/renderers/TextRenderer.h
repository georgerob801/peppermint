#ifndef PPMINT_COMPONENT_TEXT_RENDERER_H
#define PPMINT_COMPONENT_TEXT_RENDERER_H

#include <peppermint/classes/game/components/renderers/Renderer.h>

#include <peppermint/classes/rendering/Text.h>

#include <string>

namespace peppermint {
	namespace game {
		namespace components {
			class TextRenderer : public Renderer {
			public:
				TextRenderer();

				void generateVertices();

				string text = "";

				Asset* fontFile = nullptr;

				unsigned int pixelSize = 48;
				float xSpacing = 1.0f;
			private:
				string lastMeshedText = "";
				Asset* lastFontFile = nullptr;
				peppermint::rendering::text::Font* font = nullptr;
			};
		}
	}
}

#endif