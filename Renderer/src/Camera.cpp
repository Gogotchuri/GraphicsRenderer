#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///++++++++++++++++++++++++++++++++ Perspective Camera ++++++++++++++++++++++++++++++++++++++++++
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Camera::Camera(const glm::vec3 position, const glm::vec3 up, float roll, float yaw, float pitch)
	:cam_position(position), cam_up(up), cam_direction(glm::vec3(0.0f, 0.0f, -1.0f)),
	 world_up(up), cam_yaw(yaw), cam_pitch(pitch), cam_roll(roll)
{
    updateProjectionMatrix();
	updateVectors();
}

void Camera::setPosition(const glm::vec3 position)
{
	cam_position = position;
	updateVectors();
}

const glm::vec3& Camera::getPosition() const { return cam_position; }

void Camera::setPerspective(const float fov, const float aspect_ratio, const float near_sight, const float far_sight)
{
	persp_fov = fov;
	persp_aspect_ratio = aspect_ratio;
	persp_near_plane = near_sight;
	persp_far_plane = far_sight;
	updateProjectionMatrix();
}

const glm::mat4& Camera::getViewMatrix() const { return view_matrix; }

const glm::mat4& Camera::getProjectionMatrix() const { return projection_matrix; }

const glm::mat4& Camera::getViewProjectionMatrix() const { return view_projection_matrix; }

void Camera::setRoll(float roll_degree)
{
	cam_roll = roll_degree;
	updateVectors();
}

float Camera::getRoll() const { return cam_roll; }

void Camera::setPitch(float pitch_degree)
{
	cam_pitch = pitch_degree;
	updateVectors();
}

float Camera::getPitch() const { return cam_pitch; }

void Camera::setYaw(float yaw_degree)
{
	cam_yaw = yaw_degree;
	updateVectors();
}

float Camera::getYaw() const { return cam_yaw; }

void Camera::setFixedTarget(const glm::vec3 target) {
	has_fixed_target = true;
	fixed_target = target;
}

void Camera::removeFixedTarget() { has_fixed_target = false; }

bool Camera::hasFixedTarget() const { return has_fixed_target;}

//++++++++++++++++++++++++++++++++++++++Privates+++++++++++++++++++++++++++++++++++

static void printVec3(const glm::vec3 & vec, std::string name = "vec"){
	std::cout << "Vector name: " + name <<std::endl;
	std::cout << vec.x << " X; " << vec.y << " Y " << vec.z << " Z " <<std::endl;
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
	front.y = sin(glm::radians(cam_pitch));
	front.z = sin(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
	cam_direction = glm::normalize(front);
	cam_right = glm::normalize(glm::cross(cam_direction, world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cam_up = glm::normalize(glm::cross(cam_right, cam_direction));
	updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	glm::vec3 target = has_fixed_target ? fixed_target : (cam_position + cam_direction);
	view_matrix = glm::lookAt(cam_position, target, cam_up);
	view_projection_matrix = projection_matrix * view_matrix;
}

void Camera::updateProjectionMatrix()
{
	projection_matrix = glm::perspective(glm::radians(persp_fov), persp_aspect_ratio, persp_near_plane, persp_far_plane);
	view_projection_matrix = projection_matrix * view_matrix;
}



///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///++++++++++++++++++++++++++++++++ Orthographic Camera ++++++++++++++++++++++++++++++++++++++++++
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_plane, float far_plane)
	: view_matrix(glm::mat4(1.0f)), projection_matrix(glm::ortho(left, right, bottom, top, near_plane, far_plane))
{
	view_projection_matrix = projection_matrix * view_matrix;
}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::setPosition(const glm::vec3 position) {
	cam_position = position;
	updateViewMatrix();
}

void OrthographicCamera::setRoll(float roll_degree) {
	cam_roll = roll_degree;
	updateViewMatrix();
}

void OrthographicCamera::setFrustum(float left, float right, float bottom, float top, float near_plane, float far_plane) {
	projection_matrix = glm::ortho(left, right, bottom, top, near_plane, far_plane);
	view_projection_matrix = projection_matrix * view_matrix;
}
//+++++++++++++++++++++++++++++++++ Privates +++++++++++++++++++++++++++++++++++++++++++++++++++++

void OrthographicCamera::updateViewMatrix(){
	glm::mat4 IMat = glm::mat4(1.0f); //Identity matrix
	glm::vec3 ZAxis = glm::vec3(0, 0, 1);
	view_matrix = glm::inverse(
		glm::translate(IMat, cam_position) * glm::rotate(IMat, glm::radians(cam_roll), ZAxis)
	);
	view_projection_matrix = projection_matrix * view_matrix;
}