#include <stdio.h>
#include "../include/Player.h"
#include "../include/Events.h"
#include "../include/IdlePlayerState.h"


Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite), x(0), y(450.0f)
{
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Player::Player(AnimatedSprite* sprite) : m_animated_sprite(*sprite), x(0), y(450.0f)
{
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update() {
	m_animated_sprite.update();
	m_state->update(*this);
}

void Player::handleBoundaries()
{
	if(x > 1200)
	{
		x = 0;
	}
}

void Player::moveRight()
{
	x += 0.1f;
	handleBoundaries();
}

void Player::jump()
{
	y -=0.1f;
	if(y < 0.0f) y = 0.0f;
}

void Player::fall()
{
	y += 0.1f;
	if(y > 450.0f) y = 450.0f;
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }