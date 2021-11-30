// Application.cpp

#include "Spinach.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Application::Application(const char* title, int width, int height)
: context(title, width, height, this),
windowWidth(width),
windowHeight(height) {

}

Application::~Application() {

}

void Application::Run() {
	running = context.IsValid();
	while (running && context.PollEvents()) {
		backend.Clear(0.1f, 0.2f, 0.3f, 1.0f);
        // note: rendering goes here!
		context.SwapBuffers();
	}
}

void Application::OnKey(int key, bool state) {
	if (key == GLFW_KEY_ESCAPE && !state) {
		running = false;
	}
    else if (key == GLFW_KEY_SPACE && !state) {
        useRealMetrics = !useRealMetrics;
    }
    else if (key == GLFW_KEY_UP && !state) {
        deltaTime += 0.000001f;
    }
    else if (key == GLFW_KEY_DOWN && !state) {
        deltaTime -= 0.000001f;
    }
}

void Application::OnMouse(int x, int y) {
    mousePosX = (float)(x / (windowWidth / 8));
    mousePosY = (float)(y / windowHeight);
}

void Application::OnScroll(int xoffset, int yoffset){
    cameraDistance += (float)yoffset;
}

void Application::OnButton(int button, bool state) {
}