#include "render_object.h"
#include <iostream>

RenderObject::RenderObject() {}

RenderObject::~RenderObject() {}

void RenderObject::IntializeRenderObject() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ivbo);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vao);
}

void RenderObject::DestroyRenderObject() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ivbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
}

void RenderObject::BufferData(BufferType bufferType, i32 usage, void *data, i32 dataLength,
                              i32 dataSize) {
	glBindVertexArray(vao);
	u32 bufferTarget = 0;

	switch (bufferType) {
		case VERTEX_BUFFER:
			bufferTarget = GL_ARRAY_BUFFER;
			glBindBuffer(bufferTarget, vbo);
			break;
		case ELEMENT_BUFFER:
			bufferTarget = GL_ELEMENT_ARRAY_BUFFER;
			glBindBuffer(bufferTarget, ebo);
			break;
		case INDIRECT_BUFFER:
			bufferTarget = GL_DRAW_INDIRECT_BUFFER;
			glBindBuffer(bufferTarget, ibo);
			break;
		case INSTANCED_BUFFER:
			bufferTarget = GL_ARRAY_BUFFER;
			glBindBuffer(bufferTarget, ivbo);
			break;
	}

	glBufferData(bufferTarget, dataLength * dataSize, data, usage);

	glBindVertexArray(0);
	glBindBuffer(bufferTarget, 0);
}

void RenderObject::AddAttribute(u8 isInstanced, u8 isFloat, i32 attributeType, i32 vectorCount,
                                i32 stride, i32 offset) {
	glBindVertexArray(vao);

	if (isInstanced) {
		glBindBuffer(GL_ARRAY_BUFFER, ivbo);
		glVertexAttribDivisor(attributeCount, 1);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	if (isFloat) {
		glVertexAttribPointer(attributeCount, vectorCount, attributeType, GL_FALSE, stride,
		                      (void *)(offset));
	} else {
		glVertexAttribIPointer(attributeCount, vectorCount, attributeType, stride,
		                       (void *)(offset));
	}

	glEnableVertexAttribArray(attributeCount);
	attributeCount++;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderObject::Draw(DrawType drawType, i32 primitiveType, i32 count) {
	glBindVertexArray(vao);

	switch (drawType) {
		case DRAW_ARRAY: glDrawArrays(primitiveType, 0, count); break;
		case DRAW_ELEMENT: glDrawElements(primitiveType, count, GL_UNSIGNED_INT, 0); break;
	}
	glBindVertexArray(0);
}

void RenderObject::DrawIndirect(DrawType drawType, i32 primitiveType, i32 count) {
	glBindVertexArray(vao);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);

	// Last parameter is 0 because its tightly packed
	switch (drawType) {
		case DRAW_ARRAY: glMultiDrawArraysIndirect(primitiveType, 0, count, 0); break;
		case DRAW_ELEMENT:
			glMultiDrawElementsIndirect(primitiveType, GL_UNSIGNED_INT, 0, count, 0);
			break;
	}

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	glBindVertexArray(0);
}
