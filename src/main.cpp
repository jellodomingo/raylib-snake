#include <raylib.h>
#include <iostream>
#include "game.h"

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    Game game = Game(screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "Very bad snake");
    // SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    float dT = 0;
    game.StartGame();

    while (!WindowShouldClose())
    {
        game.UpdateDirection();

        dT += GetFrameTime();
        if (dT > 0.1 && !game.IsPaused())
        {
            dT = 0;
            game.UpdateGame();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        game.DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}