#include "TextureManger.h"

unordered_map<string, sf::Texture> TextureManger::textures;

void TextureManger::LoadTexture(string filename) {
	string path = "images/";
	path += filename + ".png";

	textures[filename].loadFromFile(path);
}

sf::Texture& TextureManger::GetTexture(string textureName) {

	if (textures.find(textureName) == textures.end()) {
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManger::Clear() {
	textures.clear();
}