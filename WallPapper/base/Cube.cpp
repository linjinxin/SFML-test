#include "Cube.h"
#include "VertData.h"

Cube::Cube(glm::mat4 view, glm::mat4 projection)
{
	this->mesh = new Mesh(vertice_normals, 1, 36, 2, 6, attri_normal_lens);
	this->shader = new Shader("res/cubeVert.vs", "res/cubeFrag.fs");
	this->view = view;
	this->projection = projection;
	this->pos = glm::vec3(0.0f);
	this->rotateAxial = glm::vec3(1.0f);
	this->rotateAngle = 0.0f;
	this->scale = 1.0f;
	this->color = glm::vec3(1.0f);
	this->lightPos = glm::vec3(0.0f);
	this->lightColor = glm::vec3(1.0f);
}

Cube::~Cube()
{
	delete mesh;
	delete shader;
	mesh = nullptr;
	shader = nullptr;
}

void Cube::render()
{
	mesh->bind();
	shader->use();

	glm::mat4 model;
	model = glm::translate(model, this->pos);
	model = glm::rotate(model, glm::radians(this->rotateAngle), this->rotateAxial);
	model = glm::scale(model, glm::vec3(this->scale));

	shader->setUniformMat4f("cubeModel", model);
	shader->setUniformMat4f("view", this->view);
	shader->setUniformMat4f("projection", this->projection);

	shader->setUniformf("ambientStrength", 0.1f);
	shader->setUniformf("diffuseStrength", 0.5f);
	shader->setUniformf("specularStrength", 0.8f);
	shader->setUniformf("specularShininess", 32.0f);
	
	shader->setUniformVec3f("cubeColor", this->color);
	shader->setUniformVec3f("ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setUniformVec3f("lightColor", this->lightColor);

	shader->setUniformVec3f("viewPos", glm::vec3(0, 0, 5));
	shader->setUniformVec3f("lightPos", this->lightPos);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	mesh->unBind();
	shader->unUse();
}

GLuint Cube::getProgram()
{
	return shader->getProgram();
}

void Cube::setPosition(glm::vec3 pos)
{
	this->pos = pos;
}

void Cube::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->pos = glm::vec3(x, y, z);
}

void Cube::positionTo(glm::vec3 pos)
{
	this->pos += pos;
}

void Cube::positionto(GLfloat x, GLfloat y, GLfloat z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
}

void Cube::setRotation(GLfloat angle, glm::vec3 r)
{
	this->rotateAngle = angle;
	this->rotateAxial = r;
}

void Cube::setRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	this->rotateAngle = angle;
	this->rotateAxial= glm::vec3(x, y, z);
}

void Cube::rotateTo(GLfloat angle, glm::vec3 r)
{
	this->rotateAngle += angle;
	this->rotateAxial += r;
}

void Cube::rotateTo(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	this->rotateAngle += angle;
	this->rotateAxial.x += x;
	this->rotateAxial.y += y;
	this->rotateAxial.z += z;
}

void Cube::setScale(GLfloat s)
{
	this->scale = s;
}

void Cube::scaleTo(GLfloat s)
{
	this->scale *= s;
}

void Cube::setColor(glm::vec3 c)
{
	this->color = c;
}

void Cube::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = glm::vec3(r, g, b);
}


void Cube::setLightPos(glm::vec3 pos)
{
	this->lightPos = pos;
}

void Cube::setLightPos(GLfloat x, GLfloat y, GLfloat z)
{
	this->lightPos = glm::vec3(x, y, z);
}

void Cube::setLightColor(glm::vec3 c)
{
	this->lightColor = c;
}

void Cube::setLightColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->lightColor = glm::vec3(r, g, b);
}
