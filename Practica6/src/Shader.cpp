#include "Shader.h"



using namespace std;



Shader::Shader(const string &vertexShader, const string &fragmentShader) : program(0)
{
	//Shader::program = 0;

	// create vertex shader
	int retCode = GL_FALSE;
	//Shader :: errorLog[1024];
	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderC = vertexShader.c_str();
	glShaderSource(vs, 1, &vertexShaderC, nullptr);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(vs, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	// create fragment shader
	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderC = fragmentShader.c_str();
	glShaderSource(fs, 1, &fragmentShaderC, nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(fs, sizeof(errorLog), nullptr, errorLog);

		return;

	}

	Shader::program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	//delete shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	glGetProgramiv(program, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
		return;
	}

	Shader::vposLoc = glGetAttribLocation(program, "vpos");
	Shader::vtexLoc = glGetAttribLocation(program, "vtex");
	Shader::vnormalLoc = glGetAttribLocation(program, "vnormal");

}
Shader::~Shader() {
	if (program != 0)
		glDeleteProgram(program);

}
uint32_t Shader::getId() const
{
	
	return program;
}

const char * Shader::getError() const
{
	return errorLog;
}

void Shader::use() const
{
	glUseProgram(program);
}

void Shader::setupAttribs() const
{
	if (vposLoc != -1) {
		glEnableVertexAttribArray(vposLoc);
		glVertexAttribPointer(vposLoc, 3, GL_FLOAT, false, sizeof(float) * 8, reinterpret_cast<void*>(offsetof(Vertex, pos)));
	}
	if (vtexLoc != -1) {
		glEnableVertexAttribArray(vtexLoc);
		glVertexAttribPointer(vtexLoc, 2, GL_FLOAT, false, sizeof(float) * 8, reinterpret_cast<void*>(offsetof(Vertex, uvTex)));
	}
	if (vnormalLoc != -1) {
		glEnableVertexAttribArray(vnormalLoc);
		glVertexAttribPointer(vnormalLoc, 3, GL_FLOAT, false, sizeof(float) * 8, reinterpret_cast<void*>(offsetof(Vertex, normal)));
	}
}

int Shader::getLocation(const char * name) const
{
	return  glGetUniformLocation(Shader::program, name);
}

void Shader::setInt(int loc, int val)
{
	if (loc >= 0) {
		glUniform1i(loc, val);

	}
}

void Shader::setFloat(int loc, float val)
{
	if (loc >= 0) {
		glUniform1f(loc, val);

	}
}

void Shader::setVec3(int loc, const glm::vec3 & vec)
{
	if (loc >= 0) {
		glUniform3f(loc, vec.x, vec.y, vec.z);


	}
}

void Shader::setVec4(int loc, const glm::vec4 & vec)
{
	if (loc >= 0) {
		glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);


	}
}

void Shader::setMatrix(int loc, const glm::mat4 & matrix)
{
	if (loc >= 0) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));

	}

}
