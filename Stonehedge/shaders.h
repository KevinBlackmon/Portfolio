#pragma once
#include "MyMath.h"

/// <summary>
	 /// 4x4Matrix - rotation, translation scaling
	 /// LocalSpace - define all points in carteison 
	 /// WorldSpace - World matrix for every mesh
	 /// ViewSpace - Camera matrix , world matrix, inverse apply to everything in worldspace where cam at origin
	 /// Porjection Space - account aspect ratio, FOV, near plane, far plane
	 /// Perspective Divide - last step
	 /// This is done in this order right before we draw
	 /// All in vertex shader
	 /// Two world matrix 1 for the grid 1 for the cube
	 /// Multitply every  vertex by world matrix
	 /// We want a rotation matrix and translation matrix
	 /// World matrix for the cube is the translation matrix * rotation matrix to get the cubes world matrix
	 /// Multiply by the view Matrix to get into view space
	 /// All w should initialize to 1
	 /// </summary>
	 /// <returns></returns>

void (*VertexShader)(Vertex&) = 0;

void (*PixelShader)(unsigned int&, float, float) = 0;//Add the two floats here

Matrix4x4 SV_WorldMatrix;
Matrix4x4 SV_ViewMatrix;
Matrix4x4 SV_PorjectionMatrix;

void VS_World(Vertex &multiplyMe)
{
	multiplyMe.position = VecMultiMatrix4x4(multiplyMe.position, SV_WorldMatrix);
	multiplyMe.position = VecMultiMatrix4x4(multiplyMe.position, SV_ViewMatrix);
	multiplyMe.position = VecMultiMatrix4x4(multiplyMe.position, SV_PorjectionMatrix);

	multiplyMe.position.x /= multiplyMe.position.w;
	multiplyMe.position.y /= multiplyMe.position.w;
	multiplyMe.position.z /= multiplyMe.position.w;
	//multiplyMe.u /= multiplyMe.position.w;
	//multiplyMe.v /= multiplyMe.position.w;
}

void PS_White(unsigned int &makeWhite, float _U = 0, float _V = 0)
{
	makeWhite = 0xFFFFFFFF;
}

void PS_Green(unsigned int& makeGreen, float _U = 0, float _V = 0)
{
	makeGreen = 0xFF00FF00;
}

void PS_Red(unsigned int& makeRed, float _U = 0, float _V = 0)
{
	makeRed = 0xFFFF0000;
}

void PS_TexelToPixel(unsigned int& _color, float _U, float _V)
{
	//The conversion 
	// U * ImageWidth = x
	//V * ImageHeight = y
	//call the twoDtooneD

	//Ask would I get the uv from the image array instead of passing in parameters
	int X = (int)(_U * IMAGE_WIDTH);
	int Y = (int)(_V * IMAGE_HEIGHT);
	if (GetKeyState('A') & 0x1)
	{
		_color = flower_pixels[TwoDArrayToOneDArray(X, Y, IMAGE_WIDTH)];
	}
	else if (GetKeyState('S') & 0x1)
	{
		_color = celestial_pixels[TwoDArrayToOneDArray(X, Y, IMAGE_WIDTH)];
	}
	else if (GetKeyState('D') & 0x1)
	{
		_color = greendragon_pixels[TwoDArrayToOneDArray(X, Y, IMAGE_WIDTH)];
	}
	else
	{
		_color = treeolife_pixels[TwoDArrayToOneDArray(X, Y, IMAGE_WIDTH)];
	}
	

}