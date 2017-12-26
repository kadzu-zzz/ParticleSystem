#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>

class ShaderObject {
public:
	ShaderObject(std::string vertexShader, std::string fragmentShader, std::string geometryShader, std::string tesselationControlShader, std::string tesselationEvaluationShader,
				 std::vector<std::string> attributes);
	virtual ~ShaderObject();

	virtual void attach();
	virtual void unattach();
	virtual GLint getUniformLocation(const std::string& uniformName);

	virtual void updateShader() = 0;
protected:
	bool bVertexShader, bFragmentShader, bGeometryShader, bTesselationControlShader, bTesselationEvaluationShader;
	GLuint programID;
	unsigned int numAttribs;

	void compileShader(const std::string &filePath, GLuint id);
};

