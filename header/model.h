#pragma once
#include "dependencies.h"
#include "glm/glm.hpp"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

class Model {
	using json = nlohmann::json;

private:
	std::vector<u8> binaryData;
	std::vector<f32> vertices;
	std::vector<u32> indices;
	json jsonData;

	std::vector<f32> GetVertexData(json accessor);
	std::vector<u32> GetIndexData(json accessor);
	std::vector<glm::vec3> PackToVec3(std::vector<f32> floats);
	std::vector<glm::vec2> PackToVec2(std::vector<f32> floats);

public:
	Model();
	~Model();

	void LoadModel(std::string fileName);
	void DestroyModel();

	std::vector<f32> *GetVertices();
	std::vector<u32> *GetIndices();
};
