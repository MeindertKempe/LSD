#define SDL_MAIN_HANDLED
#include "block_component.h"
#include "camera.h"
#include "control_component.h"
#include "game_object.h"
#include "model_component.h"
#include "move_to_component.h"
#include "spin_component.h"
#include "window.h"
#include <iostream>
#include <random>

Window window;
Camera camera;
ControlComponent controller;
std::vector<GameObject *> gameObjects;
std::vector<GameObject *> laneObjects;
std::vector<GameObject *> blockObjects;
std::vector<GameObject *> coinObjects;
f64 lastFrameTime = 0;

void Init();
void Update();
void Render();
void Close();

int main(int argc, char *argv[]) {
	Init();
	while (!window.WindowShouldClose()) {
		Update();
		Render();
	}
	Close();
	return 0;
}

void Init() {
	std::cout << "Initializing window..." << std::endl;
	window.InitializeWindow("Lsd Run", 1280, 720);
	std::cout << "Window initialized successfully." << std::endl;

	camera.InitializeCamera(glm::vec3{ 0, 5, 0 });

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distBlock(1, 3);

	int randBlock;

	for (int i = 0; i < 100; i++) {
		GameObject *lane = new GameObject();
		if (!lane) {
			std::cerr << "Failed to allocate memory for lane GameObject!" << std::endl;
			return;
		}
		lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
		lane->position = glm::vec3(0, 0, i * 10);
		lane->AddComponent(new MoveToComponent(&lane->position));
		laneObjects.push_back(lane);
	}
	std::cout << "Lane objects initialized successfully." << std::endl;

	GameObject *player = new GameObject();
	if (!player) {
		std::cerr << "Failed to allocate memory for player GameObject!" << std::endl;
		return;
	}
	player->AddDrawComponent(new ModelComponent("player/player.gltf", "player.png"));
	controller.player = player;
	player->AddComponent(&controller);
	player->position = glm::vec3(0.0, 1.0, 0.0);
	player->scale = glm::vec3(5);
	gameObjects.push_back(player);
	std::cout << "Player object initialized successfully." << std::endl;

	for (int i = 0; i < 100; i++) {
		randBlock = distBlock(gen);

		GameObject *block = new GameObject();
		block->AddDrawComponent(new BlockComponent("stone.png"));

//		GameObject *coin = new GameObject();
//		coin->AddDrawComponent(new ModelComponent("coin/coin.gltf", "coin.png"));

		switch (randBlock) {
			case 1:
				block->position = glm::vec3(-3.7, 2.0, i * 20);
//				coin->position = (randBlock % 2 == 0) ? glm::vec3(0, 3.0, i * 20) : glm::vec3(3.7, 3.0, i * 20);
				break;
			case 2:
				block->position = glm::vec3(0, 2.0, i * 20);
//				coin->position = (randBlock % 2 == 0) ? glm::vec3(-3.7, 3.0, i * 20) : glm::vec3(3.7, 3.0, i * 20);
				break;
			case 3:
				block->position = glm::vec3(3.7, 2.0, i * 20);
//				coin->position = (randBlock % 2 == 0) ? glm::vec3(0, 3.0, i * 20) : glm::vec3(-3.7, 3.0, i * 20);
				break;
		}

		block->AddComponent(new MoveToComponent(&block->position));
		block->scale = glm::vec3(3);

//		coin->AddComponent(new MoveToComponent(&coin->position));

//		coinObjects.push_back(coin);
		blockObjects.push_back(block);

		std::cout << "Block and coin pair " << i + 1 << " created successfully." << std::endl;
	}
	std::cout << "Block and coin objects initialized successfully." << std::endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void Update() {
	window.PollEvents();
	SDL_Event e;
	e = window.GetEvent();
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
		std::cout << "Escape pressed | closing the application" << "\n";
		window.Quit();
	}

	if (!laneObjects.empty() && laneObjects.front()->position.z <= -40) {
		laneObjects.erase(laneObjects.begin());
		GameObject *lane = new GameObject();
		lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
		lane->position = glm::vec3(0, 0, 960);
		lane->AddComponent(new MoveToComponent(&lane->position));
		laneObjects.push_back(lane);
	}

	// Calculate deltaTime
	f64 currentFrameTime = SDL_GetTicks64();
	f64 deltaTime        = currentFrameTime - lastFrameTime;
	lastFrameTime        = currentFrameTime;

	for (auto gameObject : gameObjects) {
		if (gameObject != nullptr) {
			gameObject->Update(deltaTime);
		}
	}

	for (auto gameObject : laneObjects) {
		if (gameObject != nullptr) {
			gameObject->Update(deltaTime);
		}
	}

	for (auto gameObject : blockObjects) {
		if (gameObject != nullptr) {
			gameObject->Update(deltaTime);
		}
	}

	for (auto gameObject : coinObjects) {
		if (gameObject != nullptr) {
			gameObject->Update(deltaTime);
		}
	}

	camera.Update(glm::vec3{ 0, 7, -5 });
	controller.CheckKeyPress(e);
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6, 0.7, 0.8, 1.0);

	glm::mat4 projectionView = camera.GetViewProjectionMatrix();
	for (auto gameObject : gameObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : laneObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : blockObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : coinObjects) { gameObject->Draw(projectionView); }

	window.SwapBuffers();
}

void Close() { window.DestroyWindow(); }
