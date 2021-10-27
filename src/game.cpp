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

		m_events.emplace("ACCEND_START", new AccendLadderStartCommand());
		m_events.emplace("ACCEND_STOP", new AccendLadderStopCommand());
		m_events.emplace("ATTACK", new AttackStartCommand());
		m_events.emplace("ATTACK_STOP", new AttackStopCommand());
		m_events.emplace("CLIMB_DOWN_START", new ClimbDownStartCommand());
		m_events.emplace("CLIMB_DOWN_STOP", new ClimbDownStopCommand());
		m_events.emplace("DESCEND", new DescendLadderCommand());
		m_events.emplace("DIED", new DiedCommand());
		m_events.emplace("GLIDE", new GlideCommand());
		m_events.emplace("IDLE", new IdleCommand());
		m_events.emplace("JUMP_ATTACK_START", new JumpAttackStartCommand());
		m_events.emplace("JUMP_ATTACK_STOP", new JumpAttackStopCommand());
		m_events.emplace("JUMP_START", new JumpStartCommand());
		m_events.emplace("JUMP_THROW_START", new JumpThrowStartCommand());
		m_events.emplace("REVIVE", new ReviveCommand());
		m_events.emplace("RUN_RIGHT_START", new RunRightStartCommand());
		m_events.emplace("RUN_RIGHT_STOP", new RunRightStopCommand());
		m_events.emplace("SLIDE", new SlideCommand());
		m_events.emplace("THROW_START", new ThrowStartCommand());
		m_events.emplace("THROW_STOP", new ThrowStopCommand());
		m_events.emplace("HIT_LADDER_BOTTOM", new HitLadderBottomCommand());
		m_events.emplace("HIT_LADDER_TOP", new HitLadderTopCommand());
		m_events.emplace("HIT_GROUND", new HitGroundCommand());
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
			if (e.key.keysym.sym == SDLK_d) {
				DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
				m_events.find("DIED")->second->execute(&input);
			}
			// Revieved Event
			else if (e.key.keysym.sym == SDLK_r) {
				DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
				m_events.find("REVIVE")->second->execute(&input);
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
				m_events.find("ATTACK")->second->execute(&input);
			}
			// Attack
			else if (e.key.keysym.sym == SDLK_z)
			{
				DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
				m_events.find("ATTACK")->second->execute(&input);
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
				m_events.find("THROW_START")->second->execute(&input);
			}
			// Throw Attack
			else if (e.key.keysym.sym == SDLK_x)
			{
				DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
				m_events.find("THROW_START")->second->execute(&input);
			}
			// Run Right
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Climb Up
			else if (e.key.keysym.sym == SDLK_UP)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
				m_events.find("ASCEND_START")->second->execute(&input);
			}
			// Climb Down
			else if (e.key.keysym.sym == SDLK_DOWN)
            {
				DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
				m_events.find("MOVE_DOWN_START")->second->execute(&input);
			}				// Hit Bottom of Ladder Event
			else if (e.key.keysym.sym == SDLK_c)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
                m_events.find("HIT_LADDER_BOTTOM")->second->execute(&input);
			}
			// Hit Top of Ladder Event
			else if (e.key.keysym.sym == SDLK_t)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
				m_events.find("HIT_LADDER_TOP")->second->execute(&input);
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
				m_events.find("JUMP_START")->second->execute(&input);
			}
            // Jump Event
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
                m_events.find("JUMP_START")->second->execute(&input);
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
				m_events.find("SLIDE")->second->execute(&input);
			}
			// Hit Ground Event
            else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				m_events.find("HIT_GROUND")->second->execute(&input);
			}
			// Jump Attack Event
			else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				m_events.find("HIT_GROUND")->second->execute(&input);
			}
			// Jump Throw Attack Event
			else if (e.key.keysym.sym == SDLK_h)
			{
				DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
				m_events.find("HIT_GROUND")->second->execute(&input);
			}
        }
		else if(e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_z 
				&& 
				e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Stop Attack
			else if(e.key.keysym.sym == SDLK_z)
			{
				DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
				m_events.find("ATTACK_STOP")->second->execute(&input);
			}
			// Run and Stop Throw Attack
			else if (e.key.keysym.sym == SDLK_x
				&&
				e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Stop Throw Attack
			else if (e.key.keysym.sym == SDLK_x)
			{
				DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
				m_events.find("THROW_STOP")->second->execute(&input);
			}
			// Stop Running Right
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Stop Slide
			else if (e.key.keysym.sym == SDLK_DOWN
				&&
				e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Stop Moving Up
			else if (e.key.keysym.sym == SDLK_UP)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
				m_events.find("MOVE_UP_STOP")->second->execute(&input);
			}
			// Stop Moving Down
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
				m_events.find("MOVE_DOWN_STOPx")->second->execute(&input);
			}
		}
		player->handleInput(input);

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
