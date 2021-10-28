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
    int x,y;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
public:
    Graphic(int t_x, int t_y, SDL_Renderer* t_renderer, SDL_Texture* t_texture) : x(t_x), y(t_y), renderer(t_renderer), texture(t_texture){};
    ~Graphic(){};

    void Draw()
    {
      
    }
};

class GraphicProxy : public IGraphic
{
    int x,y;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Graphic* graphic;
    Graphic* getInstance(void)
    {
        if(!graphic)
        {
            
        }
        return graphic;
    }
public:
    GraphicProxy() {graphic = nullptr;};
    ~GraphicProxy() {if(graphic) delete graphic;};
    void Draw()
    {
        getInstance()->Draw();
    };
};