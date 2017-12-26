#include "VBO.h"

#include "Vertex.h"

VBO::VBO() : vbo(0), vao(0) {
}

VBO::~VBO() {
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
}

void VBO::initialise() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex::setAttributes();

	glBindVertexArray(0);
}

void VBO::bindBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbindBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bindVertexArray() {
	glBindVertexArray(vao);
}

void VBO::unbindVertexArray() {
	glBindVertexArray(0);
}

void VBO::bufferData(Vertex * verts, unsigned int size, unsigned int BufferMode) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//MABYE THIS SHOULD BE gl_dynamic_draw
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), nullptr, BufferMode);
	//Buffer Orphan Black Magic
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vertex), verts);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::render(unsigned int size, GLenum renderMode) {
	glDrawArrays(renderMode, 0, size);
}

void VBO::render(unsigned int offset, unsigned int size, GLenum renderMode) {
	glDrawArrays(renderMode, offset, size);
}
