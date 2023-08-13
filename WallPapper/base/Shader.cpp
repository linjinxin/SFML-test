#include "Shader.h"

using namespace std;

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	glProgram = glCreateProgram();
	vertShader = fragShader = 0;

	GLuint stat1 = 0;
	GLuint stat2 = 0;
	if (strlen(vertexPath) > 0)
	{
		stat1 = attachVertexShader(vertexPath);
	}
	if (strlen(fragmentPath) > 0)
	{
		stat2 = attachFragmentShader(fragmentPath);
	}
	if (stat1 == Shader::SUCCESS && stat2 == Shader::SUCCESS)
	{
		linkShader();
	}
}

Shader::~Shader()
{
	glDeleteProgram(glProgram);
}

GLuint Shader::attachVertexShader(const GLchar * vertexPath)
{
	if (vertShader > 0)
	{
		glDetachShader(glProgram, vertShader);
	}
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	return attachShader(vertexPath, vertShader);
}

GLuint Shader::attachFragmentShader(const GLchar * fragmentPath)
{
	if (fragShader > 0)
	{
		glDetachShader(glProgram, fragShader);
	}
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	return attachShader(fragmentPath, fragShader);
}

GLuint Shader::attachShader(const GLchar* path, GLuint &shader)
{
	ifstream file;
	stringstream buffer;
	string str;
	const GLchar* source;

	file.open(path, ios::in);
	buffer << file.rdbuf();
	str = buffer.str();
	source = str.c_str();

	GLint status;
	GLchar errInfo[512];
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shader, 512, NULL, errInfo);
		cout << errInfo << endl;
		return Shader::COMPILE_ERROR;
	}

	glAttachShader(glProgram, shader);
	glDeleteShader(shader);

	return Shader::SUCCESS;
}

GLuint Shader::linkShader()
{
	GLint status;
	GLchar errInfo[512];
	glLinkProgram(glProgram);
	glGetProgramiv(glProgram, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(glProgram, 512, NULL, errInfo);
		cout << errInfo << endl;
		return Shader::LINK_ERROR;
	}

	return Shader::SUCCESS;
}

void Shader::use()
{
	glUseProgram(glProgram);
}

void Shader::unUse()
{
	glUseProgram(0);
}

GLuint Shader::getProgram()
{
	return this->glProgram;
}

void Shader::setUniformf(const char * name, GLfloat value)
{
	GLuint location = glGetUniformLocation(glProgram, name);
	glUniform1f(location, value);
}

void Shader::setUniformMat4f(const char * name, glm::mat4 value)
{
	GLuint location = glGetUniformLocation(glProgram, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformVec4f(const char * name, glm::vec4 value)
{
	GLuint location = glGetUniformLocation(glProgram, name);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setUniformVec3f(const char * name, glm::vec3 value)
{
	GLuint location = glGetUniformLocation(glProgram, name);
	glUniform3fv(location, 1, glm::value_ptr(value));
}