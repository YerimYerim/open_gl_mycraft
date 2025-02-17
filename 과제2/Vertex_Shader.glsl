#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

out vec3 passColor;
out vec3 fragPos;
out vec3 Normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
   gl_Position = projection *view * model * vec4(vPos, 1.0);
   fragPos = vec3(model* vec4(vPos, 1.0));
   Normal = vNormal;
}