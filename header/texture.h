#pragma once
#include "dependencies.h"
#include "glad/glad.h"
#include <string>

class Texture{
    u32 textureID;
    
public:
    Texture();
    ~Texture();

    void InitializeFromFile(std::string fileName);
    void DestroyTexture();
    void ActivateTexture(i32 textureUnit);
};