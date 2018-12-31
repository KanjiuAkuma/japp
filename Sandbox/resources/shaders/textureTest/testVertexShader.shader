#shader vertex
#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uvKoord;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 vertexColor;
out vec2 uv;

void main() {


	vertexColor = vec3(1.0, 0.0, 0.0);
	uv = uvKoord;
	gl_Position = u_proj * u_view * u_model *vec4(vertex, 1.0);

}