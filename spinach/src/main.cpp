// main.cpp

#include <cstdio>
#include <cassert>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct vertex {
    float x, y, z;
    float r, g, b, a;
};

const vertex triangle[] = {
    { 0.0f,  1.0f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f },
};

const char* glsl_vertex = R"(
#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

out vec4 v_color;

void main(){
    gl_Position = vec4(a_position, 1);
    v_color = a_color;
}
)";

const char* glsl_fragment = R"(
#version 330

in vec4 v_color;
out vec4 final_color;

void main(){
    final_color = v_color;
}
)";

int main(int argc, char **argv)
{
    glfwSetErrorCallback([](int code, const char* message) {
        printf("!!! %s (%d)\n", message, code);
    });

   if (!glfwInit()) {
      return 0;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   GLFWwindow* window = glfwCreateWindow(1920, 1080, "Triangle", nullptr, nullptr);
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
    });

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


   GLuint vertex_array_id = 0;
   glGenVertexArrays(1, &vertex_array_id);
   glBindVertexArray(vertex_array_id);

   GLuint vertex_buffer_id = 0;
   glGenBuffers(1, &vertex_buffer_id);
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);;
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, a));

   const int primitive_count = sizeof(triangle) / sizeof(triangle[0]);

   while (!glfwWindowShouldClose(window)) {
       int width = 0, height = 0;
       glfwGetFramebufferSize(window, &width, &height);

       glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
       glViewport(0, 0, width, height);
       glClear(GL_COLOR_BUFFER_BIT);

       glUseProgram(shader_program_id);
       glBindVertexArray(vertex_array_id);
       glDrawArrays(GL_TRIANGLES, 0, primitive_count);

       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   
   glfwTerminate();

   return 0;
}

