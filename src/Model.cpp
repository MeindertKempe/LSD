#include "model.h"
#include <fstream>
#include <streambuf>
#include <iostream>

Model::Model(){}
Model::~Model(){}


void Model::LoadModel(std::string fileName){
    using json = nlohmann::json;

    std::string filePath = "resources/models/" + fileName;
    std::ifstream gltfFile(filePath);
    jsonData = json::parse(gltfFile);
   
    //get .bin file with all the data. Needs to exist (for now)
    std::string uri = jsonData["buffers"][0]["uri"];
    std::string fileDirectory = filePath.substr(0, filePath.find_last_of('/') + 1);
    std::ifstream binaryFile(fileDirectory + uri, std::ios::binary);
    
    //read entire binary file into a string in one line because im lazy.
    std::string bytesString((std::istreambuf_iterator<char>(binaryFile)), std::istreambuf_iterator<char>());
    binaryData = std::vector<u8>(bytesString.begin(), bytesString.end());
    gltfFile.close();
    binaryFile.close();

    u32 meshCount = jsonData["meshes"].size();
    u32 vertexOffset = 0;

    for(i32 i = 0; i < meshCount; i++){
        u32 positionIndex = jsonData["meshes"][i]["primitives"][0]["attributes"]["POSITION"];
        u32 normalIndex = jsonData["meshes"][i]["primitives"][0]["attributes"]["NORMAL"];
        u32 uvIndex = jsonData["meshes"][i]["primitives"][0]["attributes"]["TEXCOORD_0"];
        u32 indicesIndex = jsonData["meshes"][i]["primitives"][0]["indices"];

        std::vector<f32> positionData = GetVertexData(jsonData["accessors"][positionIndex]);
        std::vector<glm::vec3> positions = PackToVec3(positionData);
        std::vector<f32> normalData = GetVertexData(jsonData["accessors"][normalIndex]);
        std::vector<glm::vec3> normals = PackToVec3(normalData);
        std::vector<f32> uvData = GetVertexData(jsonData["accessors"][uvIndex]);
        std::vector<glm::vec2> UVs = PackToVec2(uvData);

        for(i32 j = 0; j < positions.size(); j++){
            vertices.push_back(positions[j].z);
            vertices.push_back(positions[j].y);
            vertices.push_back(positions[j].x);
            
            vertices.push_back(normals[j].z);
            vertices.push_back(normals[j].y);
            vertices.push_back(normals[j].x);
            
            vertices.push_back(UVs[j].x);
            vertices.push_back(UVs[j].y);
        }

        std::vector<u32> indexData = GetIndexData(jsonData["accessors"][indicesIndex]);
        for(i32 k = 0; k < indexData.size(); k++){
            indices.push_back(indexData[k] + vertexOffset);
        }

        vertexOffset = positions.size();
    }
}

void Model::DestroyModel(){
    
}

std::vector<f32> Model::GetVertexData(json accessor){
    std::vector<f32> data;
    //Model has multiple bufferViews for vertices, normals, uvs, etc. this is the index for accessor[0] which is vertices.
    u32 bufferViewIndex = accessor.value("bufferView", 0);

    //Get vertex data
    json bufferView = jsonData["bufferViews"][bufferViewIndex];
    u32 byteOffset = bufferView["byteOffset"];
    u32 bufferLength  = bufferView["byteLength"];

    //index of starting data is the buffer offset + byte offset in buffer
    for(i32 i = byteOffset; i < byteOffset + bufferLength; i){
        //One float value is 4 bytes 
        u8 bytes[] = {binaryData[i++], binaryData[i++], binaryData[i++], binaryData[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        data.push_back(value);
    }

    return data;
}

std::vector<u32> Model::GetIndexData(json accessor){
    std::vector<u32> data;

    u32 bufferViewIndex = accessor.value("bufferView", 0);
    u32 componentType = accessor["componentType"];

    json bufferView = jsonData["bufferViews"][bufferViewIndex];
    u32 byteOffset = bufferView["byteOffset"];
    u32 bufferLength = bufferView["byteLength"];

    if(componentType == 5125){
        for(u32 i = byteOffset; i < byteOffset + bufferLength;){
            //One int value is 4 bytes
            u8 bytes[] = {binaryData[i++], binaryData[i++], binaryData[i++], binaryData[i++]};
            u32 value;
            std::memcpy(&value, bytes, sizeof(u32));
            data.push_back(value);
        }
    }
    else if(componentType == 5123){
            for(u32 i = byteOffset; i < byteOffset + bufferLength;){
                //One short value is 2 bytes
                u8 bytes[] = {binaryData[i++], binaryData[i++]};
                u16 value;
                std::memcpy(&value, bytes, sizeof(u16));
                data.push_back((u32)value);
            }
    }        

    return data;
}

std::vector<glm::vec3> Model::PackToVec3(std::vector<f32> floats){
    std::vector<glm::vec3> data;

    for (i32 i = 0; i < floats.size(); i){
        data.push_back(glm::vec3(floats[i++], floats[i++], floats[i++]));
    }

    return data;
}

std::vector<glm::vec2> Model::PackToVec2(std::vector<f32> floats){
    std::vector<glm::vec2> data;

    for (i32 i = 0; i < floats.size(); i){
        data.push_back(glm::vec2(floats[i++], floats[i++]));
    }

    return data;
}


std::vector<f32>* Model::GetVertices(){
    return &vertices;
}

std::vector<u32>* Model::GetIndices(){
    return &indices;
}