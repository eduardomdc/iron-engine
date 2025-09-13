#version 330 core

out vec4 fragColor;

in vec3 fragPosition;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D texture_sampler;
uniform vec3 light_color;
uniform vec3 light_position;

void main(){
    vec3 n_normal = normalize(normal);
    vec3 light_dir = normalize(light_position-fragPosition);
    float diffuse_value = max(dot(n_normal, light_dir), 0.0);
    vec3 diffuse_color = diffuse_value * light_color;
    vec3 final_color = diffuse_color + vec3(0.1f, 0.1f, 0.1f);
    fragColor = (vec4(final_color, 1))*texture(texture_sampler, texCoord);
}
