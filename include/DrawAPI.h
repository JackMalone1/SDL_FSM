#pragma once
#include "Proxy.h"
class DrawAPI
{
public:
    virtual void Draw() = 0;
};

class SDLDraw : public DrawAPI
{

    GraphicProxy m_proxy;
public:
    SDLDraw(int* t_x, int* t_y, SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_frame) : m_proxy(t_x, t_y, t_renderer, t_texture, t_frame)
    {

    }
    void Draw()
    {
        m_proxy.Draw();
    }
};