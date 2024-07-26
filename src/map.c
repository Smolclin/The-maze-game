#include "../headers/header.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6},
	{6, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 6, 0, 7, 7, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 1, 0, 0, 0, 0, 7, 7, 0, 6},
	{6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
	{6, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
	{6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

/**
 * DetectCollision - Detects if there is a wall at the given x and y coordinates
 * @x: x coordinate
 * @y: y coordinate
 * Return: true if there is a wall, false otherwise
 */

bool DetectCollision(float x, float y)
{
    int mapGridIndexX, mapGridIndexY;

    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE ||
                    y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)    {
        return true;

    mapGridIndexX = floor(x / TILE_SIZE);
    mapGridIndexY = floor(y / TILE_SIZE);
    return (map[mapGridIndexY][mapGridIndexX] != 0);
}

/**
 * isInsideMap - checks if the given x and y coordinates are inside the map
 * @x: x coordinate
 * @y: y coordinate
 * Return: true if the coordinates are inside the map, false otherwise
 */

bool isInsideMap(float x, float y)
{
    return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE &&
                            y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

/**
 * getMapValue - gets the value of the map at the given row and column
 * @row: row
 * @col: column
 * Return: value of the map at the given row and column
 */

int getMapValue(int row, int col)
{
    return map[row][col];
}

/**
 * renderMap - renders the map
 */

void renderMap(void)

{
    int i, j, tileX, tileY;
    color_t tileColor;

    for (i = 0; i < MAP_NUM_ROWS; i++) {
        for (j = 0; j < MAP_NUM_COLS; j++) {
            tileX = j * TILE_SIZE;
            tileY = i * TILE_SIZE;
            tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;
            drawRect(
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor
            );
        }
    }
}