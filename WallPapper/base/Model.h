#pragma once
#include "Mesh.h"
#include "assimp\scene.h"
#include <vector>
#include "Camera.h"

class Model
{
public:
	Model(GLchar* path);
	~Model();
	void draw(Camera *camera, GLfloat ratio);

	void positionTo(GLfloat x, GLfloat y, GLfloat z);
	void scaleTo(GLfloat scale);
	void rotateTo(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);

	Shader* getShader();

private:
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName);
	GLuint loadTextureFromFile(const GLchar *name, string path);

private:
	string directory;
	Shader *shader;

	std::vector<Mesh> meshs;
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scale;
};

