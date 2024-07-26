#include "../headers/header.h"
/**
 * drawRect - draw a rectangle
 * @x: x coordinate of rectangle
 * @y: y coordinate of rectangle
 * @width: width of rectangle
 * @height: height of rectangle
 * @color: color of rectangle
 */
void drawRect(int x, int y, int width, int height, color_t color)
{
    int i, j;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            drawPixel(x + j, y + i, color);
}
/**
 * drawLine - draw a line
 * @x0: x coordinate of init
 * @y0: y coordinate of init
 * @x1: x coordinate of init
 * @y1: y coordinate of end
 * @color: color of the pixel
 */
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
   float xIncrement, yIncrement, currentX, currentY;

   delta_x = (x1 - x0);
}  delta_y = (y1 - y0);
   if (abs(delta_x) >= abs(delta_y))
   {
       steps = abs(delta_x);
   }
   else
   {
       steps = abs(delta_y) >= abs(delta_x) ? abs(delta_y) : abs(delta_x);
   }
   xIncrement = delta_x / (float)steps;
   yIncrement = delta_y / (float)steps;
   currentX = x0;
   currentY = y0;
   for (int i = 0; i <= steps; i++)
   {
       drawPixel(round(currentX), round(currentY), color);
       currentX += xIncrement;
       currentY += yIncrement;
   } 