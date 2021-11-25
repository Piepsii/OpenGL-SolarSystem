// Shaders.h

#pragma once

namespace SolarSystem {

    const char* glsl_vertex = R"(
    #version 330

    layout (location = 0) in vec3 a_position;
    layout (location = 1) in vec4 a_color;
    layout (location = 2) in vec2 a_texcoord;
    layout (location = 3) in vec3 a_normal;

    uniform mat4 u_projection;
    uniform mat4 u_world;

    out vec4 v_color;
    out vec2 v_texcoord;
    out vec3 v_normal;

    void main(){
        gl_Position = u_projection * u_world * vec4(a_position, 1);
        v_color = a_color;
        v_texcoord = a_texcoord;
        v_normal = normalize((u_world * vec4(normalize(a_normal), 0)).xyz);
    }
    )";

    const char* glsl_fragment = R"(
    #version 330

    uniform vec3 u_light_direction;
    uniform vec4 u_light_color;

    uniform sampler2D u_diffuse;

    in vec4 v_color;
    in vec2 v_texcoord;
    in vec3 v_normal;
    out vec4 final_color;

    void main(){
        vec3 L = -normalize(u_light_direction);
        vec3 N = normalize(v_normal);
        float NdotL = max(0.0, dot(N, L));
        vec4 diffuse_color = NdotL * u_light_color;

        final_color = texture(u_diffuse, v_texcoord) * v_color * diffuse_color;
        final_color = texture(u_diffuse, v_texcoord) * v_color;

    }
    )";
}
