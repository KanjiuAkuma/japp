#shader fragment
#version 330 core

in vec3 vertexColor;
in vec2 uv;
out vec3 pixelColor;
uniform sampler2D u_texture;


void main() {

	vec4 texel = texture(u_texture, uv);
	pixelColor = texel.rgb;
}