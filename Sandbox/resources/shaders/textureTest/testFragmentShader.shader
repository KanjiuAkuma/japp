#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoordinates;

uniform sampler2D u_Texture;

void main() {
	// vec4 texColor = texture(u_Texture, vec2(1.25, 0.f));
	vec4 texColor = texture(u_Texture, v_texCoordinates);
	color = texColor;
};