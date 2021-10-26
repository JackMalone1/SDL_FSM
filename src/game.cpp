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

        SDL_Surface* textureSurface = IMG_Load(PLAYER_SPRITES);
        if(textureSurface == nullptr) std::cout << "Unable to load player images: " << IMG_GetError() << std::endl;
        player_texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
        if(player_texture == nullptr) std::cout << "Could not create texture: " << PLAYER_SPRITES << SDL_GetError();
        SDL_FreeSurface(textureSurface);
        player_animated_sprite = new AnimatedSprite(player_texture);
        player = new Player(player_animated_sprite);
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
        gpp::Events input;
        if(e.type == SDL_QUIT)
        {
            run = false;
        }

        if(e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_d)
			{

			}

			if (e.key.keysym.sym == SDLK_d) {
					DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
					input.setCurrent(gpp::Events::Event::DIED_EVENT);
			}
				// Revieved Event
			else if (e.key.keysym.sym == SDLK_r) {
				DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
				input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
			}
				// Running attack
			else if (e.key.keysym.sym == SDLK_z
				&&
				e.key.keysym.sym == SDLK_RIGHT
				||
				e.key.keysym.sym == SDLK_RIGHT
				&&
				e.key.keysym.sym == SDLK_z
				)
            {
				DEBUG_MSG("gpp::Events::Event::ATTACK_START");
				input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
			}
			// Attack
			else if (e.key.keysym.sym == SDLK_z)
			{
				DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
				input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
			}
			// Throw attack
            else if (e.key.keysym.sym == SDLK_d
				&&
				e.key.keysym.sym == SDLK_RIGHT
				||
				e.key.keysym.sym == SDLK_RIGHT
				&&
				e.key.keysym.sym == SDLK_x
				)
			{
				DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
				input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
			}
			// Throw Attack
			else if (e.key.keysym.sym == SDLK_x)
			{
				DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
				input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
			}
			// Run Right
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
			}
			// Climb Up
			else if (e.key.keysym.sym == SDLK_UP)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
				input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
			}
			// Climb Down
			else if (e.key.keysym.sym == SDLK_DOWN)
            {
				DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
				input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
			}				// Hit Bottom of Ladder Event
			else if (e.key.keysym.sym == SDLK_c)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
                input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
			}
			// Hit Top of Ladder Event
			else if (e.key.keysym.sym == SDLK_t)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
				input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
            }
			// Jump Run
			if (e.key.keysym.sym == SDLK_SPACE
				&&
				e.key.keysym.sym == SDLK_RIGHT
                ||
				e.key.keysym.sym == SDLK_RIGHT
				&&
				e.key.keysym.sym == SDLK_SPACE
				)
			{
				DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
				input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
			}
            // Jump Event
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
                input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
			}
			// Running Slide
			else if (e.key.keysym.sym == SDLK_DOWN
				&&
				e.key.keysym.sym == SDLK_RIGHT
				||
                e.key.keysym.sym == SDLK_RIGHT
				&&
				e.key.keysym.sym == SDLK_DOWN
				)
			{
				DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
				input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
			}
			// Hit Ground Event
            else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
			}

			// Jump Attack Event
			else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
			}

			// Jump Throw Attack Event
			else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
			}
        }
    }
}

void Game::update()
{
    player->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    player->getAnimatedSpriteFrame().render(0,0, renderer);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
