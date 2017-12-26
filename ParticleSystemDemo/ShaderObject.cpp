#include "ShaderObject.h"

#include "Exit.h"
#include "Engine.h"
#include "Logger.h"

#include <fstream>

ShaderObject::ShaderObject(std::string vertexShader, std::string fragmentShader, std::string geometryShader, std::string tesselationControlShader, std::string tesselationEvaluationShader,
						   std::vector<std::string> attributes) {
	numAttribs = attributes.size();
	programID = glCreateProgram();

	GLuint vertexShaderID = 0, fragmentShaderID = 0, geometryShaderID = 0, tesselationControlShaderID = 0, tesselationEvaluationShaderID = 0;

	bVertexShader = (vertexShader != "");
	bFragmentShader = (fragmentShader != "");
	bGeometryShader = (geometryShader != "");
	bTesselationControlShader = (tesselationControlShader != "");
	bTesselationEvaluationShader = (tesselationEvaluationShader != "");

	if (bVertexShader) {
		if (!(vertexShaderID = glCreateShader(GL_VERTEX_SHADER)))	pausedExit(ERROR_VERTEX_SHADER_FAILEDTOCOMPILE);
		compileShader(vertexShader, vertexShaderID);
	}
	if (bFragmentShader) {
		if (!(fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER))) pausedExit(ERROR_FRAGMENT_SHADER_FAILEDTOCOMPILE);
		compileShader(fragmentShader, fragmentShaderID);
	}
	if (bGeometryShader) {
		if (!(geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER))) pausedExit(ERROR_GEOMETRY_SHADER_FAILEDTOCOMPILE);
		compileShader(geometryShader, geometryShaderID);
	}
	if (bTesselationControlShader) {
		if (!(tesselationControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER))) pausedExit(ERROR_CONTROL_TESSELATION_SHADER_FAILEDTOCOMPILE);
		compileShader(tesselationControlShader, tesselationControlShaderID);
	}
	if (bTesselationEvaluationShader) {
		if (!(tesselationEvaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER))) pausedExit(ERROR_EVALUATION_TESSELATION_SHADER_FAILEDTOCOMPILE);
		compileShader(tesselationEvaluationShader, tesselationEvaluationShaderID);
	}

	int c = 0;
	for (std::string attrib : attributes) {
		glBindAttribLocation(programID, c, attrib.c_str());
		++c;
	}

	if (bVertexShader) glAttachShader(programID, vertexShaderID);
	if (bFragmentShader) glAttachShader(programID, fragmentShaderID);
	if (bGeometryShader) glAttachShader(programID, geometryShaderID);
	if (bTesselationControlShader) glAttachShader(programID, tesselationControlShaderID);
	if (bTesselationEvaluationShader) glAttachShader(programID, tesselationEvaluationShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(programID);
		if (bVertexShader) glDeleteShader(vertexShaderID);
		if (bFragmentShader) glDeleteShader(fragmentShaderID);
		if (bGeometryShader) glDeleteShader(geometryShaderID);
		if (bTesselationControlShader) glDeleteShader(tesselationControlShaderID);
		if (bTesselationEvaluationShader) glDeleteShader(tesselationEvaluationShaderID);

		printf(&errorLog[0]);
		pausedExit(ERROR_SHADER_FAILEDTOLINK);
	}

	if (bVertexShader) { glDetachShader(programID, vertexShaderID); glDeleteShader(vertexShaderID); }
	if (bFragmentShader) { glDetachShader(programID, fragmentShaderID); glDeleteShader(fragmentShaderID); }
	if (bGeometryShader) { glDetachShader(programID, geometryShaderID); glDeleteShader(geometryShaderID); }
	if (bTesselationControlShader) { glDetachShader(programID, tesselationControlShaderID); glDeleteShader(tesselationControlShaderID); }
	if (bTesselationEvaluationShader) { glDetachShader(programID, tesselationEvaluationShaderID); glDeleteShader(tesselationEvaluationShaderID); }
}

ShaderObject::~ShaderObject() {
	glDeleteProgram(programID);
}

void ShaderObject::attach() {
	glUseProgram(programID);
	for (unsigned int i = 0; i < numAttribs; ++i) {
		glEnableVertexAttribArray(i);
	}
}

void ShaderObject::unattach() {
	glUseProgram(0);
	for (unsigned int i = 0; i < numAttribs; ++i) {
		glDisableVertexAttribArray(i);
	}
}

GLint ShaderObject::getUniformLocation(const std::string & uniformName) {
	GLint location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		StaticLogger->logMessage(LogLevel::WARNING, "BAD UNIFORM VARIABLE: " + uniformName);
	}
	return location;
}

void ShaderObject::compileShader(const std::string & filePath, GLuint id) {
	std::string fileContents = "";
	std::ifstream GLSLShaderFile(filePath);
	if (GLSLShaderFile.fail()) {
		perror(filePath.c_str());
		pausedExit(ERROR_SHADER_FAILEDTOREADFILE);
	}
	std::string line;

	while (std::getline(GLSLShaderFile, line)) {
		fileContents += line + "\n";
	}

	GLSLShaderFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		printf(&errorLog[0]);

		pausedExit(ERROR_SHADER_FAILEDTOCOMPILE);
	}
}
