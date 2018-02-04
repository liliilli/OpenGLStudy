#version 430 core

in VS_OUT {
	vec3 fragmentPos;
	vec3 normalDir;
	vec2 textureCoord;
} fs_in;

uniform vec3 uColor;

layout (location = 0) out vec4 finalColor;
layout (location = 1) out vec4 brightColor;

void main() {
	finalColor = vec4(uColor, 1.0f);
	brightColor = vec4(uColor, 1.0f);
}