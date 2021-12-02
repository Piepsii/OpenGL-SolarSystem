#pragma once

#include <Render.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Utility {
	int64 GetCurrentTick();
	bool CreateShaderProgramFromFiles(ShaderProgram& program,
		const char* vertex_filename,
		const char* fragment_filename);
	bool CreateTextureFromFile(Texture& texture,
		const char* filename);

	static float angle_vertical = 0.0f, angle_horizontal = 0.0f;
	static float camera_distance = -5.0f;

	static glm::mat4 world_space = glm::mat4(1.0f);
	static glm::mat4 view_space = glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -30.0f, -70.0f));

}

