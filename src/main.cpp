#define SDL_MAIN_HANDLED
#include "window.h"
#include "camera.h"
#include "game_object.h"
#include "model_component.h"
#include <iostream>

Window window;
Camera camera;
std::vector<GameObject*> gameObjects;
f64 lastFrameTime = 0;

void Init();
void Update();
void Render();
void Close();

int main(int argc, char *argv[]) {
	Init();
	while(!window.WindowShouldClose()){
		Update();
		Render();

	}
	Close();
	return 0;
}


void Init(){
	window.InitializeWindow("Lsd Run", 1280, 720);
	camera.InitializeCamera(glm::vec3{0,0,0});

	GameObject* lane = new GameObject();
	lane->AddDrawComponent(new ModelComponent("lane/lane.gltf", "lane_texture.png"));
	gameObjects.push_back(lane);

	GameObject* coin = new GameObject();
	coin->AddDrawComponent(new ModelComponent("coin/coin.gltf", "coin.png"));
	coin->position = glm::vec3(0.0, 2.0, 0.0);
	gameObjects.push_back(coin);

	glEnable(GL_DEPTH_TEST);
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

	camera.Update(glm::vec3{0,0,0});
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

void Close(){
	window.DestroyWindow();
}