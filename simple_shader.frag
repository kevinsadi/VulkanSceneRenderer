#version 450

// layout qualifier takes a location value
layout (location = 0) out vec4 outColor;

void main() {
	outColor = vec4(1, 0, 0, 1);

}