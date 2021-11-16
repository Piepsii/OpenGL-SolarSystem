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

float rotationSpeed = 0.1f;
float cursorPosX = 0.0f, cursorPosY = 0.0f;

struct vertex {
    float x, y, z;
    float r, g, b, a;
};

struct Mesh {
    int m_offset;
    int m_count;
};

const vertex sixSidedCube[] = {
    // front
    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // left
    { -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f },

    // right
    { 1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f },

    // back
    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f },

    // top
    {  1.0f, 1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f },
    {  1.0f, 1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f },
    {  1.0f, 1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f },
    { -1.0f, 1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f },

    // bottom
    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f },
    {  1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f },


};

const vertex oneSidedCube[] = {
    // front
    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // left
    { -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // right
    { 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // back
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f,  1.0f,  -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // top
    {  1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },

    // bottom
    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },


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
    /*------------------------------------------------WINDOW---------------------------------------------*/

    glfwSetErrorCallback([](int code, const char* message) {
        printf("!!! %s (%d)\n", message, code);
    });

   if (!glfwInit()) {
      return 0;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   GLFWwindow* window = glfwCreateWindow(1920, 1080, "Cube", nullptr, nullptr);
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

   glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
       rotationSpeed += (float)(yoffset / 1000.0);
       });

   glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
       cursorPosX = ((float)xpos / 1920.0f - 0.5f) * 2.0f;
       cursorPosY = ((float)ypos / 1080.0f - 0.5f) * 2.0f;
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

   // Cube 1
   GLuint vertex_array_id = 0;
   glGenVertexArrays(1, &vertex_array_id);
   glBindVertexArray(vertex_array_id);

   GLuint vertex_buffer_id = 0;
   glGenBuffers(1, &vertex_buffer_id);
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(sixSidedCube), sixSidedCube, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);;
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, r));

   // Cube 2
   GLuint vertex_array_id2 = 1;
   glGenVertexArrays(1, &vertex_array_id2);
   glBindVertexArray(vertex_array_id2);

   GLuint vertex_buffer_id2 = 1;
   glGenBuffers(1, &vertex_buffer_id2);
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id2);
   glBufferData(GL_ARRAY_BUFFER, sizeof(oneSidedCube), oneSidedCube, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);;
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, r));

   const int primitive_count = sizeof(sixSidedCube) / sizeof(sixSidedCube[0]);
   float rotation = 0.0f;

   /*------------------------------------------------MESHES---------------------------------------------*/

   while (!glfwWindowShouldClose(window)) {
       int width = 0, height = 0;
       glfwGetFramebufferSize(window, &width, &height);

       rotation += rotationSpeed;

       glm::mat4 projection = glm::perspective(PI * 0.25f, ASPECT, NEAR, FAR);
       glm::mat4 world[2];
       world[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f + cursorPosX, 0.0f - cursorPosY, -7.0f)) *
           glm::rotate(glm::mat4(1.0f), rotation, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
       world[1] = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f + cursorPosX, 0.0f - cursorPosY, -7.0f)) *
           glm::rotate(glm::mat4(1.0f), rotation, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));


       glClearDepth(1.0f);
       glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
       glViewport(0, 0, width, height);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glEnable(GL_CULL_FACE);
       glCullFace(GL_BACK);

       glEnable(GL_DEPTH_TEST);

       glUseProgram(shader_program_id);
       glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
       glBindVertexArray(vertex_array_id);

       glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world[0]));
       glDrawArrays(GL_TRIANGLES, 0, primitive_count);

       glBindVertexArray(vertex_array_id2);

       glUniformMatrix4fv(world_location, 1, GL_FALSE, glm::value_ptr(world[1]));
       glDrawArrays(GL_TRIANGLES, 0, primitive_count);


       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   
   glfwTerminate();

   return 0;
}

