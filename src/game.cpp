#include "../include/game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialised. Error: " << SDL_GetError();
        running = false;
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
		Factory factory;
		m_events.emplace("ACCEND_START", factory.getObject<AccendLadderStartCommand>());
		m_events.emplace("ACCEND_STOP", factory.getObject<AccendLadderStopCommand>());
		m_events.emplace("MOVE_UP_START",factory.getObject<MoveUpStartCommand>());
		m_events.emplace("MOVE_UP_STOP", factory.getObject<MoveUpStopCommand>());
		m_events.emplace("MOVE_DOWN_START",factory.getObject<MoveDownStartCommand>());
		m_events.emplace("MOVE_DOWN_STOP", factory.getObject<MoveDownStopCommand>());
		m_events.emplace("ATTACK", factory.getObject<AttackStartCommand>());
		m_events.emplace("ATTACK_STOP", factory.getObject<AttackStopCommand>());
		m_events.emplace("CLIMB_DOWN_START", factory.getObject<ClimbDownStartCommand>());
		m_events.emplace("CLIMB_DOWN_STOP", factory.getObject<ClimbDownStopCommand>());
		m_events.emplace("DESCEND", factory.getObject<DescendLadderCommand>());
		m_events.emplace("DIED", factory.getObject<DiedCommand>());
		m_events.emplace("GLIDE", factory.getObject<GlideCommand>());
		m_events.emplace("IDLE", factory.getObject<IdleCommand>());
		m_events.emplace("JUMP_ATTACK_START", factory.getObject<JumpAttackStartCommand>());
		m_events.emplace("JUMP_ATTACK_STOP", factory.getObject<JumpAttackStopCommand>());
		m_events.emplace("JUMP_START", factory.getObject<JumpStartCommand>());
		m_events.emplace("JUMP_THROW_START", factory.getObject<JumpThrowStartCommand>());
		m_events.emplace("REVIVE", factory.getObject<ReviveCommand>());
		m_events.emplace("RUN_RIGHT_START", factory.getObject<RunRightStartCommand>());
		m_events.emplace("RUN_RIGHT_STOP", factory.getObject<RunRightStopCommand>());
		m_events.emplace("SLIDE", factory.getObject<SlideCommand>());
		m_events.emplace("THROW_START", factory.getObject<ThrowStartCommand>());
		m_events.emplace("THROW_STOP", factory.getObject<ThrowStopCommand>());
		m_events.emplace("HIT_LADDER_BOTTOM", factory.getObject<HitLadderBottomCommand>());
		m_events.emplace("HIT_LADDER_TOP", factory.getObject<HitLadderTopCommand>());
		m_events.emplace("HIT_GROUND", factory.getObject<HitGroundCommand>());
    }
}

bool Game::isRunning()
{
    return running;
}

void Game::run()
{
	while(isRunning())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&e) != 0)
    {
        gpp::Events input;
        if(e.type == SDL_QUIT)
        {
            running = false;
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
			else if (e.key.keysym.sym == SDLK_w)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
				m_events.find("MOVE_UP_START")->second->execute(&input);
			}
			// Climb Down
			else if (e.key.keysym.sym == SDLK_s)
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
				m_events.find("RUN_RIGHT_STOP")->second->execute(&input);
			}
			// Stop Slide
			else if (e.key.keysym.sym == SDLK_DOWN&&
					e.key.keysym.sym == SDLK_RIGHT)
			{
				DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
				m_events.find("RUN_RIGHT_START")->second->execute(&input);
			}
			// Stop Moving Up
			else if (e.key.keysym.sym == SDLK_w)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
				m_events.find("MOVE_UP_STOP")->second->execute(&input);
			}
			// Stop Moving Down
			else if (e.key.keysym.sym == SDLK_s)
			{
				DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
				m_events.find("MOVE_DOWN_STOP")->second->execute(&input);
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
	std::pair<int, int> position = player->getPosition();
    player->getAnimatedSpriteFrame().render(position.first,position.second, renderer);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
