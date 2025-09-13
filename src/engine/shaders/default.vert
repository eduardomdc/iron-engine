#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

uniform mat4 camera;
uniform mat4 model;

out vec3 fragPosition;
out vec3 normal;
out vec3 color;
out vec2 texCoord;

void main(){
    gl_Position = camera * model * vec4(aPos, 1.0);
    fragPosition = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(model)))*aNormal;
    color = aColor;
    texCoord = aTex;
}
