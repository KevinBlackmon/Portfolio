#include "Rasterizer.h"


/// Rotating Cube
/// define.h all defines
/// mymath.h includes defines.h all the math required
/// shaders.h includes my math.h function pointers, Rotating and color setting
/// Rasterizor.h include shaders.h contains the drawing routine
/// </summary>


int main()
{
	XTime timer;
	timer.Restart();
	 Vertex OriginalLine[2];
	//Original values
	OriginalLine[0].position.x = 0;
	OriginalLine[0].position.z = 0;
	OriginalLine[1].position.x = 0.5;
	OriginalLine[1].position.z = 0;

#pragma region Grid

	std::vector<Vertex> verticals;
	float xstart = -0.5;
	float spacing = 0.1f;
	for (size_t i = 0; i < 11; i++)
	{
		Vertex v1;
		Vertex v2;

		v1.position.x = xstart;
		v1.position.z = 0.5;
		v2.position.x = xstart;
		v2.position.z = -0.5;
		v1.position.y = 0;
		v2.position.y = 0;
		v1.position.w = 1;
		v2.position.w = 1;
		verticals.push_back(v1);
		verticals.push_back(v2);

		xstart += spacing;
	}

	std::vector<Vertex> horizontals;
	float ystart = -0.5;
	for (size_t i = 0; i < 11; i++)
	{
		Vertex v1;
		Vertex v2;

		v1.position.x = 0.5;
		v1.position.z = ystart;
		v2.position.x = -0.5;
		v2.position.z = ystart;
		v1.position.y = 0;
		v2.position.y = 0;
		v1.position.w = 1;
		v2.position.w = 1;
		horizontals.push_back(v1);
		horizontals.push_back(v2);

		ystart += spacing;
	}
#pragma endregion

#pragma region Cube Creation

	Vertex topLeft;
	topLeft.u = 0;
	topLeft.v = 0;

	Vertex topRight;
	topRight.u = 1;
	topRight.v = 0;

	Vertex bottomLeft;
	bottomLeft.u = 0;
	bottomLeft.v = 1;

	Vertex bottomRight;
	bottomRight.u = 1;
	bottomRight.v = 1;

	

	Vertex Cube[36] =
	{
		{-0.25, 0.25, -0.25, 1}, //A front top left [0]
		{-0.25, 0.25, 0.25, 1},  //B back top left  [1]
		{0.25, 0.25, 0.25, 1},   //C back top right [2]
		{0.25, 0.25, -0.25, 1},  //D front top right [3]
		{0.25, -0.25, -0.25, 1}, //E front bottom right [4]
		{0.25, -0.25, 0.25, 1},  //F back bottom right [5]
		{-0.25, -0.25, 0.25, 1}, //G back bottom left [6]
		{-0.25, -0.25, -0.25, 1}, //H front bottom left [7]	
	};							
								
#pragma endregion

	Vector4 NTL = { -0.25, 0.25, -0.25, 1 };
	Vector4 NTR = { 0.25, 0.25, -0.25, 1 };
	Vector4 NBL = { -0.25, -0.25, -0.25, 1 };
	Vector4 NBR = { 0.25, -0.25, -0.25, 1 };
	Vector4 FTL = { -0.25, 0.25, 0.25, 1 };
	Vector4 FTR = { 0.25, 0.25, 0.25, 1 };
	Vector4 FBL = { -0.25, -0.25, 0.25, 1 };
	Vector4 FBR = { 0.25, -0.25, 0.25, 1 };

	float TL[2] = {0,0};
	float TR[2] = {1,0};
	float BL[2] = {0,1};
	float BR[2] = {1,1};


	Vertex Cube2[36] =
	{
		//Front square
		{NTL, 0x00FF0000, TL[0], TL[1]},
		{NTR, 0x00FF0000, TR[0],TR[1]},
		{NBR, 0x00FF0000, BR[0],BR[1]},
		{NTL, 0x00FF0000, TL[0],TL[1]},
		{NBL, 0x00FF0000, BL[0],BL[1]},
		{NBR, 0x00FF0000, BR[0],BR[1]},

		//Right square
		{NTR, 0x00FF0000, TL[0],TL[1]},
		{FTR, 0x00FF0000, TR[0],TR[1]},
		{FBR, 0x00FF0000, BR[0],BR[1]},
		{NTR, 0x00FF0000, TL[0],TL[1]},
		{NBR, 0x00FF0000, BL[0],BL[1]},
		{FBR, 0x00FF0000, BR[0],BR[1]},

		//Back sqaure
		{FTR, 0x00FF0000, TL[0],TL[1]},
		{FTL, 0x00FF0000, TR[0],TR[1]},
		{FBL, 0x00FF0000, BR[0],BR[1]},
		{FTR, 0x00FF0000, TL[0],TL[1]},
		{FBR, 0x00FF0000, BL[0],BL[1]},
		{FBL, 0x00FF0000, BR[0],BR[1]},


		//Left square
		{FTL, 0x00FF0000, TL[0],TL[1]},
		{NTL, 0x00FF0000, TR[0],TR[1]},
		{NBL, 0x00FF0000, BR[0],BR[1]},
		{FTL, 0x00FF0000, TL[0],TL[1]},
		{FBL, 0x00FF0000, BL[0],BL[1]},
		{NBL, 0x00FF0000, BR[0],BR[1]},

		//Top square
		{FTL, 0x00FF0000, TL[0],TL[1]},
		{FTR, 0x00FF0000, TR[0],TR[1]},
		{NTR, 0x00FF0000, BR[0],BR[1]},
		{FTL, 0x00FF0000, TL[0],TL[1]},
		{NTL, 0x00FF0000, BL[0],BL[1]},
		{NTR, 0x00FF0000, BR[0],BR[1]},

		//Bottom square
		{NBL, 0x00FF0000, TL[0],TL[1]},
		{NBR, 0x00FF0000, TR[0],TR[1]},
		{FBR, 0x00FF0000, BR[0],BR[1]},
		{NBL, 0x00FF0000, TL[0],TL[1]},
		{FBL, 0x00FF0000, BL[0],BL[1]},
		{FBR, 0x00FF0000, BR[0],BR[1]},

	};

	Matrix4x4 wGrid = Identity();
	Matrix4x4 Rotation = CreateRotationX(-18);
	Matrix4x4 Translation = CreateTranslation(0, 0.0f, -1.0f);
	Matrix4x4 Camera = Matrix4x4MultiMatrix4x4(Translation, Rotation);

	SV_ViewMatrix = FastInverse(Camera);

	//world matrix = cube times rotation 
	//Once I get the cube to move back it will look like it is on top of the grid
	//FOV = 90
	// Aspect Ratio = 1
	// Near Plane is at 0.1
	// Far Plane is at 10
#pragma region ProjectionMatrix
	SV_PorjectionMatrix.rows[0].x = (float)XSCALE; 
	SV_PorjectionMatrix.rows[0].y = 0;
	SV_PorjectionMatrix.rows[0].z = 0;
	SV_PorjectionMatrix.rows[0].w = 0;
	SV_PorjectionMatrix.rows[1].x = 0;
	SV_PorjectionMatrix.rows[1].y = (float)YSCALE;
	SV_PorjectionMatrix.rows[1].z = 0;
	SV_PorjectionMatrix.rows[1].w = 0;
	SV_PorjectionMatrix.rows[2].x = 0;
	SV_PorjectionMatrix.rows[2].y = 0;
	SV_PorjectionMatrix.rows[2].z = FAR_PLANE / (FAR_PLANE - NEAR_PLANE);
	SV_PorjectionMatrix.rows[2].w = 1;
	SV_PorjectionMatrix.rows[3].x = 0;
	SV_PorjectionMatrix.rows[3].y = 0;
	SV_PorjectionMatrix.rows[3].z = -(FAR_PLANE * NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
	SV_PorjectionMatrix.rows[3].w = 0;
#pragma endregion
	

	RS_Initialize("Kevin Blackmon", SCREEN_WIDTH, SCREEN_HEIGHT);
	while (RS_Update(pixelArray, SCREEN_PIXELS))
	{
		ClearColor(0x00000000);
		timer.Signal();
		VertexShader = VS_World;
		PixelShader = PS_White;
		SV_WorldMatrix = wGrid;
		for (size_t i = 0; i < 22; i += 2)
		{
			DrawLine(verticals[i], verticals[i + 1]);
		}
		for (size_t i = 0; i < 22; i += 2)
		{
			DrawLine(horizontals[i], horizontals[i + 1]);
		}
		Matrix4x4 cubeTranslation = CreateTranslation(0, 0.25, 0);
		//(float)timer.TotalTime() * 100
		Matrix4x4 cubeRotation = CreateRotationY((float)timer.TotalTime() * 100);
		Matrix4x4 wCube = Matrix4x4MultiMatrix4x4(cubeTranslation, cubeRotation);
		SV_WorldMatrix = wCube;
		#pragma region Cube
		//PixelShader = PS_White;
		PixelShader = PS_TexelToPixel;
		//Front square
		FillTriangle(Cube2[0], Cube2[1], Cube2[2], 0x00FF0000);
		FillTriangle(Cube2[3], Cube2[4], Cube2[5], 0x00FF0000);

		//Right square
		FillTriangle(Cube2[6], Cube2[7], Cube2[8], 0x009504F8);
		FillTriangle(Cube2[9], Cube2[10], Cube2[11], 0x009504F8);
		
		//Left square
		FillTriangle(Cube2[18], Cube2[19], Cube2[20], 0x0000FF00);
		FillTriangle(Cube2[21], Cube2[22], Cube2[23], 0x0000FF00);
		
		//Back sqaure
		FillTriangle(Cube2[12], Cube2[13], Cube2[14], 0x000500FF);
		FillTriangle(Cube2[15], Cube2[16], Cube2[17], 0x000500FF);

		// Bottom square
		FillTriangle(Cube2[30], Cube2[31], Cube2[32], 0x00FFE400);
		FillTriangle(Cube2[33], Cube2[34], Cube2[35], 0x00FFE400);
		
		//Top square
		FillTriangle(Cube2[24], Cube2[25], Cube2[26], 0xFF9300);
		FillTriangle(Cube2[27], Cube2[28], Cube2[29], 0xFF9300);
		#pragma endregion
	}
	RS_Shutdown();
}