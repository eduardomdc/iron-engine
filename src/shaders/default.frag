#version 330 core

in vec3 normal;
in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

void main(){
    fragColor = vec4(color, 1.0f);
}
