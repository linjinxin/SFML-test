#pragma once
#include "Mesh.h"
#include "Shader.h"

class Light
{
public:
	Light(glm::mat4, glm::mat4);
	~Light();

	void setPosition(glm::vec3);
	void setPosition(GLfloat, GLfloat, GLfloat);
	void positionTo(glm::vec3);
	void positionto(GLfloat, GLfloat, GLfloat);
	void setScale(GLfloat);
	void scaleTo(GLfloat);
	void setColor(glm::vec3);
	void setColor(GLfloat, GLfloat, GLfloat);

	void render();

private:
	Mesh* mesh;
	Shader* shader;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 pos;
	GLfloat scale;
	glm::vec3 color;
};

