#pragma once
#include "Mesh.h"
#include "Shader.h"

class Cube
{
public:
	Cube(glm::mat4, glm::mat4);
	~Cube();

	void render();
	GLuint getProgram();
	Shader* getShader() { return shader; }

	void setPosition(glm::vec3);
	void setPosition(GLfloat, GLfloat, GLfloat);
	void positionTo(glm::vec3);
	void positionto(GLfloat, GLfloat, GLfloat);
	void setRotation(GLfloat, glm::vec3);
	void setRotation(GLfloat, GLfloat, GLfloat, GLfloat);
	void rotateTo(GLfloat, glm::vec3);
	void rotateTo(GLfloat, GLfloat, GLfloat, GLfloat);
	void setScale(GLfloat);
	void scaleTo(GLfloat);
	void setColor(glm::vec3);
	void setColor(GLfloat, GLfloat, GLfloat);

	void setLightPos(glm::vec3);
	void setLightPos(GLfloat, GLfloat, GLfloat);
	void setLightColor(glm::vec3);
	void setLightColor(GLfloat, GLfloat, GLfloat);

private:
	Mesh* mesh;
	Shader* shader;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 pos;
	glm::vec3 rotateAxial;
	GLfloat rotateAngle;
	GLfloat scale;
	glm::vec3 color;

	glm::vec3 lightPos;
	glm::vec3 lightColor;
};

