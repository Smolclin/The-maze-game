#include "../headers/header.h"

/**
 * movePlayer - moves the player
 * @DeltaTime: time elpsed
 */

void movePlayer(float DeltaTime)
{
    float moveSteps, newPlayerY, newPlayerX;

    player.rotationAngle += player.turnDirection * player.turnSpeed * DeltaTime;
    moveSteps = player.walkDirection * player.walkSpeed * DeltaTime;

    newPlayerX = player.x + cos(player.rotationAngle) * moveSteps;
    newPlayerY = player.y + sin(player.rotationAngle) * moveSteps;

    if (!DetectCollision(newPlayerX, newPlayerY))
    {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }
}

/**
 * renderPlayer - renders the player
 */

void renderPlayer(void)
{
    SDL_Rect playerRect = {
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        player.width * MINIMAP_SCALE_FACTOR,
        player.height * MINIMAP_SCALE_FACTOR,
        0xFFFFFFFF
    };
}