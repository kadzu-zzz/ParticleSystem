#include "GenericShaderObject.h"

#include <vector>

auto getAttributes() {
	auto attribs = std::vector<std::string>();

	attribs.push_back("vertexPosition");
	attribs.push_back("vertexUV");
	attribs.push_back("vertexColor");

	return attribs;
}

GenericShaderObject::GenericShaderObject() : ShaderObject("assets/shaders/genericShader2D.vs",
														  "assets/shaders/genericShader2D.fs",
														  "", "", "", getAttributes()) {
}

GenericShaderObject::~GenericShaderObject() {
}

void GenericShaderObject::updateShader(GenericShaderObjectUniform sU) {
	GLint textureLocation = this->getUniformLocation("sample");
	GLint cameraLocation = this->getUniformLocation("P");
	GLint lineMode = this->getUniformLocation("lineMode");

	glUniform1i(textureLocation, sU.texLocation);
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(*sU.cameraMatrix)[0][0]);
	glUniform1i(lineMode, sU.lineMode);
}

void GenericShaderObject::setLineMode(bool value) {
	GLint lineMode = this->getUniformLocation("lineMode");
	glUniform1i(lineMode, value);
}
