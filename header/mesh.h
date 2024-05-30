#pragma once

#include "dependencies.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

extern float block_vertices[];

class Mesh{
    public:
        u32 VBO, VAO;
        Mesh();
        Mesh(f32* verticesToDraw);
        ~Mesh();
        void draw();
};
