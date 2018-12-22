#shader geometry
#version 460 core

// particle vertices = 3
// glow vertices = 27

layout(points) in;
layout(triangle_strip, max_vertices = 30) out;


// in
in mat4 v_mvp[];
in float v_radius[];
in float v_glow[];
in vec3 v_color[];

// out
out vec4 color;

// given data
mat4 mvp = v_mvp[0];
float glow = v_glow[0];
float radius = v_radius[0];
vec4 col = vec4(v_color[0], 1.f);
vec4 pos = gl_in[0].gl_Position;

// particle points
vec2 left = vec2(-sqrt(3.f) / 2.f, -1.f / 2.f) * radius;
vec2 right = vec2(sqrt(3.f) / 2.f, -1.f / 2.f) * radius;
vec2 top = vec2(0.f, 1.f) * radius;

vec2 center(vec2 v1, vec2 v2) {
	return v1 + (v2 - v1) / 2;
}

// glow points
vec2 gLeft = left * glow;
vec2 gRight = right * glow;
vec2 gTop = top * glow;
vec2 gCenterLeft = center(gLeft, gTop);
vec2 gCenterRight = center(gRight, gTop);
vec2 gCenterBottom = center(gLeft, gRight);

// glow color
vec4 geCol = col / 100;
vec4 gsCol = col / 10;

// Emmits 3 vertices... a trinagle!
void makeTriangle(vec2 p1, vec2 p2, vec2 p3, vec4 c1, vec4 c2, vec4 c3) {
	color = c1;
	gl_Position = mvp * (pos + vec4(p1, 0, 0));
	EmitVertex();

	color = c2;
	gl_Position = mvp * (pos + vec4(p2, 0, 0));
	EmitVertex();

	color = c3;
	gl_Position = mvp * (pos + vec4(p3, 0, 0));
	EmitVertex();
	EndPrimitive();
}

void makeGlow() {
	makeTriangle(gLeft, left, gCenterBottom, geCol, gsCol, geCol);
	makeTriangle(left, gCenterBottom, right, gsCol, geCol, gsCol);
	makeTriangle(gCenterBottom, gRight, right, geCol, geCol, gsCol);
	makeTriangle(right, gRight, gCenterRight, gsCol, geCol, geCol);
	makeTriangle(top, right, gCenterRight, gsCol, gsCol, geCol);
	makeTriangle(top, gCenterRight, gTop, gsCol, geCol, geCol);
	makeTriangle(gCenterLeft, top, gTop, geCol, gsCol, geCol);
	makeTriangle(gCenterLeft, left, top, geCol, gsCol, gsCol);
	makeTriangle(gLeft, left, gCenterLeft, geCol, gsCol, geCol);
}

void makeParticle() {
	makeTriangle(left, right, top, col, col, col);
}

void main()
{
	makeGlow();
	makeParticle();
}