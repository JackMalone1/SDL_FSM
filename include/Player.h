#pragma once
#include "AnimatedSprite.h"
#include "PlayerState.h"
#include <SDL2/SDL.h>
class Player
{
private:
    AnimatedSprite m_animatedSprite;
    PlayerState* m_state;
public:
    Player(const AnimatedSprite& t_animatedSprite);
	virtual void handleInput(SDL_Event& e);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite& t_animatedSprite);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState* t_state);
};