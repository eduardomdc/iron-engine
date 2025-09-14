#version 330 core

out vec4 fragColor;

in vec3 fragPosition;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture_sampler;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

float specular_strength = 0.9;

void main(){
    vec3 n_normal = normalize(normal);
    vec3 light_dir = normalize(light_position-fragPosition);
    vec3 view_dir = normalize(view_position-fragPosition);
    vec3 reflect_dir = reflect(-light_dir, n_normal);
    vec3 ambient_color = vec3(0.1f, 0.1f, 0.1f);
    float specular_component = pow(max(dot(view_dir, reflect_dir), 0.0), 64);
    vec3 specular_color = specular_strength * specular_component * light_color;
    float diffuse_value = max(dot(n_normal, light_dir), 0.0);
    vec3 diffuse_color = diffuse_value * light_color;
    vec3 final_color = specular_color + diffuse_color + ambient_color;
    fragColor = (vec4(final_color, 1))*texture(texture_sampler, texCoord);
}
