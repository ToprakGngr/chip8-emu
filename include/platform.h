#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

class Platform {
public:
    // start window and renderer
    Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    
    // destroy
    ~Platform();

    void Update(void const* buffer, int pitch);
    bool ProcessInput(uint8_t* keys);

private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
};
