#pragma once

#include <GL\glew.h>

struct Vertex;

class VBO {
public:
	VBO();
	~VBO();

	void initialise();

	void bindBuffer();
	void unbindBuffer();
	void bindVertexArray();
	void unbindVertexArray();

	void bufferData(Vertex * verts, unsigned int size, unsigned int BufferMode = GL_DYNAMIC_DRAW);

	void render(unsigned int size, GLenum renderMode);
	void render(unsigned int offset, unsigned int size, GLenum renderMode);
private:
	GLuint vbo;
	GLuint vao;
};

