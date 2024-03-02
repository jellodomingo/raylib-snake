#pragma once
#include <raylib.h>

enum TileState
{
    empty = 0,
    snake = 1,
    item = 2,
};

class Tile
{
private:
    Vector2 origin;
    int lifespan;
    TileState state;

public:
    Tile();
    Tile(Vector2 origin, int lifespan, TileState state);
    void UpdateToSnakeTile(int lifespan);
    void UpdateToItemTile();
    void Update();
    TileState GetTileState();
    void Draw(int tileSize);
};