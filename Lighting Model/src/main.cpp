//// main.cpp
//
//#include <cstdio>
//#include <cassert>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//struct vertex {
//    float x, y, z;
//    float r, g, b, a;
//    float u, v;
//    float nx, ny, nz;
//};
//
//struct Mesh {
//    int m_offset;
//    int m_count;
//};
//
//const vertex sixSidedCube[] = {
//    // front
//    { 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 1.0f,    0.0f, 0.0f, 1.0f },
//    { 1.0f,  -1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, 1.0f },
//    { -1.0f,  1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, 1.0f },
//
//    // left
//    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    -1.0f, 0.0f, 0.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    -1.0f, 0.0f, 0.0f },
//    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    -1.0f, 0.0f, 0.0f },
//    { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    -1.0f, 0.0f, 0.0f },
//    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    -1.0f, 0.0f, 0.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    -1.0f, 0.0f, 0.0f },
//
//    // right
//    { 1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    1.0f, 0.0f, 0.0f },
//    { 1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    1.0f, 0.0f, 0.0f },
//    { 1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    1.0f, 0.0f, 0.0f },
//    { 1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    1.0f, 0.0f, 0.0f },
//    { 1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
//    { 1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    1.0f, 0.0f, 0.0f },
//
//    // back
//    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, -1.0f },
//    { 1.0f,  1.0f,  -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 0.0f, -1.0f },
//    { 1.0f,  -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, -1.0f },
//    { -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 0.0f, -1.0f },
//    { 1.0f,  1.0f,  -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, -1.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, -1.0f },
//
//    // top
//    {  1.0f, 1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f },
//    { -1.0f, 1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
//    {  1.0f, 1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 1.0f, 0.0f },
//    {  1.0f, 1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, 1.0f, 0.0f },
//    { -1.0f, 1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, 1.0f, 0.0f },
//    { -1.0f, 1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f },
//
//    // bottom
//    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, -1.0f, 0.0f },
//    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, -1.0f, 0.0f },
//    {  1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, -1.0f, 0.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f, -1.0f, 0.0f },
//    {  1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, -1.0f, 0.0f },
//    { -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f, -1.0f, 0.0f },
//
//
//};
//
//const vertex oneSidedCube[] = {
//    // front
//    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f,  1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, 1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//    // left
//    { -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//    // right
//    { 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//    // back
//    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f,  -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { 1.0f,  1.0f,  -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//    // top
//    {  1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    {  1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    {  1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, 1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, 1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//    // bottom
//    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    {  1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//    { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 1.0f },
//
//
//};
//
//const static float PI = 3.141592f;
//const static float ASPECT = 1.0f / 1.0f;
//const static float NEAR = 1.0f;
//const static float FAR = 400.0f;
//
//float cursorPosX = 0.0f, cursorPosY = 0.0f;
//
//
//const int primitive_count = sizeof(sixSidedCube) / sizeof(sixSidedCube[0]);
//
//const float deltaTime = 0.000001f;
//const float AU = 1200.0f;
//const float earthDiameter = AU / 23481.f;
//const float rotationRateEarth = deltaTime, orbitalPeriodEarth = rotationRateEarth * 365.0f;
//
//float cameraDistance = -300.0f;
//bool useRealMetrics = false;
//int numberOfPlanets = 0;
//float distanceBetweenPlanets = 3.0f;
//
//glm::mat4 projection = glm::perspective(PI * 0.25f, ASPECT, NEAR, FAR);
//
//glm::mat4 world = glm::mat4(1.0f);
//
//class CelestialBody {
//public:
//    CelestialBody(float _rotationPeriod, float _orbitalPeriod, float _radius, float _semiMajorAxis, bool _isMoon = false)
//        : rotationPeriod(_rotationPeriod),
//          orbitalPeriod(_orbitalPeriod),
//          radius(_radius * earthDiameter),
//          semiMajorAxis(_semiMajorAxis * AU),
//          isMoon(_isMoon) {
//        rotation = 0.0f;
//        orbit = 0.0f;
//        orbitEarth = 0.0f;
//        distance = numberOfPlanets * distanceBetweenPlanets;
//        numberOfPlanets++;
//        space = glm::mat4(0.0f);
//    };
//
//    void Update() {
//        rotation += rotationRateEarth / rotationPeriod;
//        orbit += orbitalPeriodEarth / orbitalPeriod;
//        if (isMoon) {
//            if (useRealMetrics) {
//                orbitEarth += orbitalPeriodEarth;
//                space = glm::rotate(world, orbitEarth, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(AU, 0.0f, cameraDistance)) *
//                    glm::rotate(world, orbit, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(semiMajorAxis, 0.0f, 0.0f)) *
//                    glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::scale(world, glm::vec3(radius, radius, radius));
//            }
//            else {
//                orbitEarth += orbitalPeriodEarth;
//                space = glm::rotate(world, orbitEarth, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(distance- distanceBetweenPlanets, 0.0f, cameraDistance)) *
//                    glm::rotate(world, orbit, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(1.5f, 0.0f, 0.0f)) *
//                    glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::scale(world, glm::vec3(0.5f, 0.5f, 0.5f));
//            }
//        }
//        else {
//            if (useRealMetrics) {
//                space = glm::rotate(world, orbit, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(semiMajorAxis, 0.0f, cameraDistance)) *
//                    glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::scale(world, glm::vec3(radius, radius, radius));
//
//            }
//            else {
//                space = glm::rotate(world, orbit, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::translate(world, glm::vec3(distance, 0.0f, cameraDistance)) *
//                    glm::rotate(world, rotation, glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f))) *
//                    glm::scale(world, glm::vec3(1.0f, 1.0f, 1.0f));
//            }
//        }
//    }
//
//    void Draw(GLint _world_location, int _primitive_count) {
//        glUniformMatrix4fv(_world_location, 1, GL_FALSE, glm::value_ptr(space));
//        glDrawArrays(GL_TRIANGLES, 0, _primitive_count);
//    }
//
//    glm::mat4 GetSpace() {
//        return space;
//    }
//
//private:
//    float rotation, orbit;
//    float rotationPeriod, orbitalPeriod, radius, semiMajorAxis, distance;
//    bool isMoon;
//    float orbitEarth;
//    glm::mat4 space;
//};
//
//const char* glsl_vertex = R"(
//#version 330
//
//layout (location = 0) in vec3 a_position;
//layout (location = 1) in vec4 a_color;
//layout (location = 2) in vec2 a_texcoord;
//layout (location = 3) in vec3 a_normal;
//
//uniform mat4 u_projection;
//uniform mat4 u_world;
//
//out vec4 v_color;
//out vec2 v_texcoord;
//out vec3 v_normal;
//
//void main(){
//    gl_Position = u_projection * u_world * vec4(a_position, 1);
//    v_color = a_color;
//    v_texcoord = a_texcoord;
//    v_normal = normalize((u_world * vec4(normalize(a_normal), 0)).xyz);
//}
//)";
//
//const char* glsl_fragment = R"(
//#version 330
//
//uniform vec3 u_light_direction;
//uniform vec4 u_light_color;
//
//uniform sampler2D u_diffuse;
//
//in vec4 v_color;
//in vec2 v_texcoord;
//in vec3 v_normal;
//out vec4 final_color;
//
//void main(){
//    vec3 L = -normalize(u_light_direction);
//    vec3 N = normalize(v_normal);
//    float NdotL = max(0.0, dot(N, L));
//    vec4 diffuse_color = NdotL * u_light_color;
//
//    final_color = texture(u_diffuse, v_texcoord) * v_color * diffuse_color;
//    final_color = texture(u_diffuse, v_texcoord) * v_color;
//
//}
//)";
//
//int main(int argc, char **argv)
//{
//    /*------------------------------------------------WINDOW---------------------------------------------*/
//
//    glfwSetErrorCallback([](int code, const char* message) {
//        printf("!!! %s (%d)\n", message, code);
//    });
//
//   if (!glfwInit()) {
//      return 0;
//   }
//
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   GLFWwindow* window = glfwCreateWindow(1200, 1200, "Solar System", nullptr, nullptr);
//   if (window == nullptr) {
//       return 0;
//   }
//
//   glfwMakeContextCurrent(window);
//   glfwSwapInterval(1);
//   if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
//       return 0;
//   }
//
//   glfwSetKeyCallback(window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods) {
//       if (keycode == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
//           glfwSetWindowShouldClose(window, GLFW_TRUE);
//       }
//       else if (keycode == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
//           useRealMetrics = !useRealMetrics;
//       }
//    });
//
//   /*------------------------------------------------WINDOW---------------------------------------------*/
//
//   /*------------------------------------------------SHADER---------------------------------------------*/
//
//
//   GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
//   glShaderSource(vertex_shader_id, 1, &glsl_vertex, nullptr);
//   glCompileShader(vertex_shader_id);
//
//   GLint compile_status = GL_TRUE;
//   glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compile_status);
//   if (compile_status == GL_FALSE) {
//       GLchar shader_error[1024] = {};
//       glGetShaderInfoLog(vertex_shader_id, sizeof(shader_error), nullptr, shader_error);
//       printf("!!! vertex shader error:\n%s\n", shader_error);
//   }
//
//   GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
//   glShaderSource(fragment_shader_id, 1, &glsl_fragment, nullptr);
//   glCompileShader(fragment_shader_id);
//
//   glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compile_status);
//   if (compile_status == GL_FALSE) {
//       GLchar shader_error[1024] = {};
//       glGetShaderInfoLog(fragment_shader_id, sizeof(shader_error), nullptr, shader_error);
//       printf("!!! fragment shader error:\n%s\n", shader_error);
//   }
//
//   GLuint shader_program_id = glCreateProgram();
//   glAttachShader(shader_program_id, vertex_shader_id);
//   glAttachShader(shader_program_id, fragment_shader_id);
//   glLinkProgram(shader_program_id);
//
//   GLint link_status = GL_TRUE;
//   glGetProgramiv(shader_program_id, GL_LINK_STATUS, &link_status);
//   if (link_status == GL_FALSE) {
//       GLchar program_error[1024] = {};
//       glGetProgramInfoLog(shader_program_id, sizeof(program_error), nullptr, program_error);
//       printf("!!! shader program error\n%s\n", program_error);
//   }
//
//
//   /*------------------------------------------------SHADER---------------------------------------------*/
//
//   /*------------------------------------------------MESHES---------------------------------------------*/
//
//   const GLint projection_location = glGetUniformLocation(shader_program_id, "u_projection");
//   const GLint world_location = glGetUniformLocation(shader_program_id, "u_world");
//   const GLint light_direction_location = glGetUniformLocation(shader_program_id, "u_light_direction");
//   const GLint light_color_location = glGetUniformLocation(shader_program_id, "u_light_color");
//
//   const glm::vec3 light_direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
//   const glm::vec4 light_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//   // Cube 1
//   GLuint vertex_array_id = 0;
//   glGenVertexArrays(1, &vertex_array_id);
//   glBindVertexArray(vertex_array_id);
//
//   GLuint vertex_buffer_id = 0;
//   glGenBuffers(1, &vertex_buffer_id);
//   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(sixSidedCube), sixSidedCube, GL_STATIC_DRAW);
//
//   glEnableVertexAttribArray(0);
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));
//
//   glEnableVertexAttribArray(1);
//   glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, r));
//
//   glEnableVertexAttribArray(2);
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, u));
//
//   glEnableVertexAttribArray(3);
//   glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, nx));
//
//   // Cube 2
//   GLuint vertex_array_id2 = 1;
//   glGenVertexArrays(1, &vertex_array_id2);
//   glBindVertexArray(vertex_array_id2);
//
//   GLuint vertex_buffer_id2 = 1;
//   glGenBuffers(1, &vertex_buffer_id2);
//   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id2);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(oneSidedCube), oneSidedCube, GL_STATIC_DRAW);
//
//   glEnableVertexAttribArray(0);;
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));
//
//   glEnableVertexAttribArray(1);
//   glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, r));
//
//   int image_width = 0, image_height = 0, image_components = 0;
//   auto image_data = stbi_load("data/gravel.png", &image_width, &image_height, &image_components, STBI_rgb_alpha);
//   assert(image_data);
//
//
//   GLuint texture_id = 0;
//   glGenTextures(1, &texture_id);
//   glBindTexture(GL_TEXTURE_2D, texture_id);
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
//   glGenerateMipmap(GL_TEXTURE_2D);
//   //assert(glGetError == GL_NO_ERROR);
//   stbi_image_free(image_data);
//
//   GLuint sampler_id = 0;
//   glGenSamplers(1, &sampler_id);
//   glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//   glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//   float time = 0.0f;
//
//   CelestialBody sunBody = CelestialBody(1000.0f, 1000.0f, 109.0f, 0.0f);
//   CelestialBody mercuryBody = CelestialBody(58.65f, 0.24f, 0.383f, 0.39f);
//   CelestialBody venusBody = CelestialBody(58.65f, 0.62f, 0.949f, 0.72f);
//   CelestialBody earthBody = CelestialBody(1.0f, 1.0f, 1.0f, 1.0f);
//   CelestialBody moonBody = CelestialBody(29.53f, 0.0027f, 0.2725f, 0.00257f, true);
//   CelestialBody marsBody = CelestialBody(1.03f, 1.88f, 0.532f, 1.52f);
//   CelestialBody jupiterBody = CelestialBody(0.41f, 11.86f, 11.209f, 5.20f);
//   CelestialBody saturnBody = CelestialBody(0.44f, 29.45f, 9.449f, 9.54f);
//   CelestialBody uranusBody = CelestialBody(58.65f, 84.02f, 4.007f, 19.19f);
//   CelestialBody neptuneBody = CelestialBody(0.67f, 164.79f, 3.883f, 30.07f);
//
//   /*------------------------------------------------MESHES---------------------------------------------*/
//
//   while (!glfwWindowShouldClose(window)) {
//       int width = 0, height = 0;
//       glfwGetFramebufferSize(window, &width, &height);
//
//       time += deltaTime;
//       if (useRealMetrics) {
//           cameraDistance = -100.0f;
//       }
//       else {
//           cameraDistance = -80.0f;
//       }
//
//
//       sunBody.Update();
//       mercuryBody.Update();
//       venusBody.Update();
//       earthBody.Update();
//       moonBody.Update();
//       marsBody.Update();
//       jupiterBody.Update();
//       saturnBody.Update();
//       uranusBody.Update();
//       neptuneBody.Update();
//
//       glClearDepth(1.0f);
//       glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//       glViewport(0, 0, width, height);
//       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//       glEnable(GL_CULL_FACE);
//       glCullFace(GL_BACK);
//
//       glEnable(GL_DEPTH_TEST);
//
//       glUseProgram(shader_program_id);
//       glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
//       glUniformMatrix3fv(light_direction_location, 1, GL_FALSE, glm::value_ptr(light_direction));
//       glUniformMatrix4fv(light_color_location, 1, GL_FALSE, glm::value_ptr(light_color));
//       glBindVertexArray(vertex_array_id);
//
//       glBindTexture(GL_TEXTURE_2D, texture_id);
//       glBindSampler(0, sampler_id);
//
//       sunBody.Draw(world_location, primitive_count);
//
//       //glBindVertexArray(vertex_array_id2);
//
//       mercuryBody.Draw(world_location, primitive_count);
//       venusBody.Draw(world_location, primitive_count);
//       earthBody.Draw(world_location, primitive_count);
//       moonBody.Draw(world_location, primitive_count);
//       marsBody.Draw(world_location, primitive_count);
//       jupiterBody.Draw(world_location, primitive_count);
//       saturnBody.Draw(world_location, primitive_count);
//       uranusBody.Draw(world_location, primitive_count);
//       neptuneBody.Draw(world_location, primitive_count);
//
//       glfwSwapBuffers(window);
//       glfwPollEvents();
//   }
//   
//   glfwTerminate();
//
//   return 0;
//}
//
