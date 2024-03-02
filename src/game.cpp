#include "game.h"
#include "tile.h"
#include <raylib.h>

Game::Game() = default;

Game::Game(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->tileSize = int(screenHeight * 0.05f);
    this->boardWidth = screenWidth / tileSize;
    this->boardHeight = screenHeight / tileSize;
    this->snakeHeadX = 5;
    this->snakeHeadY = 5;
    this->snakeLength = 2;
    this->currentDirection = NORTH;
    this->pause = false;
    this->gameOver = false;
    this->canMove = true;
    Game::CreateBoard(boardWidth, boardHeight);
}

void Game::CreateBoard(int rows, int cols)
{
    board = new Tile **[rows];

    for (int x = 0; x < rows; ++x)
    {
        board[x] = new Tile *[cols];
    }
}

void Game::DeleteBoard(int rows)
{
    for (int x = 0; x < rows; ++x)
    {
        delete[] board[x];
    }

    delete[] board;
}

void Game::ChangeDirection(Direction direction)
{
    currentDirection = direction;
}

void Game::StartGame()
{

    for (int x = 0; x < boardWidth; ++x)
    {
        for (int y = 0; y < boardHeight; ++y)
        {
            board[x][y] = new Tile(Vector2{x * tileSize, y * tileSize}, 0, empty);
        }
    }

    // Init Fruit
    (*board[3][2]).UpdateToItemTile();
}

void Game::CreateNewItem()
{
    // very bad way in creating a new item
    // edge case: what if there is one tile left and it takes bizillion tries to get the right combo
    int randX = GetRandomValue(0, 9);
    int randY = GetRandomValue(0, 9);

    while ((*board[randX][randY]).GetTileState() == snake)
    {
        randX = GetRandomValue(0, 9);
        randY = GetRandomValue(0, 9);
    }

    (*board[randX][randY]).UpdateToItemTile();
}

void Game::UpdateDirection()
{
    if (canMove)
    {
        if (IsKeyDown(KEY_W))
        {
            if (currentDirection != SOUTH)
                Game::ChangeDirection(NORTH);
        }
        else if (IsKeyDown(KEY_S))
        {
            if (currentDirection != NORTH)
                Game::ChangeDirection(SOUTH);
        }
        else if (IsKeyDown(KEY_D))
        {
            if (currentDirection != WEST)
                Game::ChangeDirection(EAST);
        }
        else if (IsKeyDown(KEY_A))
        {
            if (currentDirection != EAST)
                Game::ChangeDirection(WEST);
        }
        canMove = false;
    }
}

void Game::UpdateGame()
{
    // Move Snake
    switch (currentDirection)
    {
    case NORTH:
        --snakeHeadY;
        if (snakeHeadY < 0)
            snakeHeadY = boardHeight - 1;
        break;
    case WEST:
        --snakeHeadX;
        if (snakeHeadX < 0)
            snakeHeadX = boardWidth - 1;
        break;
    case EAST:
        ++snakeHeadX;
        if (snakeHeadX >= boardWidth)
            snakeHeadX = 0;
        break;
    case SOUTH:
        ++snakeHeadY;
        if (snakeHeadY >= boardHeight)
            snakeHeadY = 0;
        break;

    default:
        break;
    }
    canMove = true;

    // Check next tile

    // If next tile is a snake body
    switch ((*board[snakeHeadX][snakeHeadY]).GetTileState())
    {
    case empty:
        // MOVE AHEAD
        (*board[snakeHeadX][snakeHeadY]).UpdateToSnakeTile(snakeLength);
        break;
    case snake:
        // GAME OVER
        pause = true;
        gameOver = true;
        break;
    case item:
        // INCREASE SNAKE LENGTH
        ++snakeLength;
        (*board[snakeHeadX][snakeHeadY]).UpdateToSnakeTile(snakeLength);
        Game::CreateNewItem();
        break;
    }

    // update tile state
    for (int x = 0; x < boardWidth; x++)
    {
        for (int y = 0; y < boardHeight; ++y)
        {
            (*board[x][y]).Update();
        }
    }
}

void Game::DrawGame()
{

    for (int x = 0; x < boardWidth; x++)
    {
        DrawLineV(Vector2{x * tileSize, 0}, Vector2{x * tileSize, screenHeight}, WHITE);
        for (int y = 0; y < boardHeight; ++y)
        {
            DrawLineV(Vector2{0, y * tileSize}, Vector2{screenWidth, y * tileSize}, WHITE);

            (*board[x][y]).Draw(tileSize);
        }
    }

    // void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);
    if (!gameOver)
    {
        DrawText(TextFormat("%i", snakeLength - 2), screenWidth / 2, screenHeight / 6, 120, WHITE);
    }
    else
    {
        DrawText("GAME OVER", screenWidth / 6, screenHeight / 6, 70, RED);
        DrawText("FINAL SCORE", screenWidth / 6, 2 * screenHeight / 6, 70, RED);
        DrawText(TextFormat("%i", snakeLength - 2), screenWidth / 2, 3 * screenHeight / 6, 120, RED);
    }
}

void Game::PauseGame()
{
    pause = true;
}

void Game::UnpauseGame()
{
    pause = false;
}

bool Game::IsPaused()
{
    return pause;
}