#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "Command.h"
#include "Player.h"
#include "Defines.h"
#include <map>
#include "Factory.h"

class Game
{
public:
    Game();
    bool isRunning();
    void handleEvents();
    void update();
    void render();
    void run();
    void cleanup();
private:
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 900;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* m_font = nullptr;
    SDL_Event e;
    SDL_Texture* m_totalsText;
    SDL_Rect m_totalsRect;
    bool running = true;
    Player* player;
    AnimatedSprite* player_animated_sprite;
    SDL_Texture* player_texture;
    std::map<std::string, Command*> m_events; 
};