#include "Camera.hpp"
#include "Application.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
glm::vec3 view_up = { 0, 1, 0 };

Camera::Camera(float fov, float nearClip, float farClip)
{
	this->farClip = farClip;
	this->nearClip = nearClip;
	this->fov = fov;
	this->position = { 0, 0, 8 };
	this->lookVector = { 0, 0, -1 };
	this->lastX = 0;
	this->lastY = 0;
	this->pitch = 0;
	this->yaw = 0;
	this->speed = 4.f;
	this->viewportWidth = 1920;
	this->viewportHeight = 1080;
}

void Camera::HandleInput()
{
	
	glm::vec3 delta = {};

	float cam_speed = this->speed * 3 * Application::instance->GetDeltaTime();
    if(glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) cam_speed *= 4;
	if (glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        delta += this->lookVector * cam_speed;
	}

	if (glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        delta -= this->lookVector * cam_speed;
	}

	if (glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {

        delta += glm::normalize(glm::cross(this->lookVector, view_up)) * -cam_speed;
	}

	if (glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {

        delta += glm::normalize(glm::cross(this->lookVector, view_up)) * cam_speed;
	}

	this->position += delta;
}

void Camera::HandleMouseMovement(float xPos, float yPos)
{
	if(glfwGetKey(Application::instance->GetWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) return;
	float xoffset = xPos - this->lastX;
	float yoffset = this->lastY - yPos; 
	this->lastX = xPos;
	this->lastY = yPos;

	xoffset *= this->sensitivity;
	yoffset *= this->sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

    this->lookVector = {        
        cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
    };
}


void Camera::ResizeViewport(int width, int height)
{
    this->viewportWidth = width;
    this->viewportHeight = height;
}

glm::vec3& Camera::GetPosition() { return this->position; }
glm::vec3& Camera::GetLookVector() { return this->lookVector; }

ViewProjection Camera::GetViewProjection() {
	glm::mat4 projection = glm::perspective(this->fov, (float)this->viewportWidth / (float)this->viewportHeight, this->nearClip, this->farClip);
	glm::mat4 view = glm::lookAt(this->position, this->position + this->lookVector, view_up);

	ViewProjection vp = {
		projection = projection,
		view = view
	};
	return vp;
}