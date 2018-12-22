#shader vertex
#version 460 core

layout(location = 0) in float in_radius;
layout(location = 1) in float in_glow;
layout(location = 2) in vec3 in_color;

uniform mat4 u_view;
uniform mat4 u_proj;
uniform vec2 u_position;

out mat4 v_mvp;
out float v_radius;
out float v_glow;
out vec3 v_color;

void main() {
	gl_Position = vec4(u_position, 0, 1);
	v_mvp = u_view * u_proj;
	v_radius = in_radius;
	v_glow = in_glow;
	v_color = in_color;

}