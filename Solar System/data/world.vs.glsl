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