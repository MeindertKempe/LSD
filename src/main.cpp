#define SDL_MAIN_HANDLED
#include "window.h"
#include "camera.h"
#include "model.h"
#include <iostream>

Window window;
Camera camera;

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
}

void Update(){
	window.PollEvents();
	SDL_Event e;
	e = window.GetEvent();
	if(e.type == SDL_QUIT){
		window.Quit();
	}

	camera.Update(glm::vec3{0,0,0});
}

void Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.6, 0.7, 0.8, 1.0);




	window.SwapBuffers();
}

void Close(){
	window.DestroyWindow();


}