#include"../Class Utilities/RasterSurface.h"
#include "../Assignments/Assignment 1/para_CC0_particlefx-2/fire_01.h"
#include "../Assignments/Assignment 1/para_CC0_particlefx-2/lighter_flame_01.h"
#include "tiles_12.h"
#include "XTime.h"
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <vector>



struct Square
{
	unsigned int Top;
	unsigned int Bottom;
	unsigned int Left;
	unsigned int Right;
};

unsigned int TwoDArrayToOneDArray(unsigned int _x, unsigned int _y, unsigned int _width);
void ClearColor(unsigned int _color);
void DrawPixel(unsigned int _pixelX, unsigned int _pixelY, unsigned int _color);
void BLIT(const unsigned int* _source, unsigned int _sourceWidth, Square rect, unsigned int _x, unsigned int _y);
unsigned int ColorConverter(unsigned int _color);
int RandomNumbers(int _range);
unsigned int Lerp(unsigned int A, unsigned int B, float _ratio);
unsigned int ColorBlender(unsigned int _source, unsigned int _dest);

//Height and Width of the screen
const unsigned int screenHeight = 500;
const unsigned int screenWidth = 500;

//xrgb Pixels and Array or pixels
const unsigned int xrgbPixels = screenWidth * screenHeight;

unsigned int pixelArray[screenWidth * screenHeight] = { 0, };
int main()
{
	srand((unsigned int)time(NULL));

	//The grass block
	Square grass;
	grass.Left = 289;
	grass.Top = 129;
	grass.Right = 319;
	grass.Bottom = 160;

	//The flowers
	Square store;
	store.Top = 194;
	store.Left = 50;
	store.Bottom = 207;
	store.Right = 79;

	//Background XY coordinates
	unsigned int Xcord = 0;
	unsigned int Ycord = 0;

	//The shift of the each grass block
	unsigned int GrassleftShift = grass.Right - grass.Left;
	unsigned int GrassdropShift = grass.Bottom - grass.Top;


	//left and drop shift of the store
	unsigned int StoreleftShift = store.Right - store.Left;
	unsigned int StoredropShift = store.Bottom - store.Top;


	//Random XY coordinates
	unsigned int randomX[10];  
	unsigned int randomY[10];

	//Vector for the animation
	std::vector<Square> animation;

	Square temp;
	temp.Left = 0;
	temp.Right = 128;
	temp.Top = 0;
	temp.Bottom = 128;
	for (size_t i = 0; i < 64; i++)
	{
		animation.push_back(temp);
		temp.Left += 128;
		temp.Right += 128;
		if (temp.Left == 1024)
		{
			temp.Left = 0;
			temp.Top += 128;
			temp.Bottom += 128;
			temp.Right = 128;
		}
	}

	//The timer variable
	XTime timer;
	timer.Restart();

	//Vector index
	int index = 0;

	//The 30 fps tracker
	float tracker = 0;

	for (size_t i = 0; i < 10; i++)
	{
		randomX[i] = RandomNumbers(500 - StoreleftShift);
	}
	for (size_t i = 0; i < 10; i++)
	{
		randomY[i] = RandomNumbers(500 - StoredropShift);
	}

	RS_Initialize("Kevin Blackmon Lab1", screenWidth, screenHeight);
	while (RS_Update(pixelArray, xrgbPixels))
	{
		ClearColor(0x00000000);
		timer.Signal();
		float delta = (float)timer.Delta();
		tracker += delta;
		//The code for the grass background
		for (size_t j = 0; j < 500 / GrassdropShift + 1; j++)
		{
			for (size_t i = 0; i < 500 / GrassleftShift + 1; i++)
			{
				BLIT(tiles_12_pixels, tiles_12_width, grass, GrassleftShift * i, GrassdropShift * j);
			}
		}
		

		//Code for the random stores
		for (size_t i = 0; i < 10; i++)
		{
			BLIT(tiles_12_pixels, tiles_12_width, store, randomX[i], randomY[i]);
		}
		//Animation code

		BLIT(fire_01_pixels, fire_01_width, animation[index], 200, 200);
		if (tracker >= (1.0f / 30))
		{
			index++;
			tracker = 0;
			if (index >= 64)
				index = 0;
		}
	}
	
	RS_Shutdown();
}

 unsigned int TwoDArrayToOneDArray(unsigned int _x, unsigned int _y, unsigned int _width)
{
	 return _y * _width + _x;
}

 void ClearColor(unsigned int _color)
 {
	// _color = ColorConverter(_color);
	 for (size_t i = 0; i < 250000; i++)
	 {
		 pixelArray[i] = _color;
	 }
 }

 void DrawPixel(unsigned int _pixelX, unsigned int _pixelY, unsigned int _color)
 {
	 //check colors alpha < 255
	 //if is pixel at that spot color blend color is source and pixelArray is destination
	 //else do what is already there
	 unsigned int alphaMask = 0xFF000000;
	 unsigned int alpha = (_color & alphaMask) >> 24;

	 if (_pixelX < screenWidth && _pixelY < screenHeight)
	 {
		 if (alpha < 255)
		 {
			 pixelArray[TwoDArrayToOneDArray(_pixelX, _pixelY, 500)] = ColorBlender(_color, pixelArray[TwoDArrayToOneDArray(_pixelX, _pixelY, 500)]);
		 }
		 else
		 {
			 pixelArray[TwoDArrayToOneDArray(_pixelX, _pixelY, 500)] = _color;
		 }
	 }
 }

 void BLIT(const unsigned int* _source, unsigned int _sourceWidth, Square rect, unsigned int _x, unsigned int _y)
 {

	 unsigned int index = 0;
	 for (size_t rows = 0; rows < rect.Right - rect.Left; rows++)
	 {
		 for (size_t cols = 0; cols < rect.Bottom - rect.Top; cols++)
		 {
			 index = TwoDArrayToOneDArray(rect.Left + rows, rect.Top + cols, _sourceWidth);
			 unsigned int color = _source[index];
			 color = ColorConverter(color);
			 DrawPixel(_x + rows, _y + cols, color);
		 }
	 }
	 //Nested for loops
	//Draw pixel
 }

 unsigned int ColorConverter(unsigned int _color)
 {
	 //The color is in BGRA format we want ARGB

	 //RGBA color mask
	 unsigned int blueMask = 0xFF000000;
	 unsigned int greenMask = 0x00FF0000;
	 unsigned int redMask = 0x0000FF00;
	 unsigned int alphaMask = 0x000000FF;

	 unsigned int red = (_color & redMask) >> 8;
	 unsigned int green = (_color & greenMask) >> 16;
	 unsigned int blue = (_color & blueMask) >> 24;
	 unsigned int alpha = (_color & alphaMask);

	 return (alpha << 24) | (red << 16) | (green << 8) | blue;
 }

 int RandomNumbers(int _range)
 {
	 return rand() % _range;

 }

 unsigned int Lerp(unsigned int A, unsigned int B, float _ratio)
 {
	 return ((int)B - (int)A) * _ratio + A;
 }

 unsigned int ColorBlender(unsigned int _source, unsigned int _dest)
 {
	 //Source is the grass
	 //Destionation is the flame
#pragma region colorMask
	 unsigned int blueMask = 0x000000FF;
	 unsigned int greenMask = 0x0000FF00;
	 unsigned int redMask = 0x00FF0000;
	 unsigned int alphaMask = 0xFF000000;
#pragma endregion

	 unsigned int sourceRed = (_source & redMask) >> 16;
	 unsigned int sourceGreen = (_source & greenMask) >> 8;
	 unsigned int sourceBlue = (_source & blueMask);
	 unsigned int sourceAlpha = (_source & alphaMask) >> 24;

	


	 unsigned int destRed = (_dest & redMask) >> 16;
	 unsigned int destGreen = (_dest & greenMask) >> 8;
	 unsigned int destBlue = (_dest & blueMask);
	 unsigned int destAlpha = (_dest & alphaMask) >> 24;

	 float ratio = destAlpha / 255.0f;

	 //Lerp
	 unsigned int finalRed = Lerp(sourceRed, destRed, ratio);
	 unsigned int finalGreen = Lerp(sourceGreen, destGreen, ratio);
	 unsigned int finalBlue = Lerp(sourceBlue, destBlue, ratio);
	 unsigned int finalAlpha = Lerp(sourceAlpha, destAlpha, ratio);


	 return finalAlpha << 24 | finalRed << 16 | finalGreen << 8 | finalBlue;
 }
