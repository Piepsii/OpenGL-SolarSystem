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
        float u, v;
    };

    struct Mesh {
        int m_offset;
        int m_count;
    };

    static const vertex cube[36] = {
        // front
        {  1.0f,  1.0f,  1.0f,    0.0f, 1.0f,},
        { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f,},
        { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f,},
        { -1.0f, -1.0f,  1.0f,    1.0f, 0.0f,},
        {  1.0f, -1.0f,  1.0f,    0.0f, 0.0f,},
        {  1.0f,  1.0f,  1.0f,    0.0f, 1.0f,},
        // left                              
        { -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,},
        { -1.0f,  1.0f,  1.0f,    1.0f, 1.0f,},
        { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f,},
        { -1.0f,  1.0f, -1.0f,    1.0f, 0.0f,},
        { -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,},
        { -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,},
        // right                             
        {  1.0f, -1.0f, -1.0f,    0.0f, 1.0f,},
        {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f,},
        {  1.0f,  1.0f,  1.0f,    1.0f, 0.0f,},
        {  1.0f,  1.0f,  1.0f,    1.0f, 0.0f,},
        {  1.0f, -1.0f,  1.0f,    0.0f, 0.0f,},
        {  1.0f, -1.0f, -1.0f,    0.0f, 1.0f,},
        // back                              
        { -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,},
        {  1.0f,  1.0f, -1.0f,    1.0f, 1.0f,},
        {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f,},
        {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f,},
        { -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,},
        { -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,},
        // top                               
        { -1.0f,  1.0f,  1.0f,    0.0f, 1.0f,},
        {  1.0f,  1.0f,  1.0f,    1.0f, 1.0f,},
        {  1.0f,  1.0f, -1.0f,    1.0f, 0.0f,},
        {  1.0f,  1.0f, -1.0f,    1.0f, 0.0f,},
        { -1.0f,  1.0f, -1.0f,    0.0f, 0.0f,},
        { -1.0f,  1.0f,  1.0f,    0.0f, 1.0f,},
        // bottom                            
        { -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,},
        {  1.0f, -1.0f,  1.0f,    1.0f, 1.0f,},
        {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f,},
        {  1.0f, -1.0f, -1.0f,    1.0f, 0.0f,},
        { -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,},
        { -1.0f, -1.0f,  1.0f,    0.0f, 1.0f,},
    };

    const float AU = 12000.0f;
    const float earthDiameter = AU / 23481.f;
}
