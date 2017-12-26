#include "GLTexture.h"

GLTexture::GLTexture(GLuint id, unsigned int width, unsigned int height) : id(id), size({ width,height }) {
}

GLTexture::GLTexture(GLuint id, std::array<unsigned int, 2> size) : id(id), size(size) {
}

bool operator==(const GLTexture & left, const GLTexture & right) {
	return left.id == right.id;
}

bool operator!=(const GLTexture & left, const GLTexture & right) {
	return left.id != right.id;
}
