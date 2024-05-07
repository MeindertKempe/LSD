#define SDL_MAIN_HANDLED
#include "window.h"
#include "control_component.h"

Window window;
ControlComponent controller;

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
	
}

void Update(){
	window.PollEvents();
	SDL_Event e;
	e = window.GetEvent();
	if(e.type == SDL_QUIT){
		window.Quit();
	}
	controller.CheckKeyPress(e);
}

void Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.6, 0.7, 0.8, 1.0);

	window.SwapBuffers();
}

void Close(){
	window.DestroyWindow();


}
