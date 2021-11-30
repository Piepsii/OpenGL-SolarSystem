// Application.cpp

#include "Spinach.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct vertex {
    float x, y, z;
    float r, g, b, a;
    float u, v;
    float nx, ny, nz;
};

struct Mesh {
    int m_offset;
    int m_count;
};

const vertex sixSidedCube[36] = {
    // front
    {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,  1.0f },
    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f,  1.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f,  1.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f,  1.0f },
    {  1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f,  0.0f,  1.0f },
    {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f,  1.0f },
    // left                                                                            
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    -1.0f,  0.0f,  0.0f },
    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    -1.0f,  0.0f,  0.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    -1.0f,  0.0f,  0.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    -1.0f,  0.0f,  0.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    -1.0f,  0.0f,  0.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    -1.0f,  0.0f,  0.0f },
    // right                                                                           
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     1.0f,  0.0f,  0.0f },
    {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     1.0f,  0.0f,  0.0f },
    {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     1.0f,  0.0f,  0.0f },
    {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     1.0f,  0.0f,  0.0f },
    {  1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     1.0f,  0.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     1.0f,  0.0f,  0.0f },
    // back                                                              
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f },
    {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  0.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  0.0f, -1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f,  0.0f, -1.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  0.0f, -1.0f },
    // top                                                               
    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f,  1.0f,  0.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f,  1.0f,  0.0f },
    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f,  1.0f,  0.0f },
    // bottom                                                                          
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,     0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,     0.0f, -1.0f,  0.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,     0.0f, -1.0f,  0.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     0.0f, -1.0f,  0.0f },
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
    bodies.back().Create(nullptr, 1000.0f, 1000.0f, 10.9f, 0.0f, 0.0f, "data/sun.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 58.65f, 0.24f, 0.383f, 0.39f, 5.0f, "data/mercury.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 58.65f, 0.62f, 0.949f, 0.72f, 10.0f, "data/venus.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 1.0f, 1.0f, 1.0f, 1.0f, 15.0f, "data/earth.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(bodies[3].GetSpace(), 29.53f, 0.0027f, 0.2725f, 0.00257f, 3.0f, "data/moon.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr , 1.03f, 1.88f, 0.532f, 1.52f, 20.0f, "data/mars.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 0.41f, 11.86f, 11.209f, 5.20f, 25.0f, "data/jupiter.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 0.44f, 29.45f, 9.449f, 9.54f, 30.0f, "data/saturn.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 58.65f, 84.02f, 4.007f, 19.19f, 35.0f, "data/uranus.png");
    bodies.push_back(SolarSystem::CelestialBody());
    bodies.back().Create(nullptr, 0.67f, 164.79f, 3.883f, 30.07f, 40.0f, "data/neptune.png");
}

Application::~Application() {

}

void Application::Run() {
	running = context.IsValid();
	while (running && context.PollEvents()) {
		backend.Clear(0.1f, 0.2f, 0.3f, 1.0f);
        // note: rendering goes here!

        const FramebufferFormat formats[] =
        {
           FRAMEBUFFER_FORMAT_RGBA8
        };

        Framebuffer rendertarget;
        if (!rendertarget.Create(1920, 1080, 1, formats)) {
            return;
        }

        Texture crate_texture;
        if (!Utility::CreateTextureFromFile(crate_texture,
            "data/sun.png"))
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

        ShaderProgram world_program;
        if (!Utility::CreateShaderProgramFromFiles(world_program,
            "data/world.vs.glsl",
            "data/world.fs.glsl"))
        {
            return;
        }

        for (int i = 0; i < 10; i++) {
            bodies[i].Update();
        }

        glViewport(0, 0, windowWidth, windowHeight);
        glFrontFace(GL_CW);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glEnable(GL_DEPTH_TEST);

        VertexBuffer world_buffer;
        if (!world_buffer.Create(sizeof(SolarSystem::cube), SolarSystem::cube)) {
            return;
        }

        VertexLayout world_layout;
        world_layout.AddAttribute(0, VertexLayout::ATTRIBUTE_FORMAT_FLOAT, 4, false);

        glm::mat4 perspective = glm::perspective(3.141592f * 0.25f, 16.0f / 9.0f, 1.0f, 100.0f);
        glm::mat4 world = glm::translate(glm::mat4(1.0f), SolarSystem::cube_position);


        backend.SetFramebuffer(rendertarget);
        backend.Clear(0.1f, 0.2f, 0.3f, 1.0f);
        backend.SetShaderProgram(world_program);
        backend.SetShaderUniform(world_program,
          UNIFORM_TYPE_MATRIX,
          "u_projection",
          1, glm::value_ptr(perspective));
        backend.SetShaderUniform(world_program,
          UNIFORM_TYPE_MATRIX,
          "u_world",
          1, glm::value_ptr(world));
        backend.SetVertexBuffer(world_buffer);
        backend.SetVertexLayout(world_layout);
        backend.SetTexture(crate_texture);
        backend.SetSamplerState(linear_sampler);
        backend.SetBlendState(false);
        backend.SetDepthState(true, true);
        backend.SetRasterizerState(CULL_MODE_BACK, FRONT_FACE_CW);
        backend.Draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, SolarSystem::primitive_count);

        backend.ResetFramebuffer();
        backend.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        backend.SetViewport(0, 0, 1920, 1080);
        backend.SetShaderProgram(world_program);
        backend.SetVertexBuffer(world_buffer);
        backend.SetVertexLayout(world_layout);
        backend.SetTexture(rendertarget.ColorAttachmentAsTexture(0));
        backend.SetSamplerState(linear_sampler);
        backend.SetBlendState(false);
        backend.SetRasterizerState(CULL_MODE_NONE, FRONT_FACE_CCW);
        backend.Draw(PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, 6);

        //glUseProgram(shader_program_id);
        //glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
        //glUniformMatrix3fv(light_direction_location, 1, GL_FALSE, glm::value_ptr(light_direction));
        //glUniformMatrix4fv(light_color_location, 1, GL_FALSE, glm::value_ptr(light_color));
        //glBindVertexArray(vertex_array_id);

        //glBindSampler(0, sampler_id);
        //for (int i = 0; i < 10; i++) {
        //    bodies[i].Draw(world_location, primitive_count);
        //}

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

void Application::OnScroll(int xoffset, int yoffset){
}

void Application::OnButton(int button, bool state) {
}