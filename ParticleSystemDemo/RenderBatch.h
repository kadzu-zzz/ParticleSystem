#pragma once

#include "Glyph.h"

struct RenderBatch {
	RenderBatch(GLTexture* texture, GLenum renderMode, unsigned int offset = 0, unsigned int size = 0) : texture(texture), renderMode(renderMode), offset(offset), size(size) {
	}

	GLTexture* texture;
	GLenum renderMode;

	unsigned int offset;
	unsigned int size;
};