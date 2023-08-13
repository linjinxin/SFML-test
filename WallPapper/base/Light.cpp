#include "Light.h"
#include "VertData.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Light::Light(glm::mat4 view, glm::mat4 projection)
{
	this->mesh = new Mesh(NULL, 1, 36, 1, 6, attri_lens);
	this->shader = new Shader("res/lightVert.vs", "res/lightFrag.fs");
	this->view = view;
	this->projection = projection;
	this->pos = glm::vec3(0.0f);
	this->scale = 1.0f;
	this->color = glm::vec3(1.0f);
}

Light::~Light()
{
	delete mesh;
	delete shader;
	mesh = nullptr;
	shader = nullptr;
}

void Light::setPosition(glm::vec3 pos)
{
	this->pos = pos;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->pos = glm::vec3(x, y, z);
}

void Light::positionTo(glm::vec3 pos)
{
	this->pos += pos;
}

void Light::positionto(GLfloat x, GLfloat y, GLfloat z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
}

void Light::setScale(GLfloat s)
{
	this->scale = s;
}

void Light::scaleTo(GLfloat s)
{
	this->scale *= s;
}

void Light::setColor(glm::vec3 c)
{
	this->color = c;
}

void Light::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = glm::vec3(r, g, b);
}

void Light::render()
{
	mesh->bind();
	shader->use();

	glm::mat4 model;
	model = glm::translate(model, this->pos);
	model = glm::scale(model, glm::vec3(this->scale));

	shader->setUniformMat4f("view", this->view);
	shader->setUniformMat4f("projection", this->projection);
	shader->setUniformMat4f("lightModel", model);
	shader->setUniformVec3f("lightColor", this->color);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	mesh->unBind();
	shader->unUse();
}
