// Settings.h

#pragma once
#include <cstdio>
#include <cassert>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace SolarSystem {



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

    const float PI = 3.141592f;
    const float ASPECT = 1.0f / 1.0f;
    const float NEAR = 1.0f;
    const float FAR = 500.0f;
    const int primitive_count = sizeof(sixSidedCube) / sizeof(sixSidedCube[0]);

    const float AU = 12000.0f;
    const float earthDiameter = AU / 23481.f;
    static float cursorPosX = 0.0f, cursorPosY = 0.0f;
    static float deltaTime = 0.00001f;
    static float cameraDistance = -50.0f;
    static float mousePosX = 0.0f, mousePosY = 0.0f;
    static int windowWidth = 720, windowHeight = 720;
    static glm::mat4 projection = glm::perspective(PI * 0.4f, ASPECT, NEAR, FAR);

    static float rotationRateEarth = deltaTime, orbitalPeriodEarth = rotationRateEarth * 365.0f;
    static glm::mat4 world = glm::mat4(1.0f);
    static glm::mat4 view = glm::mat4(1.0f);
    static bool useRealMetrics = false;
}
