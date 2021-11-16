// main.cpp

#include <cstdio>
#include <cassert>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

const static float PI = 3.141592f;
const static float ASPECT = 16.0f / 9.0f;
const static float NEAR = 1.0f;
const static float FAR = 100.0f;


struct vertex {
    float x, y, z;
    float r, g, b, a;
};

const vertex triangle[] = {
    // position (x, y, z)    color (r, g, b, a)
    { 0.0f,  1.0f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f },
};

const char* glsl_vertex = R"(
#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

uniform mat4 u_projection;
uniform mat4 u_world;

out vec4 v_color;

void main(){
    gl_Position = u_projection * u_world * vec4(a_position, 1);
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

   const GLint projection_location = glGetUniformLocation(shader_program_id, "u_projection");
   const GLint world_location = glGetUniformLocation(shader_program_id, "u_world");

   glm::mat4 projection = glm::perspective(PI * 0.25f, ASPECT, NEAR, FAR);
   glm::mat4 world = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.0f, -10.0f));
   glm::mat4 world2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 1.0f, -11.0f));

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

       glClearDepth(1.0f);
       glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
       glViewport(0, 0, width, height);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glEnable(GL_DEPTH_TEST);

       glUseProgram(shader_program_id);
       glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
       glBindVertexArray(vertex_array_id);

       glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world));
       glDrawArrays(GL_TRIANGLES, 0, primitive_count);

       glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world2));
       glDrawArrays(GL_TRIANGLES, 0, primitive_count);


       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   
   glfwTerminate();

   return 0;
}

