#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Camera
{
public:
	enum DIR
	{
		LEFT = 1,
		RIGHT = 2,
		FRONT = 4,
		BACK = 8,
	};

public:
	static Camera* getInstance();

	Camera();
	~Camera();

	void startMove(DIR dir);
	void stopMove(DIR dir);
	void updatePos(GLfloat delta);
	void updateDir(GLfloat xOffset, GLfloat yOffset);
	void updateFov(GLfloat offset);

	glm::mat4 getCameraView();
	glm::mat4 getCameraProjection(GLfloat ratio);
	GLfloat getCameraFov();
	glm::vec3 getCameraPostion();
	glm::vec3 getCameraFront();

	void setIsOrtho(GLboolean isOrtho);
	void setCameraPosition(glm::vec3 position);
	void setCameraPosition(GLfloat x, GLfloat y, GLfloat z);
	void setCameraFront(glm::vec3 front);
	void setCameraFront(GLfloat x, GLfloat y, GLfloat z);
	void setCameraFov(GLfloat fov);
	void setMoveSpeed(GLfloat speed);
	void setRotateSpeed(GLfloat speed);

private:
	static Camera *camera;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat fov;
	GLfloat _near;
	GLfloat _far;

	GLboolean isOrtho;

	GLuint moveDir;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
};

