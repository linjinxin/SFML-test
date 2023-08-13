#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	GLuint attachVertexShader(const GLchar* vertexPath);
	GLuint attachFragmentShader(const GLchar* fragmentPath);
	GLuint linkShader();
	void use();
	void unUse();

	GLuint getProgram();
	void setUniformf(const char* name, GLfloat value);
	void setUniformMat4f(const char* name, glm::mat4 value);
	void setUniformVec4f(const char* name, glm::vec4 value);
	void setUniformVec3f(const char* name, glm::vec3 value);

private:
	GLuint attachShader(const GLchar* path, GLuint &shader);

private:
	GLuint glProgram;
	GLuint vertShader;
	GLuint fragShader;

public:
	static const int SUCCESS = 1;
	static const int COMPILE_ERROR = 2;
	static const int LINK_ERROR = 3;
};

#endif // !__SHADER_H__

