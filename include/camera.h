#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <header.h>

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	//camera attribs
	glm::vec3 Position, Front, Up, Right, WorldUp;

	float Yaw, Pitch;
	float movementSpeed, mouseSensitivity, zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(up), Yaw(yaw), Pitch(pitch), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		updateCameraVectors();
	}

	//returns the view matrix calculated using euler angles and the lookat matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	//processes input received from any keyboard like input system
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		if (direction == Camera_Movement::FORWARD)
			Position += Front * velocity;
		if (direction == Camera_Movement::BACKWARD)
			Position -= Front * velocity;
		if (direction == Camera_Movement::LEFT)
			Position -= Right * velocity;
		if (direction == Camera_Movement::RIGHT)
			Position += Right * velocity;
	}

	//process input received from a mouse input system. expects offset value in both x and y direction
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= mouseSensitivity;
		yoffset *= -mouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		//make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		//update front, right and up vectors using the updated euler angles
		updateCameraVectors();
	}

	//process input received from a mouse scroll-wheel event
	void ProcessMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

private:
	//calculates the front vector from the camera's updated euler angles
	void updateCameraVectors()
	{
		//calculate the new front vector
		glm::vec3 front;
		front.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
		front.y = glm::sin(glm::radians(Pitch));
		front.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		//recalculate others
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif
