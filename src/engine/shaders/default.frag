#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D texture_sampler;

void main(){
    fragColor = vec4(color, 1)*texture(texture_sampler, texCoord);
}
