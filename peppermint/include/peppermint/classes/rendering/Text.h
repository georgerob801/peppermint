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
				/// <summary>
				/// Destroy this character.
				/// </summary>
				~Character();

				/// <summary>
				/// The height (in pixels) that this Character was rendered at.
				/// </summary>
				unsigned int fontHeight;
				/// <summary>
				/// The size of this Character.
				/// </summary>
				ivec2 size;
				/// <summary>
				/// The bearing of this Character.
				/// </summary>
				ivec2 bearing;
				/// <summary>
				/// The advance of this Character.
				/// </summary>
				unsigned int advance;
				/// <summary>
				/// A pointer to the Texture that represents this Character.
				/// </summary>
				peppermint::rendering::Texture* tex;
			};

			class Font {
			public:
				/// <summary>
				/// Destroy this Font.
				/// </summary>
				~Font();

				/// <summary>
				/// The name of this Font.
				/// </summary>
				string name;
				/// <summary>
				/// A map of chars to Characters.
				/// </summary>
				map<char, vector<Character*>> characters;

				/// <summary>
				/// The FreeType fontface.
				/// </summary>
				FT_Face face;

				/// <summary>
				/// Set the size this Font should be rendered at.
				/// </summary>
				/// <param name="size"></param>
				void setFontSize(unsigned int size);

				/// <summary>
				/// Get a character.
				/// </summary>
				/// <param name="character">The character to get.</param>
				/// <returns>A pointer to the Character.</returns>
				Character* getCharacter(char character);
				/// <summary>
				/// Get a character at a size.
				/// </summary>
				/// <param name="character">The character to get.</param>
				/// <param name="height">The pixel height to render the character at.</param>
				/// <returns>A pointer to the Character.</returns>
				Character* getCharacter(char character, unsigned int height);

				/// <summary>
				/// The Asset this Font was derived from.
				/// </summary>
				Asset* derivedFrom = nullptr;
			private:
				unsigned int fontSize = 48;
				unsigned int lastUsedFontSize = NULL;
			};

			class FTManager {
			public:
				/// <summary>
				/// The FT_Library
				/// </summary>
				static FT_Library ft;

				/// <summary>
				/// A pointer to the Shader that text uses.
				/// </summary>
				static Shader* textShader;

				/// <summary>
				/// Pointers to all the Fonts registered.
				/// </summary>
				static vector<Font*> fonts;

				/// <summary>
				/// Initialise the FT_Manager
				/// </summary>
				static void init();
				/// <summary>
				/// Register a Font.
				/// </summary>
				/// <param name="fontFile">The font file Asset.</param>
				/// <returns>A pointer to the font</returns>
				static Font* addFont(Asset* fontFile);
				/// <summary>
				/// Get a registered Font.
				/// </summary>
				/// <param name="fontFile">The font file Asset.</param>
				/// <returns>A pointer to the font.</returns>
				static Font* getFont(Asset* fontFile);
				/// <summary>
				/// Close the FT_Library.
				/// </summary>
				static void clear();
			};
		}
	}
}

#endif