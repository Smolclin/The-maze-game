#include "../headers/header.h"

/**
 * distanceBetweenPoints - calculates the distance between two points
 * @x1: x coordinate of the first point
 * @y1: y coordinate of the first point
 * @x2: x coordinate of the second point
 * @y2: y coordinate of the second point
 * Return: distance between the two points
 */

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return (sqrtf(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

/**
 * isRayFacingDown - checks if the ray is facing down
 * @angle: angle of the ray
 * Return: true if the ray is facing down, false otherwise
 */

bool isRayFacingDown(float angle)
{
    return (angle > 0 && angle < PI);
}

/**
 * isRayFacingUp - checks if the ray is facing up
 * @angle: angle of the ray
 * Return: true if the ray is facing up, false otherwise
 */

bool isRayFacingUp(float angle)
{
    return (!isRayFacingDown(angle));
}

/**
 * isRayFacingRight - checks if the ray is facing right
 * @angle: angle of the ray
 * Return: true if the ray is facing right, false otherwise
 */

bool isRayFacingRight(float angle)
{
    return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * isRayFacingLeft - checks if the ray is facing left
 * @angle: angle of the ray
 * Return: true if the ray is facing left, false otherwise
 */

bool isRayFacingLeft(float angle)
{
    return (!isRayFacingRight(angle));
}