#pragma once
#include "draw_component.h"
#include "model.h"
#include "render_object.h"
#include "shader.h"
#include "texture.h"

class ModelComponent : public DrawComponent {
private:
	Shader shader;
	Texture texture;
	RenderObject renderObject;
	Model model;

public:
	ModelComponent(std::string modelPath, std::string texturePath);
	~ModelComponent();

	virtual void Draw(glm::mat4 projectionView, glm::mat4 transform) override;
};
