#pragma once
#include "shaders.h"

unsigned int Lerp(unsigned int A, unsigned int B, float _ratio);
unsigned int ColorBlender(unsigned int _source, unsigned int _dest, float _ratio);
unsigned int ColorBlender(unsigned int _source, unsigned int _dest);
unsigned int ColorConverter(unsigned int _color);
void ClearColor(unsigned int _color);
void parametericLine(Vertex& _startVertex, Vertex& _endVertex);
void DrawPixel(int _pixelX, int _pixelY, float _pixelZ, unsigned int _color);




unsigned int Lerp(unsigned int A, unsigned int B, float _ratio)
{
	return (unsigned int)(((int)B - (int)A) * _ratio + A);
}

float Lerp(float A, float B, float _ratio)
{
	return ((B - A) * _ratio + A);
}

int Lerp( int A,  int B, float _ratio)
{
	return (int)((B - A) * _ratio + A);
}

unsigned int ColorBlender(unsigned int _source, unsigned int _dest, float _ratio)
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

	//Lerp
	unsigned int finalRed = Lerp(sourceRed, destRed, _ratio);
	unsigned int finalGreen = Lerp(sourceGreen, destGreen, _ratio);
	unsigned int finalBlue = Lerp(sourceBlue, destBlue, _ratio);
	unsigned int finalAlpha = Lerp(sourceAlpha, destAlpha, _ratio);


	return finalAlpha << 24 | finalRed << 16 | finalGreen << 8 | finalBlue;
}

unsigned int ColorBlender(unsigned int _source, unsigned int _dest)
{
	//color lerp
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

unsigned int BerpColor(unsigned int _color1, unsigned int _color2, unsigned int _color3, Vector4 _bya)
{
	//Color lerp
#pragma region colorMask
	unsigned int blueMask = 0x000000FF;
	unsigned int greenMask = 0x0000FF00;
	unsigned int redMask = 0x00FF0000;
	unsigned int alphaMask = 0xFF000000;
#pragma endregion

	unsigned int _color1Red = (_color1 & redMask) >> 16;
	unsigned int _color1Green = (_color1 & greenMask) >> 8;
	unsigned int _color1Blue = (_color1 & blueMask);
	unsigned int _color1Alpha = (_color1 & alphaMask) >> 24;

	unsigned int _color2Red = (_color2 & redMask) >> 16;
	unsigned int _color2Green = (_color2 & greenMask) >> 8;
	unsigned int _color2Blue = (_color2 & blueMask);
	unsigned int _color2Alpha = (_color2 & alphaMask) >> 24;

	unsigned int _color3Red = (_color3 & redMask) >> 16;
	unsigned int _color3Green = (_color3 & greenMask) >> 8;
	unsigned int _color3Blue = (_color3 & blueMask);
	unsigned int _color3Alpha = (_color3 & alphaMask) >> 24;

	//Berp
	unsigned int finalRed = (unsigned int)Berp((float)_color1Red, (float)_color2Red, (float)_color3Red, _bya);
	unsigned int finalGreen = (unsigned int)Berp((float)_color1Green, (float)_color2Green, (float)_color3Green, _bya);
	unsigned int finalBlue = (unsigned int)Berp((float)_color1Blue, (float)_color2Blue, (float)_color3Blue, _bya);
	unsigned int finalAlpha = (unsigned int) Berp((float)_color1Alpha, (float)_color2Alpha, (float)_color3Alpha, _bya);


	return finalAlpha << 24 | finalRed << 16 | finalGreen << 8 | finalBlue;
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

void ClearColor(unsigned int _color)
{
	for (size_t i = 0; i < SCREEN_PIXELS; i++)
	{
		pixelArray[i] = _color;
		Zbuffer[i] = 1;
	}
}

void parametericLine( Vertex& _startVertex,  Vertex& _endVertex)
{
	//Four varience of the loop
	//larger change in Y means Y loop
	//larger change in X means X loop
	//Is the line going up
	//Is the line going down

	//Change to use the struct vertex so it takes two and set the arrays 0 and 1 as the xy
	float startX = _startVertex.position.x;
	float endX = _endVertex.position.x;
	float startY = _startVertex.position.y;
	float endY = _endVertex.position.y;
	float startZ = _startVertex.position.z;
	float endZ = _endVertex.position.z;


	//Basically and if statement by checking if which didplacement is greater then setting the value to that
	float GreaterDisplace = (std::abs(endX - startX) > std::abs(endY - startY)) ? std::abs(endX - startX) : std::abs(endY - startY);

	for (float i = 0; i < GreaterDisplace; i++)
	{
		float ratio = (float)i / GreaterDisplace;
		unsigned int blendedColor = ColorBlender(_startVertex.color, _endVertex.color, ratio);
		int currY = Lerp((int)startY, (int)endY, ratio);
		int currX = Lerp((int)startX, (int)endX, ratio);
		float currZ = Lerp(startZ, endZ, ratio);
		if (PixelShader)
		{
			PixelShader(blendedColor, 0, 0);
		}
		DrawPixel((int)currX, (int)floor(currY + 0.5), currZ, blendedColor);
	}
}

void DrawPixel(int _pixelX, int _pixelY, float _pixelZ, unsigned int _color)
{
	//check colors alpha < 255
	//if is pixel at that spot color blend color is source and pixelArray is destination
	//else do what is already there
	unsigned int alphaMask = 0xFF000000;
	unsigned int alpha = (_color & alphaMask) >> 24;
	

	if (_pixelX < SCREEN_WIDTH && _pixelY < SCREEN_HEIGHT && _pixelX >= 0 && _pixelY >= 0)
	{
		if (_pixelZ < Zbuffer[TwoDArrayToOneDArray(_pixelX, _pixelY, SCREEN_WIDTH)])
		{
			pixelArray[TwoDArrayToOneDArray(_pixelX, _pixelY, SCREEN_WIDTH)] = _color; //= ColorBlender(_color, pixelArray[TwoDArrayToOneDArray(_pixelX, _pixelY, SCREEN_WIDTH)]);
			Zbuffer[TwoDArrayToOneDArray(_pixelX, _pixelY, SCREEN_WIDTH)] = _pixelZ;
		}
	}
}

void DrawLine(const Vertex& start, const Vertex& end)
{
	Vertex copy_start = start;
	Vertex copy_end = end;

	if (VertexShader)
	{
		VertexShader(copy_start);
		VertexShader(copy_end);
	}

	//Ask about what the SCREENXY are?
	Vertex Screen_Start = CartesainToScreen(copy_start);
	Vertex Screen_End = CartesainToScreen(copy_end);


	parametericLine(Screen_Start, Screen_End);
}

/// <summary>
/// Three point and fill in the area of those three points
/// Fill triangle the same as the draw line when you get to paracentric line use the fill triangle algorithms
/// UV convert to XY and plug into 2Dto1D coverter
/// </summary>
/// <returns></returns>
void FillTriangle(Vertex _beta, Vertex _alpha, Vertex _gamma, unsigned int _color = 0xFFFFFFFF)
{
	//UV interpolation

	Vertex copy_beta = _beta;
	Vertex copy_alpha = _alpha;
	Vertex copy_gamma = _gamma;

	if (VertexShader)
	{
		VertexShader(copy_beta);
		VertexShader(copy_alpha);
		VertexShader(copy_gamma);
	}
	Vertex Screen_Beta = CartesainToScreen(copy_beta);
	Vertex Screen_Alpha = CartesainToScreen(copy_alpha);
	Vertex Screen_Gamma = CartesainToScreen(copy_gamma);

	float minX = min(min(Screen_Beta.position.x, Screen_Alpha.position.x), Screen_Gamma.position.x);
	float minY = min(min(Screen_Beta.position.y, Screen_Alpha.position.y), Screen_Gamma.position.y);
	float maxX = max(max(Screen_Beta.position.x, Screen_Alpha.position.x), Screen_Gamma.position.x);
	float maxY = max(max(Screen_Beta.position.y, Screen_Alpha.position.y), Screen_Gamma.position.y);

	for (size_t i = (size_t)minX; i < maxX; i++)
	{
		for (size_t j = (size_t)minY; j < maxY; j++)
		{
			Vertex temp;
			temp.position.x = (float)i;
			temp.position.y = (float)j;
			Vector4 bya = FindBarycentricCoordinates(Screen_Beta.position, Screen_Alpha.position, Screen_Gamma.position, temp.position);
			if ((bya.x >=0 && bya.x <= 1) && (bya.y >= 0 && bya.y <= 1) && (bya.z >= 0 && bya.z <= 1))
			{
				temp.position.z = Berp(Screen_Beta.position.z, Screen_Alpha.position.z, Screen_Gamma.position.z, bya);
				float birlz = Berp(1 / Screen_Beta.position.w, 1 / Screen_Alpha.position.w, 1 / Screen_Gamma.position.w, bya);
				float baryu = Berp(Screen_Beta.u / Screen_Beta.position.w, Screen_Alpha.u / Screen_Alpha.position.w, Screen_Gamma.u / Screen_Gamma.position.w, bya);
				float baryv = Berp(Screen_Beta.v / Screen_Beta.position.w, Screen_Alpha.v / Screen_Alpha.position.w, Screen_Gamma.v / Screen_Gamma.position.w, bya);
				//Figure out how to divide the UV by W
				if (PixelShader)
				{
					PixelShader(_color, baryu / birlz, baryv / birlz);
				}
				_color = ColorConverter(_color);
				//convert the color
				temp.color = _color;
				DrawPixel(i, j, temp.position.z, temp.color);
			}
		}
	}
}
