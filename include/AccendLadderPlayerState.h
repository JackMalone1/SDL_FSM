#ifndef ACCEND_LADDER_PLAYER_STATE_H
#define ACCEND_LADDER_PLAYER_STATE_H

#include "Player.h"
#include "PlayerState.h"

class AccendLadderPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
};

#endif
