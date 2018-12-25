#include "Mesh.h"

Mesh::Mesh(VertexArray* va, VertexBuffer* vb, VertexBufferLayout* vbl, IndexBuffer* ib)
	: va(va), vb(vb), vbl(vbl), ib(ib) {}

Mesh::~Mesh() {
	delete va;
	delete vb;
	delete vbl;
	delete ib;
}

void Mesh::bind() const {
	va->bind();
	ib->bind();
}
