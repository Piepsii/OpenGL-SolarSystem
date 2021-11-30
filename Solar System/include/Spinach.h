// Spinach.h

#pragma once

#include <vector>
#include <Render.h>
#include <glm/glm.hpp>
#include "CelestialBody.h"

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

	void CreateSolarSystem();

	bool running{};
	RenderContext context;
	RenderBackend backend;

	std::vector<SolarSystem::CelestialBody> bodies;
	glm::mat4 projection{ glm::perspective(3.141592f * 0.4f, 1.0f, 1.0f, 500.0f) };
	int windowWidth, windowHeight;
};

