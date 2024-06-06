#pragma once
#include "dependencies.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum BufferType {
	VERTEX_BUFFER,
	ELEMENT_BUFFER,
	INDIRECT_BUFFER,
	INSTANCED_BUFFER,
};

enum DrawType {
	DRAW_ARRAY,
	DRAW_ELEMENT,
};

typedef struct {
	u32 count;
	u32 instanceCount;
	u32 first;
	u32 baseInstance;
} DrawArraysIndirectCommand;

typedef struct {
	u32 count;
	u32 instanceCount;
	u32 firstIndex;
	u32 baseVertex;
	u32 baseInstance;
} DrawElementsIndirectCommand;

class RenderObject {
private:
	u32 vao;
	u32 vbo;
	u32 ivbo;
	u32 ibo;
	u32 ebo;
	u8 attributeCount = 0;

public:
	RenderObject();
	~RenderObject();

	void IntializeRenderObject();
	void DestroyRenderObject();

	void BufferData(BufferType bufferType, i32 drawType, void *data, i32 dataLength, i32 dataSize);
	void AddAttribute(u8 isInstanced, u8 isFloat, i32 attributeType, i32 vectorCount, i32 stride,
	                  i32 offset);
	void Draw(DrawType drawType, i32 primitiveType, i32 count);
	void DrawIndirect(DrawType drawType, i32 primitiveType, i32 count);
};
