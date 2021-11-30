// Spinach.h

#pragma once


#include <Render.h>
#include <glm/glm.hpp>

struct GLFWwindow;
struct RenderContext {
	RenderContext(const char* title, int width, int height, void* user_data);
	~RenderContext();
	
	bool IsValid() const;
	bool PollEvents();
	void SwapBuffers();

	GLFWwindow* window{};
};

struct Application {
	Application(const char* title, int width, int height);
	~Application();

	void Run();

	void OnKey(int key, bool state);
	void OnMouse(int x, int y);
	void OnScroll(int xoffset, int yoffset);
	void OnButton(int button, bool state);

	bool running{};
	RenderContext context;
	RenderBackend backend;

	const float PI = 3.141592f;
	const float ASPECT = 1.0f / 1.0f;
	const float NEAR = 1.0f;
	const float FAR = 500.0f;

	bool useRealMetrics;
	float deltaTime{0.00001f};
	float mousePosX{0.0f}, mousePosY{0.0f};
	float cameraDistance{-50.0f};
	glm::mat4 projection;
	float rotationRateEarth{deltaTime}, orbitalPeriodEarth{rotationRateEarth * 365.0f};
	glm::mat4 world{ glm::mat4(1.0f) };
	glm::mat4 view{ glm::mat4(1.0f) };
	int windowWidth, windowHeight;
};

namespace Utility {
	int64 GetCurrentTick();
	bool CreateShaderProgramFromFiles(ShaderProgram& program,
		const char* vertex_filename,
		const char* fragment_filename);
	bool CreateTextureFromFile(Texture& texture,
		const char* filename);
}
