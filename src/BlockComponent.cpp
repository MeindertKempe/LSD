#include "block_component.h"

BlockComponent::BlockComponent(std::string texturePath, f32* verticesToDraw){
    
    texture.InitializeFromFile(texturePath);

    renderObject.IntializeRenderObject();

    renderObject.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, verticesToDraw, 60, 12);
    renderObject.AddAttribute(false, true, GL_FLOAT, 3, 5 * sizeof(float), 0);
    renderObject.AddAttribute(false, true, GL_FLOAT, 2, 5 * sizeof(float), 3 * sizeof(float));
}

BlockComponent::~BlockComponent(){
    renderObject.DestroyRenderObject();
    texture.DestroyTexture();
}
    
void BlockComponent::Draw(glm::mat4 projectionView, glm::mat4 modelMatrix){
    texture.ActivateTexture(0);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionView));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    renderObject.Draw(DRAW_ARRAY, GL_TRIANGLES, 36);
}

f32 block_vertices[] = {
    // Back face
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

