#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
#include <glm/glm.hpp>

class Camera{
public:
    Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
		const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float roll=0, float yaw=-90.0f, float pitch=0.0f);
	~Camera() {};

	void setPosition(const glm::vec3 position);
	const glm::vec3& getPosition() const;

	void setRoll(float roll_degree);
	float getRoll() const;

	void setPitch(float pitch_degree);
	float getPitch() const;

	void setYaw(float yaw_degree);
	float getYaw() const;

	void setFixedTarget(const glm::vec3 target);
	void removeFixedTarget();

	bool hasFixedTarget() const;

	void setPerspective(float fov, float aspect_ratio, float near_sight = 0.1, float far_sight = 100.0f);
	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getViewProjectionMatrix() const;

private:
	void updateVectors();
	void updateViewMatrix();
	void updateProjectionMatrix();

private:
	glm::vec3 cam_position;
	glm::vec3 cam_up;
	glm::vec3 cam_direction;
	glm::vec3 cam_right;
	glm::vec3 world_up;
	float cam_yaw, cam_roll, cam_pitch;

	glm::mat4 view_matrix;
	glm::mat4 projection_matrix;
	glm::mat4 view_projection_matrix;

	//Default projection values
	float persp_fov = 45.0f;
	float persp_aspect_ratio = 16.0f / 9.0f;
	float persp_near_plane = 0.1f;
	float persp_far_plane = 100.0f;

	glm::vec3 fixed_target = glm::vec3(0.0f, 0.0f, 0.0f);
	bool has_fixed_target = false;
};

class OrthographicCamera{
public:
    OrthographicCamera(float left=1, float right=-1, float bottom=-1, float top=1, float near_plane = -1.0, float far_plane = 1.0);
	~OrthographicCamera();

	void setPosition(const glm::vec3 position);
	const glm::vec3& getPosition() const { return cam_position; };

	void setRoll(float roll_degree);
	float getRoll() const { return cam_roll; };

	void setFrustum(float left, float right, float bottom, float top, float near_plane = -1.0, float far_plane = 1.0);

	const glm::mat4& getViewMatrix() const { return view_matrix; };
	const glm::mat4& getProjectionMatrix() const { return projection_matrix; };
	const glm::mat4& getViewProjectionMatrix() const { return view_projection_matrix; };

private:
	void updateViewMatrix();

private:
	glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, 0.0f);
	float cam_roll = 0.0f;

	glm::mat4 view_matrix;
	glm::mat4 projection_matrix;
	glm::mat4 view_projection_matrix;
};

#endif