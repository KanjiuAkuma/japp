#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoordinates;

out vec2 v_texCoordinates;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
	mat4 mvp = u_proj * u_view * u_model;
	gl_Position = mvp * position;
	v_texCoordinates = texCoordinates;
};
