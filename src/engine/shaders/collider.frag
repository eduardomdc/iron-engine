#version 330 core

in vec3 normal;
in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

void main(){
    fragColor = vec4(1.0f, 0.0f, 0.0f, 0.3f);
}
