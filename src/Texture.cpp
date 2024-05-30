#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cstdio>
#include <iostream>

Texture::Texture() {}
Texture::~Texture() {}

void Texture::InitializeFromFile(std::string fileName) {
	glGenTextures(1, &textureID);

	std::string filePath = "resources/textures/" + fileName;
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the textures
	i32 width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	u8 *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (data && (nrChannels == 4 || nrChannels == 3)) {
		if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			             data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
			             data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::DestroyTexture() { glDeleteTextures(1, &textureID); }

void Texture::ActivateTexture(i32 textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
