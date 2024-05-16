#pragma once

#include <iostream>
#include "dependencies.h"
#include "SDL.h"

class GameManager{
    f64 startTime;
    f64 elapsedTime;
    u32 score;
    bool isStarted;

    public:
        GameManager();
        ~GameManager();
        void start();
        void stop();
        bool getIsStarted();
        void addScore(int score = 1);
        void showElapsedTime();
};