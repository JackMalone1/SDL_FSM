#ifndef PLAYER_H
#define PLAYER_H
#include "Events.h"
#include "PlayerState.h"
#include "AnimatedSprite.h"

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	float x,y;
public:
	Player(const AnimatedSprite&);
	Player(AnimatedSprite*);
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void moveRight();
	void jump();
	void fall();

	std::pair<int,int> getPosition()
	{
		return std::pair<int, int>(x, y);
	}
private:
	void handleBoundaries();
};
#endif

