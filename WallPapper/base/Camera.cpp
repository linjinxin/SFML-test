#include "Camera.h"

Camera *Camera::camera;

Camera * Camera::getInstance()
{
	if (!Camera::camera)
	{
		Camera::camera = new Camera();
	}
	return Camera::camera;
}

Camera::Camera()
{
	this->cameraPos = glm::vec3(0, 0, 3);
	this->cameraFront = glm::vec3(0, 0, -1);
	this->cameraUp = glm::vec3(0, 1, 0);

	this->pitch = 0;
	this->yaw = -90.0f;
	this->fov = 45.0f;
	this->_near = 1.0f;
	this->_far = 10.0f;

	this->moveDir = 0;
	this->isOrtho = false;

	this->moveSpeed = 1.0f;
	this->rotateSpeed = 0.1f;
}

Camera::~Camera()
{
}

void Camera::startMove(DIR dir)
{
	this->moveDir |= dir;
}

void Camera::stopMove(DIR dir)
{
	this->moveDir ^= dir;
}

void Camera::updatePos(GLfloat delta)
{
	if (this->moveDir & DIR::LEFT)
	{
		this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->moveSpeed * delta;
	}
	else if (this->moveDir & DIR::RIGHT)
	{
		this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->moveSpeed * delta;
	}
	if (this->moveDir & DIR::BACK)
	{
		this->cameraPos -= this->cameraFront * this->moveSpeed * delta;
	}
	else if (this->moveDir & DIR::FRONT)
	{
		this->cameraPos += this->cameraFront * this->moveSpeed * delta;
	}
}

void Camera::updateDir(GLfloat xOffset, GLfloat yOffset)
{
	this->pitch += yOffset * this->rotateSpeed;
	this->yaw -= xOffset * this->rotateSpeed;

	if (this->pitch < -89.0f)
	{
		this->pitch - -89.0f;
	}
	else if (this->pitch > 89.0f)
	{
		this->pitch = 89.0f;
	}

	GLfloat pitch_r = glm::radians(this->pitch);
	GLfloat yaw_r = glm::radians(this->yaw);
	GLfloat pitch_xz = cos(pitch_r);
	this->cameraFront.y = sin(pitch_r);
	this->cameraFront.x = cos(yaw_r) * pitch_xz;
	this->cameraFront.z = sin(yaw_r) * pitch_xz;
	this->cameraFront = glm::normalize(this->cameraFront);
}

void Camera::updateFov(GLfloat offset)
{
	this->fov += offset;
	if (this->fov < 10.0f)
	{
		this->fov = 10.0f;
	}
	else if (this->fov > 135.0f)
	{
		this->fov = 135.0f;
	}
}

glm::mat4 Camera::getCameraView()
{
	return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

glm::mat4 Camera::getCameraProjection(GLfloat ratio)
{
	if (this->isOrtho)
	{
		return glm::ortho(-ratio, ratio, -1.0f, 1.0f, _near, _far);
	}
	else
	{
		return glm::perspective(this->getCameraFov(), ratio, _near, _far);
	}
}

GLfloat Camera::getCameraFov()
{
	return glm::radians(this->fov);
}

glm::vec3 Camera::getCameraPostion()
{
	return this->cameraPos;
}

glm::vec3 Camera::getCameraFront()
{
	return this->cameraFront;
}

void Camera::setIsOrtho(GLboolean isOrtho)
{
	this->isOrtho = isOrtho;
}

void Camera::setCameraPosition(glm::vec3 position)
{
	this->cameraPos = position;
}

void Camera::setCameraPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->cameraPos.x = x;
	this->cameraPos.y = y;
	this->cameraPos.z = z;
}

void Camera::setCameraFront(glm::vec3 front)
{
	this->cameraFront = front;
}

void Camera::setCameraFront(GLfloat x, GLfloat y, GLfloat z)
{
	this->cameraFront.x = x;
	this->cameraFront.y = y;
	this->cameraFront.z = z;
}

void Camera::setCameraFov(GLfloat fov)
{
	this->fov = fov;
}

void Camera::setMoveSpeed(GLfloat speed)
{
	this->moveSpeed = speed;
}

void Camera::setRotateSpeed(GLfloat speed)
{
	this->rotateSpeed = speed;
}

