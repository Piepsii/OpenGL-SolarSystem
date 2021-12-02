// Application.cpp

#include "Spinach.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct vertex {
	float x, y, z;
	float u, v;
};

const vertex cube_data[360] = {
	// front
   { -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },
   {  1.0f,  1.0f,  1.0f,   1.0f, 1.0f, },
   {  1.0f, -1.0f,  1.0f,   1.0f, 0.0f, },
   {  1.0f, -1.0f,  1.0f,   1.0f, 0.0f, },
   { -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, },
   { -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },

   // right                             
   {  1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },
   {  1.0f,  1.0f, -1.0f,   1.0f, 1.0f, },
   {  1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   {  1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   {  1.0f, -1.0f,  1.0f,   0.0f, 0.0f, },
   {  1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },

   // back                              
   {  1.0f,  1.0f, -1.0f,   0.0f, 1.0f, },
   { -1.0f,  1.0f, -1.0f,   1.0f, 1.0f, },
   { -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   { -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   {  1.0f, -1.0f, -1.0f,   0.0f, 0.0f, },
   {  1.0f,  1.0f, -1.0f,   0.0f, 1.0f, },

   // left                              
   { -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, },
   { -1.0f,  1.0f,  1.0f,   1.0f, 1.0f, },
   { -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, },
   { -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, },
   { -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, },
   { -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, },

   // top                               
   {  1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },
   { -1.0f,  1.0f,  1.0f,   1.0f, 1.0f, },
   { -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, },
   { -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, },
   {  1.0f,  1.0f, -1.0f,   0.0f, 0.0f, },
   {  1.0f,  1.0f,  1.0f,   0.0f, 1.0f, },

   // bottom                               
   { -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, },
   {  1.0f, -1.0f,  1.0f,   1.0f, 1.0f, },
   {  1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   {  1.0f, -1.0f, -1.0f,   1.0f, 0.0f, },
   { -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, },
   { -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, },
};

static const float final_data[]{
   -1.0f,  1.0f,  0.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
   -1.0f, -1.0f,  0.0f, 0.0f,
   -1.0f,  1.0f,  0.0f, 1.0f,
};


Application::Application(const char* title, int width, int height)
	: context(title, width, height, this),
	windowWidth(width),
	windowHeight(height) {
	CreateSolarSystem();
}

void Application::CreateSolarSystem()
{
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create( 1000.0f, 1000.0f, 0.0f, "data/sun.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(58.65f, 0.24f, 5.0f, "data/mercury.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(58.65f, 0.62f, 10.0f, "data/venus.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(1.0f, 1.0f,  15.0f, "data/earth.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(29.53f, 0.0027f, 3.0f, "data/moon.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(1.03f, 1.88f, 20.0f, "data/mars.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(0.41f, 11.86f, 25.0f, "data/jupiter.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(0.44f, 29.45f, 30.0f, "data/saturn.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(58.65f, 84.02f, 35.0f, "data/uranus.png");
	bodies.push_back(SolarSystem::CelestialBody());
	bodies.back().Create(0.67f, 164.79f, 40.0f, "data/neptune.png");

	for (int i = 0; i < bodies.size(); i++) {
		bodies[i].SetOffset(i * sizeof(cube_data));
		bodies[i].SetCount(sizeof(cube_data) / sizeof(cube_data[0]));
	}
}

Application::~Application() {

}

void Application::Run() {
	running = context.IsValid();
	const FramebufferFormat formats[] =
	{
		FRAMEBUFFER_FORMAT_RGBA8,
		FRAMEBUFFER_FORMAT_D32
	};
	Framebuffer rendertarget;
	if (!rendertarget.Create(1920, 1080, 1, formats)) {
		return;
	}
	ShaderProgram world_program;
	if (!Utility::CreateShaderProgramFromFiles(world_program,
											   "data/world.vs.glsl",
											   "data/world.fs.glsl"))
	{
		return;
	}

	SamplerState linear_sampler;
	if (!linear_sampler.Create(
		SAMPLER_FILTER_MODE_LINEAR,
		SAMPLER_ADDRESS_MODE_CLAMP,
		SAMPLER_ADDRESS_MODE_CLAMP))
	{
		return;
	}
	const int primitive_count = sizeof(cube_data) / sizeof(cube_data[0]);
	VertexBuffer vertex_buffer;
	if (!vertex_buffer.Create(sizeof(cube_data) * int(bodies.size()), cube_data)) {
		return;
	}
	VertexLayout vertex_layout;
	vertex_layout.AddAttribute(0, VertexLayout::ATTRIBUTE_FORMAT_FLOAT, 3, false);
	vertex_layout.AddAttribute(1, VertexLayout::ATTRIBUTE_FORMAT_FLOAT, 2, false);

	ShaderProgram final_program;
	if (!Utility::CreateShaderProgramFromFiles(final_program,
											   "data/final.vs.glsl",
											   "data/final.fs.glsl"))
	{
		return;
	}
	VertexBuffer final_buffer;
	if (!final_buffer.Create(sizeof(final_data), final_data)) {
		return;
	}
	VertexLayout final_layout;
	final_layout.AddAttribute(0, VertexLayout::ATTRIBUTE_FORMAT_FLOAT, 4, false);

	bodies[4].SetSpaceToOrbit(bodies[3].GetSpacePtr());

	while (running && context.PollEvents()) {
		backend.SetFramebuffer(rendertarget);
		backend.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		for (int i = 0; i < bodies.size(); i++) {
			bodies[i].Update();
			bodies[i].Draw(backend,
						   rendertarget,
						   world_program,
						   vertex_buffer,
						   vertex_layout,
						   linear_sampler);
		}

		backend.ResetFramebuffer();
		backend.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		backend.SetViewport(0, 0, 1920, 1080);
		backend.SetShaderProgram(final_program);
		backend.SetVertexBuffer(final_buffer);
		backend.SetVertexLayout(final_layout);
		backend.SetTexture(rendertarget.ColorAttachmentAsTexture(0));
		backend.SetSamplerState(linear_sampler);
		backend.SetBlendState(false);
		backend.SetRasterizerState(CULL_MODE_NONE, FRONT_FACE_CW);
		backend.Draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, 6);

		context.SwapBuffers();
	}
}

void Application::OnKey(int key, bool state) {
	if (key == GLFW_KEY_ESCAPE && !state) {
		running = false;
	}
}

void Application::OnMouse(int x, int y) {
}

void Application::OnScroll(int xoffset, int yoffset) {
}

void Application::OnButton(int button, bool state) {
}