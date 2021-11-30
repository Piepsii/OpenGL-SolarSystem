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