#define SDL_MAIN_HANDLED
#include "control_component.h"
#include "window.h"
#include "camera.h"
#include "game_object.h"
#include "model_component.h"
#include "move_to_component.h"
#include "spin_component.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

Window window;
ControlComponent controller;
Camera camera;
std::vector<GameObject*> gameObjects;
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

void Init(){
	window.InitializeWindow("Lsd Run", 1280, 720);
	camera.InitializeCamera(glm::vec3{0,5,0});

	for (int i = 0; i < 100; i++)
	{
		GameObject *lane = new GameObject();
		lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
		lane->position = glm::vec3(0, 0, i * 10);
		lane->AddComponent(new MoveToComponent(&lane->position));
		//lane->AddComponent(new SpinComponent(0.0005f));
		gameObjects.push_back(lane);
	}

	GameObject* player = new GameObject();
	player->AddDrawComponent(new ModelComponent("player/player.gltf", "player.png"));
	player->position = glm::vec3(0.0, 1.0, 0.0);
	gameObjects.push_back(player);	

	GameObject* coin = new GameObject();
	coin->AddDrawComponent(new ModelComponent("coin/coin.gltf", "coin.png"));
	coin->AddComponent(new SpinComponent(0.0005f));
	coin->position = glm::vec3(0.0, 2.0, 0.0);
	gameObjects.push_back(coin);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	cv::VideoCapture cap(0);
	cv::Mat img;
	
	while (true) {
		cap.read(img);
		imshow("Image", img);
		cv::waitKey(1);
	}
}

void Update(){
	window.PollEvents();
	SDL_Event e;
	e = window.GetEvent();
	if(e.type == SDL_QUIT){
		window.Quit();
	}

	//Calculate deltaTime
    f64 currentFrameTime = SDL_GetTicks64();
	f64 deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

	for(auto gameObject : gameObjects){
        gameObject->Update(deltaTime);
    }

	camera.Update(glm::vec3{0,5,0});
	
}

void Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6, 0.7, 0.8, 1.0);

	glm::mat4 projectionView = camera.GetViewProjectionMatrix();
    for(auto gameObject : gameObjects){
        gameObject->Draw(projectionView);
    }

	window.SwapBuffers();
}

void Close() { window.DestroyWindow(); }
