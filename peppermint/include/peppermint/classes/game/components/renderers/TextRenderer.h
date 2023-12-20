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

				string getText();
				void setText(string text);

				/// <summary>
				/// The Asset of the Font this TextRenderer uses.
				/// </summary>
				Asset* fontFile = nullptr;

				/// <summary>
				/// The height (in pixels) to render the font at.
				/// </summary>
				unsigned int pixelSize = 48;
				/// <summary>
				/// Kerning
				/// </summary>
				float xSpacing = 1.0f;
				/// <summary>
				/// Line height
				/// </summary>
				float ySpacing = 1.0f;

				bool autoWrapX = true;
				float maxWidth = 800.0f;

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				string lastMeshedText = "";
				Asset* lastFontFile = nullptr;
				peppermint::rendering::text::Font* font = nullptr;

				/// <summary>
				/// Stores the text this TextRenderer displays.
				/// </summary>
				string text = "";
			};
		}
	}
}

#endif