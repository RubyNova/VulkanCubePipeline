#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdint>

class Camera {
public:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	inline glm::mat4 getUboMatrix() const {
		return projectionMatrix * viewMatrix;
	}

	static Camera createDefaultCamera(int32_t width, int32_t height) {
		Camera camera;

		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f));

		glm::mat4 projection = glm::perspective<float>(90, static_cast<float>(width) / static_cast<float>(height), 0, 65535);

		camera.viewMatrix = view;
		camera.projectionMatrix = projection;
	}
};

#endif //!CAMERA_H