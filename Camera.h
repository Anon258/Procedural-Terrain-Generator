#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera {
public:
	glm::vec3 position;
	glm::vec3 angle;
	glm::vec3 camera_up;
	glm::vec3 camera_right;
	glm::vec3 world_up;
	float Yaw;
	float Pitch;
	float Speed;
	float Sensitivity;
	float Zoom;

	//Constructor to initialize all variables
	camera(glm::vec3 coordinates, glm::vec3 init_angle) {
		position = coordinates;
		angle = init_angle;
		Yaw = -90.0f;
		Pitch = 0.0f;
		Speed = 2.5f;
		Sensitivity = 0.1f;
		Zoom = 50.0f;
		UpdateVectors();
	}

	//Find view matrix
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(position, position + angle, camera_up);
	}

	void Keyboard(GLFWwindow* window, float deltaTime) {
		float cam_velocity = Speed * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position = position + angle * cam_velocity;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position = position - angle * cam_velocity;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position = position + camera_right * cam_velocity;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position = position - camera_right * cam_velocity;
	}

	//Change Yaw and Pitch Movement
	void MouseYP(float xoffset, float yoffset)
	{
		xoffset *= Sensitivity;
		yoffset *= Sensitivity;
		Yaw = Yaw + xoffset;
		Pitch = Pitch + yoffset;
		//Constrain Pitch
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateVectors();
	}

	//Change Zoom Movement
	void MouseZoom(float yoffset) {
		Zoom = Zoom - yoffset;
		if (Zoom < 0.5f)
			Zoom = 0.5f;
		if (Zoom > 50.0f)
			Zoom = 50.0f;
	}

private:
	void UpdateVectors() {
		glm::vec3 new_angle;
		new_angle.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		new_angle.y = sin(glm::radians(Pitch));
		new_angle.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		angle = glm::normalize(new_angle);
		camera_right = glm::normalize(glm::cross(angle, world_up));
		camera_up = glm::normalize(glm::cross(camera_right, angle));
	}
};