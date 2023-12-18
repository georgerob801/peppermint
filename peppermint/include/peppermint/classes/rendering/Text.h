#ifndef PPMINT_TEXT_H
#define PPMINT_TEXT_H

#include <peppermint/classes/rendering/Texture.h>
#include <peppermint/classes/rendering/Shader.h>

#include <vector>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace peppermint {
	namespace rendering {
		namespace text {
			class Character {
			public:
				~Character();

				unsigned int fontHeight;
				ivec2 size;
				ivec2 bearing;
				unsigned int advance;
				peppermint::rendering::Texture* tex;
			};

			class Font {
			public:
				~Font();

				string name;
				map<char, vector<Character*>> characters;

				FT_Face face;

				void setFontSize(unsigned int size);

				Character* getCharacter(char character);
				Character* getCharacter(char character, unsigned int height);

				Asset* derivedFrom = nullptr;
			private:
				unsigned int fontSize = 48;
				unsigned int lastUsedFontSize = NULL;
			};

			class FTManager {
			public:
				static FT_Library ft;

				static Shader* textShader;

				static vector<Font*> fonts;

				static void init();
				static Font* addFont(Asset* fontFile);

				static Font* getFont(Asset* fontFile);

				static void clear();
			};
		}
	}
}

#endif