#pragma once

#include <gl\glew.h>
#include <array>

struct GLTexture {
public:
	GLTexture(GLuint id, unsigned int width, unsigned int height);
	GLTexture(GLuint id, std::array<unsigned int, 2> size);

	GLuint id;
	std::array<unsigned int, 2> size;
};

bool operator ==(const GLTexture& left, const GLTexture& right);
bool operator !=(const GLTexture& left, const GLTexture& right);