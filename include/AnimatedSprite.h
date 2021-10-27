#pragma once
#include <SDL2/SDL.h>
#include "Timer.h"
#include <vector>
#include "Debug.h"
class AnimatedSprite
{
public:
	AnimatedSprite();
	AnimatedSprite(SDL_Texture*);
	AnimatedSprite(SDL_Texture*, SDL_Rect);
	~AnimatedSprite();

    const Timer& getTimer();
    float getTime();
    const std::vector<SDL_Rect>& getFrames();
    void clearFrames();
    const SDL_Rect& getFrame(int);
    void addFrame(const SDL_Rect&);
    const int getCurrentFrame();
    void setLooped(bool);
    const bool getLooped();
    void setPlayed(bool);
    const bool getPlayed();
    void setTime(float);
    void update();

    void setTextureRect(SDL_Rect);
    SDL_Texture* getTexture();
    void setTextureDimensions(int, int);
    void render(int, int, SDL_Renderer*);
private:
    Timer m_timer;
    float m_time;
    std::vector<SDL_Rect> m_frames;
    unsigned int m_currentFrame;
    bool m_loop;
    unsigned int m_playCount;
    unsigned int m_maxPlays;
    bool m_played;

    SDL_Texture* m_texture;
    SDL_Rect m_frame;
    int m_textureWidth;
    int m_textureHeight;
};
