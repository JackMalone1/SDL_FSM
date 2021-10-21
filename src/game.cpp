#include "../include/game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialised. Error: " << SDL_GetError();
        run = false;
    }
    else
    {
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        window = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        m_font = TTF_OpenFont("assets/fonts/MONOFONT.ttf", 24);
        if(m_font == nullptr) std::cout << "font could not be loaded" << std::endl;
        if(window == nullptr)
        {
            std::cout << "Failed to create window. Error: " << SDL_GetError();
        }
    }
}

bool Game::isRunning()
{
    return run;
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            run = false;
        }
        int x,y;
        Uint32 mouseButtons;

        SDL_PumpEvents();

        mouseButtons = SDL_GetMouseState(&x, &y);

        if ((mouseButtons & SDL_BUTTON_LMASK) != 0) {
            for(Button* button : buttons)
            {

            }
        }
    }
}

void Game::update()
{
    for(Button* button : buttons)
    {

    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    for(Button* button : buttons)
    {

    }
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::displayBricks()
{
    for(auto& brick : m_bricks)
    {

    }
}

void Game::updateTotals()
{
    for(auto& button : buttons)
    {

    }
}

void Game::displayTotals()
{
    commands.execute();
    std::string s = "Built: ";

    if(m_bricks.size() > 0)
    {
        for(auto& brick : m_bricks)
        {
            s += brick->getType() + "\n";
        }

        m_bricks.clear();
    }
    
    std::cout << s;
}