#pragma once
#include "draw_component.h"
#include "render_object.h"
#include "texture.h"

extern f32 block_vertices[];

class BlockComponent : public DrawComponent
{
private:
    Texture texture;
    RenderObject renderObject;

public:
	BlockComponent(std::string texturePath, f32* verticesToDraw = block_vertices);
	~BlockComponent();

	virtual void Draw(glm::mat4 projectionView, glm::mat4 transform) override;
};