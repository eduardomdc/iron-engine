#version 330 core

out vec4 fragColor;

in vec3 fragPosition;
in vec3 vert_normal;
in vec2 texCoord;

uniform sampler2D texture_sampler;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

float specular_strength = 1.0;
float shiny = 256.0;

void main(){
    vec3 normal = normalize(vert_normal);
    // blinn-phong
    vec3 light_dir = normalize(light_position-fragPosition);
    vec3 view_dir = normalize(view_position-fragPosition);
    vec3 halfway_dir = normalize(light_dir+view_dir);
    float specular_component = pow(max(dot(normal, halfway_dir), 0.0), shiny);
    vec3 specular_color = specular_strength * specular_component * light_color;

    vec3 ambient_color = vec3(0.1f, 0.1f, 0.2f);
    float diffuse_value = max(dot(normal, light_dir), 0.0);
    vec3 diffuse_color = diffuse_value * light_color;
    vec3 final_color = specular_color + diffuse_color + ambient_color;
    fragColor = (vec4(final_color, 1))*texture(texture_sampler, texCoord);
}
