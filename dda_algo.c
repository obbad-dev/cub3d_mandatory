#include "header.h"


float normalizeAngle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle <  0){
		angle = TWO_PI + angle;
	}
	return angle;
}
float distanceBetweenPoints(float x1, float y1, float x2, float y2){

	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void DDA(t_data *data, float rayAngle)
{
	rayAngle = normalizeAngle(rayAngle);
	int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	int isRayFacingUp = !isRayFacingDown; 
	
	int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;


	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	// int horzWallContent = 0;

	yintercept = floor(data->py/TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	xintercept = data->px + (yintercept - data->py) / tan(rayAngle);

	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE/tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WIN_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WIN_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (check_wall(xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // horzWallContent = arr[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

	// vertical strip 
	int foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    // int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(data->px / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = data->px + (xintercept - data->px) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WIN_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WIN_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (check_wall(xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            // vertWallContent = arr[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }


    float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(data->px, data->py, horzWallHitX, horzWallHitY) : FLT_MAX;
    float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(data->px,data->py, vertWallHitX, vertWallHitY) : FLT_MAX;
	if (vertHitDistance < horzHitDistance) 
	{
		draw_line(data, data->px, data->py, vertWallHitX, vertWallHitY, 0x00ff00);
	}
	else
		draw_line(data, data->px, data->py, horzWallHitX, horzWallHitY, 0x00ff00);
    // if (vertHitDistance < horzHitDistance) {
    //     rays[stripId].distance = vertHitDistance;
    //     rays[stripId].wallHitX = vertWallHitX;
    //     rays[stripId].wallHitY = vertWallHitY;
    //     rays[stripId].wallHitContent = vertWallContent;
    //     rays[stripId].wasHitVertical = true;
    // } else {
    //     rays[stripId].distance = horzHitDistance;
    //     rays[stripId].wallHitX = horzWallHitX;
    //     rays[stripId].wallHitY = horzWallHitY;
    //     rays[stripId].wallHitContent = horzWallContent;
    //     rays[stripId].wasHitVertical = true;
    // }
    // rays[stripId].rayAngle = rayAngle;
    // rays[stripId].isRayFacingDown = isRayFacingDown;
    // rays[stripId].isRayFacingUp = isRayFacingUp;
    // rays[stripId].isRayFacingLeft = isRayFacingLeft;
    // rays[stripId].isRayFacingRight = isRayFacingRight;
}































































// void DDA(t_data *data, double rayAngle)
// {	
// 	double rayDirX = cos(rayAngle);
// 	double rayDirY = sin(rayAngle);

// 	double deltaDistX = fabs(1 / rayDirX);
// 	double deltaDistY = fabs(1 / rayDirY);

// 	int x = (int)data->px; 
// 	int y = (int)data->py; 

// 	int stepX = 0;
// 	int stepY = 0;
// 	double sideDistX = 0;
// 	double sideDistY = 0;

// 	if (rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (data->px - x) * deltaDistX;
// 	}
// 	else 
// 	{
// 		stepX = 1;
// 		sideDistX = (x + 1.0 - data->px) * deltaDistX;
// 	}

// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (data->py - y) * deltaDistY;
// 	}
// 	else 
// 	{
// 		stepY = 1;
// 		sideDistY = (y + 1.0 - data->py) * deltaDistY;
// 	}

// 	int side = 0;

// 	while (1)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			x += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			y += stepY;
// 			side = 1;
// 		}
// 		if (check_wall(x, y)) 
// 			break;
// 	}

	
// }


