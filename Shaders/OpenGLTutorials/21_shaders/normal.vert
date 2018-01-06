#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;
//uniform vec2 offsets[100];

void main() {
	fColor = aColor;

	//vec2 offset = offsets[gl_InstanceID];
	vec2 offset = aOffset;
    gl_Position = vec4((aPos * gl_InstanceID / 100.0f) + offset, 0, 1.0);
}   