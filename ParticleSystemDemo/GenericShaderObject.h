#pragma once

#include "ShaderObject.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

struct GenericShaderObjectUniform {
	GLint texLocation;
	glm::mat4x4* cameraMatrix;
	GLboolean lineMode;

	GenericShaderObjectUniform(glm::mat4x4* cameraMatrix, GLboolean lineMode = false, GLint texLocation = 0) :
		cameraMatrix(cameraMatrix), lineMode(lineMode), texLocation(texLocation) {
	}
};

class GenericShaderObject :
	public ShaderObject {
public:
	GenericShaderObject();
	virtual ~GenericShaderObject();

	virtual void updateShader(GenericShaderObjectUniform sU);

	void setLineMode(bool value);
private:
	virtual void updateShader() {}
};

