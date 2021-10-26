#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "Command.h"
#include "Player.h"
#include "Defines.h"

class Game
{
public:
    Game();
    bool isRunning();
    void handleEvents();
    void update();
    void render();
    void cleanup();
private:
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 900;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* m_font = nullptr;
    SDL_Event e;
    MacroCommand commands;
    SDL_Texture* m_totalsText;
    SDL_Rect m_totalsRect;
    bool run = true;
    Player* player;
    AnimatedSprite* player_animated_sprite;
    SDL_Texture* player_texture;
private:

};