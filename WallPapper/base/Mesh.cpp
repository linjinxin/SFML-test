#include "Mesh.h"

#define Iter std::vector<GLuint>::iterator

std::vector<GLuint> Mesh::VBO_List;

/**
* @param vetices 顶点数据
* @param vbo VBO id，这里传进来是因为多个 Mesh 可能共享一个 VBO，如果检测到这个 vbo 已经创建了，则不再创建
* @param vertex_count 顶点个数
* @param attri_count 顶点属性个数
* @param attri_all_len 所有属性总长度（几个）
* @param attri_lens 每个属性长度（几个）
*/

Mesh::Mesh(GLfloat* vertices, GLint vbo, GLint vertex_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens)
{
	use_index = GL_FALSE;

	GLboolean bVBOExist = GL_FALSE;
	for (Iter it = VBO_List.begin(); it != VBO_List.end(); it++)
	{
		if (*it == vbo)
		{
			VBO = vbo;
			bVBOExist = GL_TRUE;
			break;
		}
	}

	glGenVertexArrays(1, &VAO);
	if (!bVBOExist)
	{
		glGenBuffers(1, &VBO);
		VBO_List.push_back(VBO);
	}
	
	glBindVertexArray(VAO);	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (!bVBOExist)
	{
		glBufferData(GL_ARRAY_BUFFER, vertex_count * attri_all_len * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	}

	GLuint offset = 0;
	for (GLuint i = 0; i < attri_count; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attri_lens[i], GL_FLOAT, GL_FALSE, attri_all_len * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		offset += attri_lens[i];
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
* @param vetices 顶点数据
* @param indices 索引数据
* @param vbo VBO id，这里传进来是因为多个 Mesh 可能共享一个 VBO，如果检测到这个 vbo 已经创建了，则不再创建
* @param vertex_count 顶点个数
* @param index_count 索引个数
* @param attri_count 顶点属性个数
* @param attri_all_len 所有属性总长度（几个）
* @param attri_lens 每个属性长度（几个）
*/

Mesh::Mesh(GLfloat * vertices, GLuint* indices, GLint vbo, GLint vertex_count, GLint index_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens)
{
	use_index = GL_TRUE;

	GLboolean bVBOExist = GL_FALSE;
	for (Iter it = VBO_List.begin(); it != VBO_List.end(); it++)
	{
		if (*it == vbo)
		{
			VBO = vbo;
			bVBOExist = GL_TRUE;
			break;
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	if (!bVBOExist)
	{
		glGenBuffers(1, &VBO);
		VBO_List.push_back(VBO);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (!bVBOExist)
	{
		glBufferData(GL_ARRAY_BUFFER, vertex_count * attri_all_len * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	}

	GLuint offset = 0;
	for (GLuint i = 0; i < attri_count; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attri_lens[i], GL_FLOAT, GL_FALSE, attri_all_len * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		offset += attri_lens[i];
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(GLuint), (GLvoid*)indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (use_index)
	{
		glDeleteBuffers(1, &EBO);
	}
}

void Mesh::bind()
{
	glBindVertexArray(VAO);
}

void Mesh::unBind()
{
	glBindVertexArray(0);
}

