#pragma once
#include "defines.h"

struct Vector2
{
	float x;
	float y;
};

struct Vector3
{
	float x, y, z;
	float xyz[3];
};

struct Vector4
{
	float x, y, z, w;

	float xyzw[4];
};

struct Vertex
{
	Vector4 position;
	unsigned int color;
	float u, v;
};

struct Matrix3x3
{
	Vector3 rows[3];
};

struct Matrix4x4
{
	Vector4 rows[4];
};

Matrix4x4 Identity()
{
	Matrix4x4 temp;
	//The first row
	temp.rows[0].x = 1;
	temp.rows[0].y = 0;
	temp.rows[0].z = 0;
	temp.rows[0].w = 0;
	//The second row
	temp.rows[1].x = 0;
	temp.rows[1].y = 1;
	temp.rows[1].z = 0;
	temp.rows[1].w = 0;
	//The third row
	temp.rows[2].x = 0;
	temp.rows[2].y = 0;
	temp.rows[2].z = 1;
	temp.rows[2].w = 0;
	//The fourth row
	temp.rows[3].x = 0;
	temp.rows[3].y = 0;
	temp.rows[3].z = 0;
	temp.rows[3].w = 1;

	return temp;
}

Matrix4x4 CreateRotationX(float _degree)
{
	Matrix4x4 temp = Identity();
	float radians = _degree * (float)(M_PI / 180);
	/*X Rotation
	[ 1,	0,	0] 
	[0, cos, -sin] 
	[0, sin,  cos]
	*/

	temp.rows[1].y = cos(radians);
	temp.rows[1].z = -sin(radians);
	temp.rows[2].y = sin(radians);
	temp.rows[2].z = cos(radians);
	
	return temp;
}

Matrix4x4 CreateRotationY(float _degree)
{
	Matrix4x4 temp = Identity();
	float radians = _degree * (float)(M_PI / 180);
	/*Y Rotation
	[ cos, 0,  sin]
	[0,   1,	 0]
	[-sin, 0, cos ]
	*/

	temp.rows[0].x = cos(radians);
	temp.rows[0].z = sin(radians);
	temp.rows[2].x = -sin(radians);
	temp.rows[2].z = cos(radians);

	return temp;
}

Matrix4x4 CreateRotationZ(float _degree)
{
	Matrix4x4 temp = Identity();
	float radians = _degree * (float)(M_PI / 180);
	/*Z rotation
	[ cos,-sin, 0]
	[ sin, cos, 0]
	[0,	   0,   1]
	*/

	temp.rows[0].x = cos(radians);
	temp.rows[0].y = -sin(radians);
	temp.rows[1].x = sin(radians);
	temp.rows[1].y = cos(radians);

	return temp;
}


Vector4 Vec3MultiMatrix3x3(Vector4 _vec4, Matrix3x3 _matrix)
{
	Vector4 temp;

	temp.x = (_vec4.x * _matrix.rows[0].x) + (_vec4.y * _matrix.rows[1].x) + (_vec4.z * _matrix.rows[2].x);
	temp.y = (_vec4.x * _matrix.rows[0].y) + (_vec4.y * _matrix.rows[1].y) + (_vec4.z * _matrix.rows[2].y);
	temp.z = (_vec4.x * _matrix.rows[0].z) + (_vec4.y * _matrix.rows[1].z) + (_vec4.z * _matrix.rows[2].z);

	return temp;
}

Vector4 VecMultiMatrix4x4(Vector4 _vec4, Matrix4x4 _matrix4x4)
{
	/*
	Vector3 	Matrix3x3		Vector3 
	[ X,Y,Z,] * [A, B, C,   =  [XA + YD + ZG,
				 D, E, F,		XB + YE + ZH,
				 G, H, I]		XC + YF + ZI]
	*/

	Vector4 temp;
	temp.x = (_vec4.x * _matrix4x4.rows[0].x) + (_vec4.y * _matrix4x4.rows[1].x) + (_vec4.z * _matrix4x4.rows[2].x) + (_vec4.w * _matrix4x4.rows[3].x);
	temp.y = (_vec4.x * _matrix4x4.rows[0].y) + (_vec4.y * _matrix4x4.rows[1].y) + (_vec4.z * _matrix4x4.rows[2].y) + (_vec4.w * _matrix4x4.rows[3].y);
	temp.z = (_vec4.x * _matrix4x4.rows[0].z) + (_vec4.y * _matrix4x4.rows[1].z) + (_vec4.z * _matrix4x4.rows[2].z) + (_vec4.w * _matrix4x4.rows[3].z);
	temp.w = (_vec4.x * _matrix4x4.rows[0].w) + (_vec4.y * _matrix4x4.rows[1].w) + (_vec4.z * _matrix4x4.rows[2].w) + (_vec4.w * _matrix4x4.rows[3].w);

	return temp;

}

int TwoDArrayToOneDArray(int _x, int _y, unsigned int _width)
{
	return _y * _width + _x;
}

Vertex CartesainToScreen(Vertex _vec4)
{
	Vertex temp = _vec4;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

	temp.position.x = (_vec4.position.x + 1) * (width / 2);
	temp.position.y = (1 - _vec4.position.y) * (height / 2);

	return temp;
}

Matrix4x4 CreateTranslation(float _x, float _y, float _z)
{
	Matrix4x4 temp = Identity();

	temp.rows[3].x = _x;
	temp.rows[3].y = _y;
	temp.rows[3].z = _z;
	//change the bottom row 0 1 2

	return temp;
}

//Assuming the matrix is Affine and Orthogonal
Matrix4x4 FastInverse(Matrix4x4 _matrix)
{
	Vector4 position = _matrix.rows[3];

	/* Transpose example
		[1,2,3          [1,4,7
		 4,5,6      =    2,5,8
		 7,8,9]          3,6,9]
	*/

//This matrix is already transposed
#pragma region matrix3x3

	Matrix3x3 matrix3x3;
	matrix3x3.rows[0].x = _matrix.rows[0].x;
	matrix3x3.rows[0].y = _matrix.rows[1].x;
	matrix3x3.rows[0].z = _matrix.rows[2].x;
	matrix3x3.rows[1].x = _matrix.rows[0].y;
	matrix3x3.rows[1].y = _matrix.rows[1].y;
	matrix3x3.rows[1].z = _matrix.rows[2].y;
	matrix3x3.rows[2].x = _matrix.rows[0].z;
	matrix3x3.rows[2].y = _matrix.rows[1].z;
	matrix3x3.rows[2].z = _matrix.rows[2].z;
#pragma endregion

	position = Vec3MultiMatrix3x3(position, matrix3x3);

	//Negate the vector
	position.x *= -1;
	position.y *= -1;
	position.z *= -1;
	position.w = _matrix.rows[3].w;

	_matrix.rows[3] = position;
	_matrix.rows[0].x = matrix3x3.rows[0].x;
	_matrix.rows[0].y = matrix3x3.rows[0].y;
	_matrix.rows[0].z = matrix3x3.rows[0].z;
	_matrix.rows[1].x = matrix3x3.rows[1].x;
	_matrix.rows[1].y = matrix3x3.rows[1].y;
	_matrix.rows[1].z = matrix3x3.rows[1].z;
	_matrix.rows[2].x = matrix3x3.rows[2].x;
	_matrix.rows[2].y = matrix3x3.rows[2].y;
	_matrix.rows[2].z = matrix3x3.rows[2].z;

	return _matrix;
}

Matrix4x4 Matrix4x4MultiMatrix4x4(Matrix4x4 _matrix1, Matrix4x4 _matrix2)
{
	/*Rows* Cols
	[A,B,C,D        [M,N,O,P
     E,F,G,H     *   Q,R,S,T 
     I,J,K,L         U,V,W,X
	 1,2,3,4]        5,6,7,8]*/
	Vector4 Xvector1 = _matrix1.rows[0];
	Vector4 Yvector1 = _matrix1.rows[1];
	Vector4 Zvector1 = _matrix1.rows[2];
	Vector4 Wvector1 = _matrix1.rows[3];

	Vector4 Xvector2 = _matrix2.rows[0];
	Vector4 Yvector2 = _matrix2.rows[1];
	Vector4 Zvector2 = _matrix2.rows[2];
	Vector4 Wvector2 = _matrix2.rows[3];


	Matrix4x4 temp;

	//The X row for temp
	temp.rows[0].x = (Xvector1.x * Xvector2.x) + (Xvector1.y * Yvector2.x) + (Xvector1.z * Zvector2.x) + (Xvector1.w * Wvector2.x);
	temp.rows[0].y = (Xvector1.x * Xvector2.y) + (Xvector1.y * Yvector2.y) + (Xvector1.z * Zvector2.y) + (Xvector1.w * Wvector2.y);
	temp.rows[0].z = (Xvector1.x * Xvector2.z) + (Xvector1.y * Yvector2.z) + (Xvector1.z * Zvector2.z) + (Xvector1.w * Wvector2.z);
	temp.rows[0].w = (Xvector1.x * Xvector2.w) + (Xvector1.y * Yvector2.w) + (Xvector1.z * Zvector2.w) + (Xvector1.w * Wvector2.w);

	//The Y row for temp
	temp.rows[1].x = (Yvector1.x * Xvector2.x) + (Yvector1.y * Yvector2.x) + (Yvector1.z * Zvector2.x) + (Yvector1.w * Wvector2.x);
	temp.rows[1].y = (Yvector1.x * Xvector2.y) + (Yvector1.y * Yvector2.y) + (Yvector1.z * Zvector2.y) + (Yvector1.w * Wvector2.y);
	temp.rows[1].z = (Yvector1.x * Xvector2.z) + (Yvector1.y * Yvector2.z) + (Yvector1.z * Zvector2.z) + (Yvector1.w * Wvector2.z);
	temp.rows[1].w = (Yvector1.x * Xvector2.w) + (Yvector1.y * Yvector2.w) + (Yvector1.z * Zvector2.w) + (Yvector1.w * Wvector2.w);

	//The Z row for temp
	temp.rows[2].x = (Zvector1.x * Xvector2.x) + (Zvector1.y * Yvector2.x) + (Zvector1.z * Zvector2.x) + (Zvector1.w * Wvector2.x);
	temp.rows[2].y = (Zvector1.x * Xvector2.y) + (Zvector1.y * Yvector2.y) + (Zvector1.z * Zvector2.y) + (Zvector1.w * Wvector2.y);
	temp.rows[2].z = (Zvector1.x * Xvector2.z) + (Zvector1.y * Yvector2.z) + (Zvector1.z * Zvector2.z) + (Zvector1.w * Wvector2.z);
	temp.rows[2].w = (Zvector1.x * Xvector2.w) + (Zvector1.y * Yvector2.w) + (Zvector1.z * Zvector2.w) + (Zvector1.w * Wvector2.w);

	//The W row for temp
	temp.rows[3].x = (Wvector1.x * Xvector2.x) + (Wvector1.y * Yvector2.x) + (Wvector1.z * Zvector2.x) + (Wvector1.w * Wvector2.x);
	temp.rows[3].y = (Wvector1.x * Xvector2.y) + (Wvector1.y * Yvector2.y) + (Wvector1.z * Zvector2.y) + (Wvector1.w * Wvector2.y);
	temp.rows[3].z = (Wvector1.x * Xvector2.z) + (Wvector1.y * Yvector2.z) + (Wvector1.z * Zvector2.z) + (Wvector1.w * Wvector2.z);
	temp.rows[3].w = (Wvector1.x * Xvector2.w) + (Wvector1.y * Yvector2.w) + (Wvector1.z * Zvector2.w) + (Wvector1.w * Wvector2.w);

	return temp;
}

float ImplicitLineEquation(Vector4 _point, Vector4 _lineStart, Vector4 _lineEnd)
{
	return (((_lineStart.y - _lineEnd.y) * _point.x) + ((_lineEnd.x - _lineStart.x) * _point.y)) + (_lineStart.x * _lineEnd.y) - (_lineStart.y * _lineEnd.x);
}

//Returns Beta/Alpha/Gamma
Vector4 FindBarycentricCoordinates(Vector4 _beta, Vector4 _alpha, Vector4 _gamma, Vector4 _point)
{
	Vector4 temp;
	float maxBeta = ImplicitLineEquation(_beta, _alpha, _gamma);
	float subBeta = ImplicitLineEquation(_point, _alpha, _gamma);

	float maxAlpha = ImplicitLineEquation(_alpha, _gamma, _beta);
	float subAlpha = ImplicitLineEquation(_point, _gamma, _beta);

	float maxGamma = ImplicitLineEquation(_gamma, _beta, _alpha);
	float subGamma = ImplicitLineEquation(_point, _beta, _alpha);

	temp.x = subBeta / maxBeta;
	temp.y = subAlpha / maxAlpha;
	temp.z = subGamma / maxGamma;

	return temp;
}

float Berp(float _betaZ, float _alphaZ, float _gammaZ, Vector4 _bya)
{
	//alpha(A) + (beta)B + (gamma)C
	return (_betaZ * _bya.x) + (_alphaZ * _bya.y) + (_gammaZ * _bya.z);
}