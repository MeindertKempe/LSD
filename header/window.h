#pragma once
#include "dependencies.h"
#include "glad/glad.h"
#include "SDL.h"
#include <string>

class Window{
    private:
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    SDL_Window* window = NULL;
    SDL_GLContext glContext = NULL;
    SDL_Event e;
    bool quit = false;

    public:
    Window();
    ~Window();
    void InitializeWindow(std::string title, int width, int height);
    void DestroyWindow();
    bool WindowShouldClose();
    void Quit();
    void PollEvents();
    void SwapBuffers();
    void Update(bool centeredMouse);

    SDL_Event GetEvent();
};