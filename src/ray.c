#include "../headers/header.h"

ray_t rays[NUM_RAYS];

static bool foundHorzWallHit, foundVertWallHit;
static float horzWallHitX, horzWallHitY, vertWallHitX, vertWallHitY;
static int horzWallContent, vertWallContent;

/**
 * horzIntersection - finds the horizontal intersection of the ray
 * @rayAngle: angle of the ray
 */

void horzIntersection(float rayAngle)
{
    float nextHorzTouchX, nextHorzTouchY, xintercept, yintercept, xstep, ystep;

    foundHorzWallHit = false;
    horzWallHitx = horzWallHitY = horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += rayFacingDown(rayAngle) ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= rayFacingUp(rayAngle) ? -1 : 1;
    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (rayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1;
    xstep *= (rayFacingRight(rayAngle) && xstep < 0) ? -1 : 1;
    nextHorzTouchX = xintercept;
    nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (rayFacingUp(rayAngle) ? -1 : 0);

        if (DetectCollision(xToCheck, yToCheck))
        {
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = getMapValue((int)floor(yToCheck / TILE_SIZE),
                                                                (int)floor(xToCheck / TILE_SIZE));
            foundHorzWallHit = true;
            break;
        }
        nextHorzTouchX += xstep;
        nextHorzTouchY += ystep;
    }
}

/**
 * vertIntersection - finds the vertical intersection of the ray
 * @rayAngle: angle of the ray
 */

void vertIntersection(float rayAngle)
{
    float nextVertouchX, nextVertouchY;
    float xintercept, yintercept, xstep, ystep;

    foundVertWallHit = false;
    vertWallHitX = vertWallHitY = vertWallContent = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += rayFacingRight(rayAngle) ? TILE_SIZE : 0;
    yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= rayFacingLeft(rayAngle) ? -1 : 1;
    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (rayFacingUp(rayAngle) && ystep > 0) ? -1 : 1;
    ystep *= (rayFacingDown(rayAngle) && ystep < 0) ? -1 : 1;
    nextVertouchX = xintercept;
    nextVertouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (isInsideMap(nextVertouchX, nextVertouchY))
    {
        float xToCheck = nextVertouchX + (rayFacingLeft(rayAngle) ? -1 : 0);
        float yToCheck = nextVertouchY;

        if (DetectCollision(xToCheck, yToCheck))
        {
            vertWallHitX = nextVertouchX;
            vertWallHitY = nextVertouchY;
            vertWallContent = getMapValue((int)floor(yToCheck / TILE_SIZE),
                                                                (int)floor(xToCheck / TILE_SIZE));
            foundVertWallHit = true;
            break;
        }
        nextVertouchX += xstep;
        nextVertouchY += ystep;
    }
}

/**
 * castRay - casts a ray
 * @rayAngle: angle of the ray
 * @stripId: id of the strip
 */

void castRay(float rayAngle, int stripId)
{
    float horzHitDistance, vertHitDistance;

    rayAngle = remainder(rayAngle, TWO_PI);
    if (rayAngle < 0)
        rayAngle = TWO_PI + rayAngle;

    horzIntersection(rayAngle);
    vertIntersection(rayAngle);
    horzHitDistance = foundHorzWallHit
                            ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
                            : FLT_MAX;
    vertHitDistance = foundVertWallHit
                            ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
                            : FLT_MAX;

    if (vertHitDistance < horzHitDistance)
    {
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitX = vertWallHitX;
        rays[stripId].wallHitY = vertWallHitY;
        rays[stripId].wallHitContent = vertWallContent;
        rays[stripId].wasHitVertical = true;
        rays[stripId].rayAngle = rayAngle;
    }
    else
    {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitX = horzWallHitX;
        rays[stripId].wallHitY = horzWallHitY;
        rays[stripId].wallHitContent = horzWallContent;
        rays[stripId].wasHitVertical = false;
        rays[stripId].rayAngle = rayAngle;
    }
}

/**
 * castAllRays - casts all rays
 */

void castAllRays(void)
{
    int col;

    for (col = 0; col < NUM_RAYS; col++)
    {
        float rayAngle = player.rotationAngle + 
                                        atan((col - NUM_RAYS / 2) / PROJ_PLANE);
        castRay(rayAngle, col);
    }
}

/**
 * renderRays - renders the rays
 */

void renderRays(void)
{
    int i;

    for (i = 0; i < NUM_RAYS; i +=50)
    {
        drawLine(
            player.x * MINIMAP_SCALE_FACTOR,
            player.y * MINIMAP_SCALE_FACTOR,
            rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
            rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
            0xFF0000FF
        )
    }
}