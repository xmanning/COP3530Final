#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
uniform mat4 view;
uniform mat4 projection;
out vec3 color;
void main() {
	color = normal;
	gl_Position = view * projection * vec4(pos, 1.0f);
}