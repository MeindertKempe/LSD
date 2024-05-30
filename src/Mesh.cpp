#include "mesh.h"

Mesh::Mesh(){

}

Mesh::Mesh(f32* verticesToDraw){

}

void Mesh::draw(){

}

Mesh::~Mesh(){

}


// Cube coordinates with the texture coordinates
f32 block_vertices[] = {
    // Back face         texture coordinates
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // top-left
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // top-right         
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};

