#include "tile.h"
#include <raylib.h>
#include <string> // for string and to_string()

Tile::Tile() = default;

Tile::Tile(Vector2 origin, int lifespan, TileState state)
{
    this->origin = origin;
    this->lifespan = lifespan;
    this->state = state;
};

void Tile::UpdateToSnakeTile(int lifespan)
{
    this->state = snake;
    this->lifespan = lifespan;
};

void Tile::UpdateToItemTile()
{
    this->state = item;
    this->lifespan = -1;
}

TileState Tile::GetTileState()
{
    return state;
}

void Tile::Update()
{
    if (lifespan > 0)
        --lifespan;

    if (lifespan >= 1)
    {
        state = snake;
    }
    else if (lifespan == 0)
    {
        state = empty;
    }
    else if (lifespan == -1)
    {
        state = item;
    }
};

void Tile::Draw(int tileSize)
{

    switch (state)
    {
    case empty:
        // DrawText("0", origin.x, origin.y, tileSize, WHITE);
        break;
    case snake:
        // DrawText(std::to_string(lifespan).c_str(), origin.x, origin.y, tileSize, RED);
        DrawRectangleV(Vector2{origin.x, origin.y}, Vector2{tileSize, tileSize}, WHITE);
        break;
    case item:
        DrawRectangleV(Vector2{origin.x, origin.y}, Vector2{tileSize, tileSize}, RED);
        break;
    }
};