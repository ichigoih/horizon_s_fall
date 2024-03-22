#pragma once

#include <SDL2/SDL.h>

#include "ECS.hpp"


class TileComponent : public Component {
    public:
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;
        Vector2D position;

        TileComponent() = default;

        ~TileComponent() {
            SDL_DestroyTexture(texture);
        }

        TileComponent(int srcX, int srcY, int xpos, int ypos, int tSize, int tScale, const char* filePath) {
            texture = TextureManager::LoadTexture(filePath);

            position.x = xpos;
            position.y = ypos;

            srcRect.x = srcX;
            srcRect.y = srcY;
            srcRect.w = srcRect.h = tSize;

            destRect.x = xpos;
            destRect.y = ypos;
            destRect.w = destRect.h = tSize * tScale;
        }

        void update() override {
            destRect.x = position.x - Game::camera.x;
            destRect.y = position.y - Game::camera.y;
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        }
};