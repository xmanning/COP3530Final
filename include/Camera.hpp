#pragma once
#include <glm/glm.hpp>
#include "Common.hpp"
#include "ViewProjection.hpp"

class Camera
{
	float fov;
	glm::vec3 position;
	glm::vec3 lookVector;
	float nearClip;
	float farClip;
	float pitch, yaw;
	float lastX, lastY;
	float speed;
	float viewportWidth, viewportHeight;
	float sensitivity;
public:
    Camera(float fov, float nearClip, float farClip);
    void HandleInput();
    void ResizeViewport(int width, int height);
    void HandleMouseMovement(float xPos, float yPos);
    glm::vec3& GetPosition();
    glm::vec3& GetLookVector();
    ViewProjection GetViewProjection();
};