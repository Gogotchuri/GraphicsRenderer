#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& world_up, float roll_degree)
	:cam_position(position), cam_up(world_up), world_up(world_up),
		cam_yaw(-90.0f), cam_pitch(0.0f), cam_roll(roll_degree)
{
    updateProjectionMatrix();
	updateVectors();
}

void Camera::setPosition(const glm::vec3 & position)
{
	cam_position = position;
	updateVectors();
}

const glm::vec3& Camera::getPosition() const
{
	return cam_position;
}

void Camera::setPerspective(const float fov, const float aspect_ratio, const float near_sight, const float far_sight)
{
	persp_fov = fov;
	persp_aspect_ratio = aspect_ratio;
	persp_near_plane = near_sight;
	persp_far_plane = far_sight;
	updateProjectionMatrix();
}

const glm::mat4& Camera::getViewMatrix() const
{
	return view_matrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return projection_matrix;
}

const glm::mat4& Camera::getViewProjectionMatrix() const
{
	return view_projection_matrix;
}


void Camera::setRoll(float roll_degree)
{
	cam_roll = roll_degree;
	updateVectors();
}

float Camera::getRoll() const
{
	return cam_roll;
}


void Camera::setPitch(float pitch_degree)
{
	cam_pitch = pitch_degree;
	updateVectors();
}

float Camera::getPitch() const
{
	return cam_pitch;
}

void Camera::setYaw(float yaw_degree)
{
	cam_yaw = yaw_degree;
	updateVectors();
}

float Camera::getYaw() const
{
	return cam_yaw;
}

//++++++++++++++++++++++++++++++++++++++Privates+++++++++++++++++++++++++++++++++++

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
	front.y = sin(glm::radians(cam_pitch));
	front.z = cos(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
	cam_direction = glm::normalize(front);

	cam_direction = glm::normalize(cam_direction);
	cam_right = glm::normalize(glm::cross(cam_direction, world_up));
	cam_up = glm::normalize(glm::cross(cam_right, cam_direction));

	updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	view_matrix = glm::lookAt(cam_position, cam_position + cam_direction, cam_up);
	view_projection_matrix = projection_matrix * view_matrix;
}

void Camera::updateProjectionMatrix()
{
	projection_matrix = glm::perspective(glm::radians(persp_fov), persp_aspect_ratio, persp_near_plane, persp_far_plane);
	view_projection_matrix = projection_matrix * view_matrix;
}
