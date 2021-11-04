#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class IGraphic
{
public:
    IGraphic() = default;
    virtual void Draw() = 0;
};

class Graphic : public IGraphic
{
    int* x;
    int* y;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect* frame;
public:
    Graphic(int* t_x, int* t_y, SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_frame) : x(t_x), y(t_y), renderer(t_renderer), texture(t_texture), frame(t_frame){};
    ~Graphic(){};

    void Draw()
    {
        std::cout << "x: " << *x << ", y: " << *y;
        SDL_Rect renderRect = {*x, *y, frame->w, frame->h};
        SDL_RenderCopy(renderer, texture, frame, &renderRect);
    }
};

class GraphicProxy : public IGraphic
{
    int* x;
    int* y;
    SDL_Rect* frame;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Graphic* graphic;
    Graphic* getInstance(void)
    {
        if(!graphic)
        {
            graphic = new Graphic(x, y, renderer, texture, frame);
        }
        return graphic;
    }
public:
    GraphicProxy() {graphic = nullptr;};
    GraphicProxy(int* t_x, int* t_y, SDL_Renderer* t_renderer, SDL_Texture* t_texture, SDL_Rect* t_frame) : x(t_x), y(t_y), renderer(t_renderer), texture(t_texture), frame(t_frame){};
    ~GraphicProxy() {if(graphic) delete graphic;};
    void Draw()
    {
        getInstance()->Draw();
    };
};