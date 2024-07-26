#include "../headers/header.h"

bool GameRunning = false;
int TickLastFrame;
player_t player;

/**
 * setup_game - initialize player variables and load wall textures
 */

void setup_game(void)
{
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.width = 1;
    player.height = 30;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = PI / 2;
    player.walkSpeed = 100;
    player.turnSpeed = 45 * (PI / 180);
    WallTexturesready();
}

/**
 * update_game - update player position and rotation
 */

void update_game(void)
{
    float deltaTime;
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - TickLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
    {
        SDL_Delay(timeToWait);
    }
    deltaTime = (SDL_GetTicks() - TickLastFrame) / 1000.0;
    TickLastFrame = SDL_GetTicks();
    movePlayer(deltaTime);
    castAllRays();

    // printf("Player x: %f, Player y: %f\n", player.x, player.y);
}

/**
 * render - render the game
 */

void render_game(void)
{
    clearColorBuffer(0xFF000000);
    renderWall();
    renderPlayer();
    renderColorBuffer();
    renderMap();
    renderRays();
}

/**
 * Destroy - destroy the window
 */

void destroy_game(void)
{
    freeWallTextures();
    destroyWindow();
}

/**
 * main - main function
 * Return: 0
 */

int main(void)
{
    GameRunning = initializeWindow();
    setup_game();
    while (GameRunning)
    {
        handle_input();
        update_game();
        render_game();
    }
    destroy_game();
    return (0);
}