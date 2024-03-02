#pragma once
#include "tile.h"

enum Direction
{
    NORTH = 0,
    WEST = 1,
    EAST = 2,
    SOUTH = 3,
};

class Game
{
private:
    int screenWidth;
    int screenHeight;
    int tileSize;
    int boardWidth;
    int boardHeight;
    int snakeHeadX;
    int snakeHeadY;
    int snakeLength;
    bool pause;
    bool gameOver;
    bool canMove;
    Tile ***board;
    Direction currentDirection;

public:
    Game();
    Game(int screenWidth, int screenHeight);
    void CreateBoard(int rows, int cols);
    void DeleteBoard(int rows);
    void ChangeDirection(Direction direction);
    void UpdateDirection();
    void StartGame();
    void CreateNewItem();
    void UpdateGame();
    void DrawGame();
    void PauseGame();
    void UnpauseGame();
    bool IsPaused();
};