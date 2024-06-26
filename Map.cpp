#include <fstream>

#include "Map.hpp"
#include "Game.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"


extern Manager manager;


Map::Map(std::string texID, int mScale, int tSize, int mSizeX, int mSizeY)
    : textureID(texID), mapScale(mScale), tileSize(tSize), sizeX(mSizeX), sizeY(mSizeY) {
        scaledSize = mScale * tSize;
    }


Map::~Map() {    }


void Map::LoadMap(std::string path) {
    char tile;
    std::ifstream mapFile(path);

    int srcX, srcY;

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            srcY = atoi(&tile) * tileSize;

            mapFile.get(tile);
            srcX = atoi(&tile) * tileSize;

            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);

            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);

            if (tile == '1') {
                auto& tCol(manager.addEntity());
                tCol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tCol.addGroup(Game::groupColliders);
            }

            mapFile.ignore();
        }
    }
    
    mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);

    if (srcX == 1 * tileSize  && srcY == 2 * tileSize)
        tile.addGroup(Game::groupGrasses);
    else tile.addGroup(Game::groupMap);
}
