#pragma once

#include "GLTexture.h"
#include "Texture.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

class TextureAsset {
public:
	static TextureResource getTexture(std::string filename, bool atlasTexture = true, GLenum forceDifferentWrapping = GL_CLAMP_TO_EDGE);

private:
	static std::vector<Texture*> textures;
	static std::vector<AtlasTexture*> atlasTextures;

	static GLTexture loadTexture(std::string filename, GLenum wrapping);
};

