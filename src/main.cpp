#define SDL_MAIN_HANDLED
#include "background.h"
#include "bounding_box_component.h"
#include "camera.h"
#include "control_component.h"
#include "game_object.h"
#include "model_component.h"
#include "block_component.h"
#include "move_to_component.h"
#include "spin_component.h"
#include "window.h"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <random>

Window window;
ControlComponent controller;
Camera camera;

std::vector<GameObject *> gameObjects;
std::vector<GameObject *> laneObjects;
std::vector<GameObject *> blockObjects;
std::vector<GameObject *> coinObjects;

Background background;
f64 lastFrameTime = 0;

std::thread visionThread;

int randBlock;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distBlock(1, 3);

void Init();
void Update();
void Render();
void Close();
void StartVision();

int main(UNUSED int argc, UNUSED char *argv[]) {
	Init();
	while (!window.WindowShouldClose()) {
		Update();
		Render();
	}
	Close();
	return 0;
}

void Init() {
	visionThread = std::thread(StartVision);

	window.InitializeWindow("Lsd Run", 1280, 720);
	camera.InitializeCamera(glm::vec3{ 0, 5, 0 });
	camera.Update(glm::vec3{ 0, 5, 0 });

	SDL_GL_SetSwapInterval(1);

	i32 numberOfLanes = 1;
	for (i32 i = 0; i < numberOfLanes; i++) {
		GameObject *lane = new GameObject(&gameObjects);
		lane->scale.z    = 1000;
		lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
		lane->position = glm::vec3(0, 0, i * 10 - 5);
		lane->AddComponent(new MoveToComponent(&lane->position));
		// lane->AddComponent(new SpinComponent(0.0005f));
		gameObjects.push_back(lane);
	}

	GameObject *player = new GameObject(&gameObjects);
	player->AddDrawComponent(new ModelComponent("player/player.gltf", "player.png"));
	player->position = glm::vec3(0.0, 1.0, 0.0);
	player->AddBBComponent(
	    new BoundingBoxComponent(player, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	gameObjects.push_back(player);

	GameObject *coin = new GameObject(&gameObjects);
	coin->AddDrawComponent(new ModelComponent("coin/coin.gltf", "coin.png"));
	coin->AddComponent(new SpinComponent(0.0005f));
	coin->position = glm::vec3(0.0, 2.0, 0.0);
	gameObjects.push_back(coin);

	for (int i = 0; i < 100; i++) {
		bool makeCoin = false;
		if (i % 3 == 0) makeCoin = true;

		randBlock = distBlock(gen);

		GameObject *block = new GameObject(&gameObjects);
		block->AddDrawComponent(new BlockComponent("stone.png"));

		GameObject *coin = nullptr;
		if (makeCoin) {
			coin = new GameObject(&gameObjects);
			coin->AddDrawComponent(new ModelComponent("coin/coin.gltf", "coin.png"));
		}

		switch (randBlock) {
			case 1:
				block->position = glm::vec3(-3.7, 2.0, i * 20);
				if (makeCoin)
					coin->position = (randBlock % 2 == 0) ? glm::vec3(0, 3.0, i * 20)
					                                      : glm::vec3(3.7, 3.0, i * 20);
				break;
			case 2:
				block->position = glm::vec3(0, 2.0, i * 20);
				if (makeCoin)
					coin->position = (randBlock % 2 == 0) ? glm::vec3(-3.7, 3.0, i * 20)
					                                      : glm::vec3(3.7, 3.0, i * 20);
				break;
			case 3:
				block->position = glm::vec3(3.7, 2.0, i * 20);
				if (makeCoin)
					coin->position = (randBlock % 2 == 0) ? glm::vec3(0, 3.0, i * 20)
					                                      : glm::vec3(-3.7, 3.0, i * 20);
				break;
		}

		block->AddComponent(new MoveToComponent(&block->position));
		block->scale = glm::vec3(3);

		if (makeCoin) {
			coin->AddComponent(new SpinComponent(0.005));
			coin->AddComponent(new MoveToComponent(&coin->position));
		}

		if (makeCoin) { coinObjects.push_back(coin); }

		blockObjects.push_back(block);
	}

	// setup background;
	std::vector<f32> quad = { -1, -1, -1, 1, 1, -1, 1, 1 };
	background.shader.InitializeShader("background_vertex.glsl", "background_fragment.glsl");
	background.renderObject.IntializeRenderObject();
	background.renderObject.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, quad.data(), quad.size(),
	                                   sizeof(quad[0]));
	background.renderObject.AddAttribute(false, true, GL_FLOAT, 2, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void Update() {
	window.PollEvents();
	SDL_Event e;
	e = window.GetEvent();
	if (e.type == SDL_QUIT) { window.Quit(); }

	if (!laneObjects.empty() && laneObjects.front()->position.z <= -40) {
		laneObjects.erase(laneObjects.begin());
		GameObject *lane = new GameObject(&gameObjects);
		lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
		lane->position = glm::vec3(0, 0, 960);
		lane->AddComponent(new MoveToComponent(&lane->position));
		laneObjects.push_back(lane);
	}

	if (blockObjects.front()->position.z <= -10) {
		blockObjects.erase(blockObjects.begin());
		randBlock         = distBlock(gen);
		GameObject *block = new GameObject(&gameObjects);
		block->AddDrawComponent(new BlockComponent("stone.png"));
	}



	// Calculate deltaTime
	f64 currentFrameTime = SDL_GetTicks64();
	f64 deltaTime        = currentFrameTime - lastFrameTime;
	lastFrameTime        = currentFrameTime;

	for (auto gameObject : gameObjects) {
		if (gameObject != nullptr) { gameObject->Update(deltaTime); }
	}

	for (auto gameObject : laneObjects) {
		if (gameObject != nullptr) { gameObject->Update(deltaTime); }
	}

	for (auto gameObject : blockObjects) {
		if (gameObject != nullptr) { gameObject->Update(deltaTime); }
	}

	for (auto gameObject : coinObjects) {
		if (gameObject != nullptr) { gameObject->Update(deltaTime); }
	}

	camera.Update(glm::vec3{ 0, 7, -5 });
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6, 0.7, 0.8, 1.0);

	glDepthFunc(GL_LESS);

	glm::mat4 projectionView = camera.GetViewProjectionMatrix();

	for (auto gameObject : gameObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : laneObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : blockObjects) { gameObject->Draw(projectionView); }
	for (auto gameObject : coinObjects) { gameObject->Draw(projectionView); }

	glDepthFunc(GL_EQUAL);

	background.shader.UseProgram();
	glUniform2fv(0, 1, glm::value_ptr(glm::vec2(window.WINDOW_WIDTH, window.WINDOW_HEIGHT)));
	glUniform1f(1, SDL_GetTicks64());
	background.renderObject.Draw(DRAW_ARRAY, GL_TRIANGLE_STRIP, 4);

	window.SwapBuffers();
}

void StartVision() {
	cv::VideoCapture cap(0);

	cv::Mat img, backgroundImage;

	// 10 sec for the user to get out of the way
	std::cout << "Ga voor de camera weg";
	std::this_thread::sleep_for(1s);

	cap.read(backgroundImage);
	cv::imshow("background", backgroundImage);

	while (!window.WindowShouldClose()) {
		cap.read(img);

		cv::subtract(backgroundImage, img, img);
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(img, img, cv::Size(3, 3), 3, 3);
		cv::dilate(img, img, cv::Mat(), cv::Point(-1, -1), 9);
		cv::erode(img, img, cv::Mat(), cv::Point(-1, -1), 12);
		cv::threshold(img, img, 96, 255, cv::THRESH_BINARY);

		int width      = img.cols;
		int thirdWidth = width / 3;

		int height       = img.rows;
		int secondHeight = height / 2;

		cv::Mat left   = img(cv::Rect(0, 0, thirdWidth, img.rows));
		cv::Mat middle = img(cv::Rect(thirdWidth, 0, thirdWidth, img.rows));
		cv::Mat right  = img(cv::Rect(2 * thirdWidth, 0, thirdWidth, img.rows));

		auto topRect    = cv::Rect(0, 0, img.cols, secondHeight - 100);
		auto bottomRect = cv::Rect(0, height - 10, width, 10);

		cv::Mat top    = img(topRect);
		cv::Mat bottom = img(bottomRect);

		int leftSum   = cv::sum(left)[0];
		int middleSum = cv::sum(middle)[0];
		int rightSum  = cv::sum(right)[0];

		int topSum    = cv::sum(top)[0];
		int bottomSum = cv::sum(bottom)[0];

		std::string action;
		if (topSum < 10000) {
			action = "crouching";
		} else if (topSum > 10000 && bottomSum > 2000) {
			action = "doing nothing";
		} else if (bottomSum < 2000) {
			action = "jumping";
		}

		std::string position;
		if (leftSum > middleSum && leftSum > rightSum) {
			position = "Left";
		} else if (middleSum > leftSum && middleSum > rightSum) {
			position = "Middle";
		} else if (rightSum > leftSum && rightSum > middleSum) {
			position = "Right";
		} else {
			position = "Unknown";
		}

		std::cout << "User is in the " << position << " part of the image" << std::endl;
		std::cout << "User is currently " << action << std::endl;

		cv::rectangle(img, topRect, cv::Scalar(255, 0, 0), 2);
		cv::rectangle(img, bottomRect, cv::Scalar(255, 0, 0), 2);

		cv::imshow("Vision", img);
		cv::waitKey(1);
	}
}

void Close() {
	window.DestroyWindow();
	visionThread.join();
#ifdef DEBUG
	for (GameObject *gameObject : gameObjects) {
		for (Component *component : gameObject->GetComponents()) { delete component; }
		delete gameObject->GetBBComponent();
		delete gameObject->GetDrawComponent();
		delete gameObject;
	}
#endif
}
