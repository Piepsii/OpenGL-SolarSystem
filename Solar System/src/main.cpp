// main.cpp

#pragma once
#include "CelestialBody.h"
#include "Shaders.h"


namespace SolarSystem {
    extern float cursorPosX, cursorPosY;
    extern float deltaTime;
    extern float cameraDistance;
    extern float mousePosX, mousePosY;
    extern int windowWidth, windowHeight;
    extern glm::mat4 projection;

    extern float rotationRateEarth, orbitalPeriodEarth;
    extern glm::mat4 world;
    extern glm::mat4 view;
    extern bool useRealMetrics;

    int Run(int argc, char** argv)
    {

        /*------------------------------------------------WINDOW---------------------------------------------*/

        glfwSetErrorCallback([](int code, const char* message) {
            printf("!!! %s (%d)\n", message, code);
            });

        if (!glfwInit()) {
            return 0;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Solar System", nullptr, nullptr);
        if (window == nullptr) {
            return 0;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
            return 0;
        }

        glfwSetKeyCallback(window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods) {
            if (keycode == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            else if (keycode == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
                useRealMetrics = !useRealMetrics;
            }
            else if (keycode == GLFW_KEY_UP && action == GLFW_RELEASE) {
                deltaTime += 0.000001f;
            }
            else if (keycode == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
                deltaTime -= 0.000001f;
            }
            });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            mousePosX = (float)(xpos / (windowWidth / 8));
            mousePosY = (float)(ypos / windowHeight);
            });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            cameraDistance += (float)yoffset;
            });

        /*------------------------------------------------WINDOW---------------------------------------------*/

        /*------------------------------------------------SHADER---------------------------------------------*/


        GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader_id, 1, &glsl_vertex, nullptr);
        glCompileShader(vertex_shader_id);

        GLint compile_status = GL_TRUE;
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar shader_error[1024] = {};
            glGetShaderInfoLog(vertex_shader_id, sizeof(shader_error), nullptr, shader_error);
            printf("!!! vertex shader error:\n%s\n", shader_error);
        }

        GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_id, 1, &glsl_fragment, nullptr);
        glCompileShader(fragment_shader_id);

        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_FALSE) {
            GLchar shader_error[1024] = {};
            glGetShaderInfoLog(fragment_shader_id, sizeof(shader_error), nullptr, shader_error);
            printf("!!! fragment shader error:\n%s\n", shader_error);
        }

        GLuint shader_program_id = glCreateProgram();
        glAttachShader(shader_program_id, vertex_shader_id);
        glAttachShader(shader_program_id, fragment_shader_id);
        glLinkProgram(shader_program_id);

        GLint link_status = GL_TRUE;
        glGetProgramiv(shader_program_id, GL_LINK_STATUS, &link_status);
        if (link_status == GL_FALSE) {
            GLchar program_error[1024] = {};
            glGetProgramInfoLog(shader_program_id, sizeof(program_error), nullptr, program_error);
            printf("!!! shader program error\n%s\n", program_error);
        }


        /*------------------------------------------------SHADER---------------------------------------------*/

        /*------------------------------------------------MESHES---------------------------------------------*/

        const GLint projection_location = glGetUniformLocation(shader_program_id, "u_projection");
        const GLint world_location = glGetUniformLocation(shader_program_id, "u_world");
        const GLint light_direction_location = glGetUniformLocation(shader_program_id, "u_light_direction");
        const GLint light_color_location = glGetUniformLocation(shader_program_id, "u_light_color");

        const glm::vec3 light_direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
        const glm::vec4 light_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        // Cube 1
        GLuint vertex_array_id = 0;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        GLuint vertex_buffer_id = 0;
        glGenBuffers(1, &vertex_buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sixSidedCube), sixSidedCube, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, r));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, u));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, nx));

        float time = 0.0f;

        std::vector<CelestialBody> bodies;
        bodies.push_back(CelestialBody());
        bodies.back().Create(1000.0f, 1000.0f, 10.9f, 0.0f, 0.0f, "data/sun.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(58.65f, 0.24f, 0.383f, 0.39f, 5.0f, "data/mercury.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(58.65f, 0.62f, 0.949f, 0.72f, 10.0f, "data/venus.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(1.0f, 1.0f, 1.0f, 1.0f, 15.0f, "data/earth.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(29.53f, 0.0027f, 0.2725f, 0.00257f, 3.0f, "data/moon.png", bodies[3].GetSpace());
        bodies.push_back(CelestialBody());
        bodies.back().Create(1.03f, 1.88f, 0.532f, 1.52f, 20.0f, "data/mars.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(0.41f, 11.86f, 11.209f, 5.20f, 25.0f, "data/jupiter.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(0.44f, 29.45f, 9.449f, 9.54f, 30.0f, "data/saturn.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(58.65f, 84.02f, 4.007f, 19.19f, 35.0f, "data/uranus.png");
        bodies.push_back(CelestialBody());
        bodies.back().Create(0.67f, 164.79f, 3.883f, 30.07f, 40.0f, "data/neptune.png");

        GLuint sampler_id = 0;
        glGenSamplers(1, &sampler_id);
        glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        /*------------------------------------------------MESHES---------------------------------------------*/

        while (!glfwWindowShouldClose(window)) {
            int width = 0, height = 0;
            glfwGetFramebufferSize(window, &width, &height);

            time += deltaTime;
            rotationRateEarth = deltaTime;
            orbitalPeriodEarth = rotationRateEarth * 365.0f;
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, cameraDistance)) *
                glm::rotate(glm::mat4(1.0f), mousePosY, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f))) *
                glm::rotate(glm::mat4(1.0f), mousePosX, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));

            for (int i = 0; i < 10; i++) {
                bodies[i].Update();
            }

            glClearDepth(1.0f);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glFrontFace(GL_CW);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);

            glEnable(GL_DEPTH_TEST);

            glUseProgram(shader_program_id);
            glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix3fv(light_direction_location, 1, GL_FALSE, glm::value_ptr(light_direction));
            glUniformMatrix4fv(light_color_location, 1, GL_FALSE, glm::value_ptr(light_color));
            glBindVertexArray(vertex_array_id);

            glBindSampler(0, sampler_id);
            for (int i = 0; i < 10; i++) {
                bodies[i].Draw(world_location, primitive_count);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

        return 0;
    }
}

int main(int argc, char** argv) {
    SolarSystem::Run(argc, argv);
}
