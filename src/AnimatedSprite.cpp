#include "../include/AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() :
    m_currentFrame(0),
    m_time(0.5f),
    m_loop(true),
    m_playCount(0),
    m_maxPlays(0),
    m_played(0)
{
    DEBUG_MSG("AnimatedSprite()");
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t_texture) : AnimatedSprite()
{
    DEBUG_MSG("AnimatedSprite(SDL_Texture*)");
    m_texture = t_texture;
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t_texture, SDL_Rect t_rect) : AnimatedSprite(m_texture)
{
    m_frames.push_back(t_rect);
}

AnimatedSprite::~AnimatedSprite()
{
    DEBUG_MSG("~AnimatedSprite()");
}

const Timer& AnimatedSprite::getTimer()
{
    return m_timer;
}

uint32_t AnimatedSprite::getTime()
{
    return m_time;
}

void AnimatedSprite::setTime(uint32_t t_time)
{
    m_time = t_time;
}

const std::vector<SDL_Rect>& AnimatedSprite::getFrames()
{
    return m_frames;
}

void AnimatedSprite::clearFrames()
{
    m_currentFrame = 0;
    m_played = false;
    if(!m_frames.empty())
    {
        m_frames.clear();
    }
}

const SDL_Rect& AnimatedSprite::getFrame(int n)
{
    return m_frames.at(n);
}

void AnimatedSprite::addFrame(const SDL_Rect& t_frame)
{
    m_frames.push_back(t_frame);
}

const int AnimatedSprite::getCurrentFrame()
{
    return m_currentFrame;
}

void AnimatedSprite::setLooped(bool t_loop)
{
    m_loop = t_loop;
}

const bool AnimatedSprite::getLooped()
{
    return m_loop;
}

void AnimatedSprite::setPlayed(bool t_played)
{
    m_played = t_played;
}

const bool AnimatedSprite::getPlayed()
{
    return m_played;
}

void AnimatedSprite::update()
{
    if(m_played && !m_loop)
    {
        m_currentFrame = m_frames.size() - 1;
    }
    else
    {
        if(m_timer.getTicksAsSeconds() > m_time)
        {
            if(m_frames.size() > m_currentFrame + 1)
            {
                m_currentFrame++;
            }
            else
            {
                m_currentFrame = 0;
                m_played = true;
            }
            m_timer.reset();
        }
    }
}

SDL_Texture* AnimatedSprite::getTexture()
{
    return m_texture;
}

void AnimatedSprite::setTextureRect(SDL_Rect t_rect)
{
    m_frame = t_rect;
}

void AnimatedSprite::setTextureDimensions(int t_width, int t_height)
{
    m_textureWidth = t_width;
    m_textureHeight = t_height;
}

void AnimatedSprite::render(int t_x, int t_y, SDL_Renderer* t_renderer)
{
    SDL_Rect renderRect = {t_x, t_y, m_frame.w, m_frame.h};
    SDL_RenderCopy(t_renderer, m_texture, &m_frame, &renderRect);
}