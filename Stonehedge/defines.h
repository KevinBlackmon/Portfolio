#pragma once
#include "RasterSurface.h"
#include <math.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500
#define SCREEN_PIXELS ((SCREEN_WIDTH) * (SCREEN_HEIGHT))
#define FOV 90
#define ASPECT_RATIO ((float)SCREEN_HEIGHT / SCREEN_WIDTH)
#define NEAR_PLANE 0.1f
#define FAR_PLANE 10
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "XTime.h"
#include "celestial.h"
#include "greendragon.h"
#include "flower.h"
#include "treeolife.h"
#define RADIANS_FOV FOV * (M_PI / 180)
#define YSCALE (1/tan((0.5) * RADIANS_FOV))
#define XSCALE YSCALE * ASPECT_RATIO
#define IMAGE_WIDTH flower_width
#define IMAGE_HEIGHT flower_height
unsigned int pixelArray[SCREEN_PIXELS] = { 0, };
float Zbuffer[SCREEN_PIXELS] = { 0, };
//FOV = 90
// Aspect Ratio = 1
// Near Plane is at 0.1
// Far Plane is at 10

