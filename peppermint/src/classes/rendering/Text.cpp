#include <peppermint/classes/rendering/Text.h>

#include <peppermint/Exceptions.hpp>

#include <glad/glad.h>

using namespace peppermint::rendering::text;

FT_Library FTManager::ft;
peppermint::rendering::Shader* FTManager::textShader;
vector<Font*> FTManager::fonts;

Character::~Character() {
	delete this->tex;
}

void FTManager::init() {
	if (FT_Init_FreeType(&FTManager::ft)) throw peppermint::exceptions::rendering::text::FreeTypeCannotInitialiseException();

	FTManager::textShader = new Shader(new Asset(Asset::VERTEX_SHADER_SOURCE, (char*)"peppermint/resource/shader/vertex/default.vert"), new Asset(Asset::FRAGMENT_SHADER_SOURCE, (char*)"peppermint/resource/shader/fragment/text.frag"));
}

Font* FTManager::addFont(Asset* fontFile) {
	Font* f = new Font();

	if (FT_New_Face(FTManager::ft, fontFile->path, 0, &f->face)) {
		throw peppermint::exceptions::rendering::text::CannotLoadFaceException();
	}

	f->derivedFrom = fontFile;
	FTManager::fonts.push_back(f);

	return f;
}

Font* FTManager::getFont(Asset* fontFile) {
	vector<Font*>::iterator it = find_if(FTManager::fonts.begin(), FTManager::fonts.end(), [fontFile](Font* item) { return fontFile == item->derivedFrom; });

	if (it == FTManager::fonts.end()) return nullptr;
	return *it;
}

void FTManager::clear() {
	FT_Done_FreeType(FTManager::ft);
}

Font::~Font() {
	map<char, vector<Character*>>::iterator it;

	for (it = this->characters.begin(); it != this->characters.end(); it++) {
		for (vector<Character*>::iterator it2 = this->characters[(*it).first].begin(); it2 != this->characters[(*it).first].end(); it2++) {
			delete *it2;
		}
	}

	FT_Done_Face(this->face);
}

void Font::setFontSize(unsigned int size) {
	this->fontSize = size;
	FT_Set_Pixel_Sizes(this->face, 0, size);
}

Character* Font::getCharacter(char character) {
	return this->getCharacter(character, this->fontSize);
}

Character* Font::getCharacter(char character, unsigned int height) {
	vector<Character*>::iterator index;
	bool doesntExist = false;

	// check if already generated
	if (this->characters.find(character) != this->characters.end()) {
		index = find_if(this->characters[character].begin(), this->characters[character].end(), [character, height](Character* val) { return val->fontHeight == height; });
	} else {
		doesntExist = true;
	}

	if (doesntExist || index == this->characters[character].end()) {
		if (this->lastUsedFontSize != height) {
			FT_Set_Pixel_Sizes(this->face, 0, height);
			this->lastUsedFontSize = height;
		}

		if (FT_Load_Char(this->face, character, FT_LOAD_RENDER)) {
			throw peppermint::exceptions::rendering::text::CannotLoadGlyphException();
		}

		Texture* tex = new Texture();

		tex->bind();
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, this->face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Character* c = new Character {
			.fontHeight = height,
			.size = ivec2(this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows),
			.bearing = ivec2(this->face->glyph->bitmap_left, this->face->glyph->bitmap_top),
			.advance = (unsigned int)this->face->glyph->advance.x,
			.tex = tex
		};

		if (this->characters.find(character) == this->characters.end()) {
			// insert whole new thing
			this->characters.insert(pair<char, vector<Character*>>(character, vector<Character*>()));
		}
		// add character
		this->characters[character].push_back(c);

		return c;
	} else {
		return *index;
	}
}