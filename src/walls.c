#include "../include/walls.h"

/**
 * changeColorIntensity - Changes the intensity of the color
 * @factor: The factor to change the intensity
 * @color: The color to change the intensity
 * 
 */

void changeColorIntensity(float factor, SDL_Color *color)
{
    SDL_color a = (*color & 0xFF000000);
    SDL_color r = (*color & 0x00FF0000) * factor;
    SDL_color g = (*color & 0x0000FF00) * factor;
    SDL_color b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * renderFloor - Renders the floor
 * @WallBottomPixel: wall bottom pixel
 * @texelColor: texture color for current pixel
 * @x: current element in the rays array
*/

void renderFloor(int WallBottomPixel, SDL_Color *texelColor, int x)
{
    int y, texture_height, texture_width, textureOffsetY, textureOffsetX;
    float distance, ratio;

    texture_height = wallTextures[3].height;
    texture_width = wallTextures[3].width;

    for (y = WallBottomPixel; y < WINDOW_HEIGHT; y++)
    {
        ratio = player.height / (y - WINDOW_HEIGHT / 2);
        distance = (ratio * PROJ_PLANE)
                                / cos(rays[x].rayAngle - player.rotationAngle);

        textureOffsetY = (int)abs((distance * sin(rays[x].rayAngle)) + player);
        textureOffsetX = (int)abs((distance * cos(rays[x].rayAngle)) + player);

        textureOffsetY = (int)abs(textureOffsetY * texture_height / 30) % texture_height;
        textureOffsetX = (int)abs(textureOffsetX * texture_width / 30) % texture_width;

        *texelColor = wallTextures[4].texture_buffer[(textureOffsetY * texture_width) + textureOffsetX];
        drawPixel(x, y, texelColor);
    }
}

/**
 * renderCeil - renders the ceiling
 * @WallTopPixel: wall top pixel
 * @texelColor: texture color for current pixel
 * @x: current element in the rays array
 */

void renderCeil(int WallTopPixel, SDL_Color *texelColor, int x)
{
    int y, texture_height, texture_width, textureOffsetY, textureOffsetX;
    float distance, ratio;

    texture_height = wallTextures[3].height;
    texture_width = wallTextures[3].width;

    for (y = 0; y < WallTopPixel; y++)
    {
        ratio = player.height / (y - WINDOW_HEIGHT / 2);
        distance = (ratio * PROJ_PLANE)
                                / cos(rays[x].rayAngle - player.rotationAngle);

        textureOffsetY = (int)abs((distance * sin(rays[x].rayAngle)) + player);
        textureOffsetX = (int)abs((distance * cos(rays[x].rayAngle)) + player);

        textureOffsetY = (int)abs(textureOffsetY * texture_height / 30) % texture_height;
        textureOffsetX = (int)abs(textureOffsetX * texture_width / 30) % texture_width;

        *texelColor = wallTextures[3].texture_buffer[(textureOffsetY * texture_width) + textureOffsetX];
        drawPixel(x, y, texelColor);
    }
}

/**
 * renderWall - Renders the wall
 */

void renderWall(void)
{
    int x, y, textNum, texture_height, texture_width,
        textureOffsetY, textureOffsetX, WallTopPixel, WallBottomPixel;
        wallStripHeight, distanceFromTop;
        float perpDistance, projectedWallHeight;
        SDL_color texelColor;

    for (x = 0; x < NUM_RAYS; x++)
    {
        perpDistance = rays[x].distance * cos(rays[x].rayAngle
							- player.rotationAngle);
		projectedWallHeight = (TILE_SIZE / perpDistance) * PROJ_PLANE;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT
							? SCREEN_HEIGHT : wallBottomPixel;
		texNum = rays[x].wallHitContent - 1;
		texture_width = wallTextures[texNum].width;
		texture_height = wallTextures[texNum].height;
		renderFloor(wallBottomPixel, &texelColor, x);
		renderCeil(wallTopPixel, &texelColor, x);

		if (rays[x].wasHitVertical)
			textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
		else
			textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;

		for (y = wallTopPixel; y < wallBottomPixel; y++)
		{
			distanceFromTop = y + (wallStripHeight / 2) - (SCREEN_HEIGHT / 2);
			textureOffsetY = distanceFromTop *
								((float)texture_height / wallStripHeight);
			texelColor = wallTextures[texNum].
						 texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
			if (rays[x].wasHitVertical)
				changeColorIntensity(&texelColor, 0.5);
			drawPixel(x, y, texelColor);
		}
    }
}