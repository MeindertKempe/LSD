#pragma once
#include <string>
#include "dependencies.h"
#include "glad/glad.h"



class Shader{
private:
    u32 programID;
    u32 GenShader(std::string path, u32 type);
    std::string LoadShaderFromFile(std::string filePath);
    void CheckCompileErrors(u32 id, std::string type);

public:
    Shader();
    ~Shader();

    void InitializeShader(std::string vertexPath, std::string fragmentPath);
    void DestroyShader();
    void UseProgram();
    u32 GetProgram();
};