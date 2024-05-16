#include "game_manager.h"

GameManager::GameManager(): score(0), isStarted(false){
}

void GameManager::start(){
    startTime = SDL_GetTicks64();
    isStarted = true;
}

void GameManager::stop(){
    score = 0;
    isStarted = false;
    f64 currentTime = SDL_GetTicks();
    elapsedTime = currentTime - startTime;
    showElapsedTime();
}

GameManager::~GameManager(){
    score = 0;
}

bool GameManager::getIsStarted(){
    return isStarted;
} 

void GameManager::showElapsedTime(){
    u32 elapsedTimeInSeconds = elapsedTime / 1000;
    u32 elapsedMinute = 0;
    while(elapsedTimeInSeconds > 60) {
        elapsedMinute++;
        elapsedTimeInSeconds -= 60;
    }
    std::cout << "elapsedTime: " << elapsedMinute << "min - " << elapsedTimeInSeconds << "sec";
}

