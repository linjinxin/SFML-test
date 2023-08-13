#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	Mesh(GLfloat* vertices, GLint vbo, GLint vertex_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens);
	Mesh(GLfloat* vertices, GLuint* indices, GLint vbo, GLint vertex_count, GLint index_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens);
	~Mesh();

	void bind();
	void unBind();

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLboolean use_index;

	static std::vector<GLuint> VBO_List;
};

