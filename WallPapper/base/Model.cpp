#include "Model.h"
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"
#include "SOIL\SOIL.h"
#include "stbi\stb_image.h"

Model::Model(GLchar * path)
{
	shader = new Shader("res/vert.vs", "res/frag.fs");
	pos = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1.0f);

	this->loadModel(path);
}

Model::~Model()
{
}

void Model::loadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << importer.GetErrorString() << endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of("/"));
	//从根结点开始解析
	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		GLuint inx = node->mMeshes[i];
		aiMesh *mesh = scene->mMeshes[inx];
		this->meshs.push_back(processMesh(mesh, scene));
	}
	//递归解析子结点
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 pos;
		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;
		vertex.position = pos;

		glm::vec3 norm;
		norm.x = mesh->mNormals[i].x;
		norm.y = mesh->mNormals[i].y;
		norm.z = mesh->mNormals[i].z;
		vertex.normal = norm;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texc;
			texc.x = mesh->mTextureCoords[0][i].x;
			texc.y = mesh->mTextureCoords[0][i].y;
			vertex.texcoords = texc;
		}
		else
		{
			vertex.texcoords = glm::vec2(0, 0);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * material, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString name;
		Texture texture;
		material->GetTexture(type, i, &name);
		texture.id = loadTextureFromFile(name.C_Str(), directory);
		texture.type = typeName;
		texture.name = name;
		textures.push_back(texture);
	}
	return textures;
}

GLuint Model::loadTextureFromFile(const GLchar * name, string path)
{
	GLchar str[1024];
	sprintf_s(str, "%s/%s", path.c_str(), name);
	//return SOIL_load_OGL_texture(str, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT);

	GLuint TexObj;
	GLint width, height, nChannels;

	glGenTextures(1, &TexObj);
	glBindTexture(GL_TEXTURE_2D, TexObj);

	//GLubyte *image = SOIL_load_image(/*(path + "/" + name).c_str(),*/str, &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)image);
	//SOIL_free_image_data(image);

	stbi_uc *image = stbi_load(str, &width, &height, &nChannels, 0);
	GLenum format = nChannels == 4 ? GL_RGBA : (nChannels == 3 ? GL_RGB : GL_RED);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid*)image);
	stbi_image_free(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return TexObj;
}

void Model::draw(Camera *camera, GLfloat ratio)
{
	glm::mat4 transform;
	transform = glm::translate(transform, pos);
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	transform = glm::scale(transform, glm::vec3(scale));

	shader->use();
	shader->setUniformMat4f("model", transform);
	shader->setUniformMat4f("view", camera->getCameraView());
	shader->setUniformMat4f("projection", camera->getCameraProjection(ratio));

	for (vector<Mesh>::iterator it = meshs.begin(); it != meshs.end(); it++)
	{
		it->draw(*shader);
	}

	shader->unUse();
}

void Model::positionTo(GLfloat x, GLfloat y, GLfloat z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
}

void Model::scaleTo(GLfloat scale)
{
	this->scale *= scale;
}

void Model::rotateTo(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis)
{
	this->rotation.x += xAxis;
	this->rotation.y += yAxis;
	this->rotation.z += zAxis;
}

Shader* Model::getShader()
{
	return shader;
}
