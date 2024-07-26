#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include "upng.h"

//constants
#define PI 3.14159265
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.25
#define SCREEN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS SCREEN_WIDTH
#define PROJ_PLANE (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2)
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define NUM_TEXTURES 8
typedef uint32_t uint32_t color_t;

void handle_input(void);
extern bool GameRunning;
// Function-variables-structs for draw
bool initializeWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void render_game(void);
void renderColorBuffer(void);
void drawRect(int x, int y, int width, int height, color_t color);
void drawPixel(int x, int y, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);
// Function-variables-structs for map
bool DetectCollision(float x, float y);
void renderMap(void);
bool isInsideMap(float x, float y);
int getMapValue(int row, int col);
// Function-variables-structs for player
/**
 * struct player_s - player struct
 * @x: x coordinate of player
 * @y: y coordinate of player
 * @width: width of player
 * @height: height of player
 * @turnDirection: -1 for left, 1 for right, 0 for none
 * @walkDirection: -1 for back, 1 for front, 0 for none
 * @rotationAngle: angle of player
 * @walkSpeed: speed of player
 * @turnSpeed: speed of player turning
 */
typedef struct player_s
{
    float x;
    float y;
    float width;
    float height;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;
extern player_t player;
void movePlayer(float DeltaTime);
void renderPlayer(void);
// Function-variables-structs for raycasting
/**
 * struct ray_s - ray struct
 * @rayAngle: angle of ray
 * @wallHitX: x coordinate of wall hit
 * @wallHitY: y coordinate of wall hit
 * @distance: distance to wall hit
 * @wasHitVertical: 1 if hit vertical wall, 0 if hit horizontal wall
 * @wallHitContent: content of wall hit
 */
typedef struct ray_s
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int wallHitContent;
} ray_t;
extern ray_t rays[NUM_RAYS];

void castAllRays(void);
void renderRays(void);
bool isRayFacingDown(float angle);
bool isRayFacingUp(float angle);
bool isRayFacingRight(float angle);
bool isRayFacingLeft(float angle);
void castRay(float rayAngle, int stripId);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void horzIntersection(float rayAngle);
void vertIntersection(float rayAngle);
// Function-variables-structs for textures

/**
 * struct texture_s - struct for the texture
 * @width: width of texture
 * @height: height of texture
 * @texture_buffer: buffer of texture
 * @upngTexture: pointer to upng texture
 */
typedef struct texture_s
{
    int width;
    int height;
    color_t *texture_buffer;
    upng_t *upngTexture;
} texture_t;
texture_t wallTextures[NUM_TEXTURES];
void WallTexturesready(void);
void freeWallTextures(void);
// Function-variables-structs for walls
void renderWall(void);
#endif