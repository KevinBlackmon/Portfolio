#include "Rasterizer.h"


/// Rotating Cube
/// define.h all defines
/// mymath.h includes defines.h all the math required
/// shaders.h includes my math.h function pointers, Rotating and color setting
/// Rasterizor.h include shaders.h contains the drawing routine
/// </summary>


int main()
{
//#pragma region mathTest
//	Matrix4x4 test;
//	test.rows[0].x = 1;
//	test.rows[0].y = 0;
//	test.rows[0].z = 0;
//	test.rows[0].w = 0;
//	test.rows[1].x = 0;
//	test.rows[1].y = 0.309;
//	test.rows[1].z = 0.951;
//	test.rows[1].w = 0;
//	test.rows[2].x = 0;
//	test.rows[2].y = -0.951;
//	test.rows[2].z = 0.309;
//	test.rows[2].w = 0;
//	test.rows[3].x = 0;
//	test.rows[3].y = 0;
//	test.rows[3].z = 0;
//	test.rows[3].w = 1;
//
//
//	Matrix4x4 temp;
//	temp.rows[0].x = 1;
//	temp.rows[0].y = 0;
//	temp.rows[0].z = 0;
//	temp.rows[0].w = 0;
//	temp.rows[1].x = 0;
//	temp.rows[1].y = 1;
//	temp.rows[1].z = 0;
//	temp.rows[1].w = 0;
//	temp.rows[2].x = 0;
//	temp.rows[2].y = 0;
//	temp.rows[2].z = 1;
//	temp.rows[2].w = 0;
//	temp.rows[3].x = 7;
//	temp.rows[3].y = 8;
//	temp.rows[3].z = 5;
//	temp.rows[3].w = 1;
//
//
//	Matrix4x4 ans = Matrix4x4MultiMatrix4x4(temp, test);
//	Matrix4x4 check = FastInverse(ans);
//#pragma endregion

	XTime timer;
	timer.Restart();
	 Vertex OriginalLine[2];
	//Original values
	OriginalLine[0].position.x = 0;
	OriginalLine[0].position.z = 0;
	OriginalLine[1].position.x = 0.5;
	OriginalLine[1].position.z = 0;


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
		{-0.25, 0.25, -0.25, 1},	//[8][0]
		{-0.25, 0.25, 0.25, 1},		//[9][1]
		{0.25, 0.25, 0.25, 1},		//[10][2]
		{0.25, 0.25, -0.25, 1},		//[11][3]
		{0.25, -0.25, -0.25, 1},	//[12][4]
		{0.25, -0.25, 0.25, 1},		//[13][5]
		{-0.25, -0.25, 0.25, 1},	//[14][6]
		{-0.25, -0.25, -0.25, 1},	//[15][7]
		{-0.25, 0.25, -0.25, 1},	//[16][0]
		{-0.25, 0.25, 0.25, 1},		//[17][1]
		{0.25, 0.25, 0.25, 1},		//[19][2]
		{0.25, 0.25, -0.25, 1},		//[20][3]
		{0.25, -0.25, -0.25, 1},	//[21][4]
		{0.25, -0.25, 0.25, 1},		//[22][5]
		{-0.25, -0.25, 0.25, 1},	//[23][6]
		{-0.25, -0.25, -0.25, 1},	//[24][7]
		{-0.25, 0.25, -0.25, 1},	//[25][0]
		{-0.25, 0.25, 0.25, 1},		//[26][1]
		{0.25, 0.25, 0.25, 1},		//[27][2]
		{0.25, 0.25, -0.25, 1},		//[28][3]
		{0.25, -0.25, -0.25, 1},	//[29][4]
		{0.25, -0.25, 0.25, 1},		//[30][5]
		{-0.25, -0.25, 0.25, 1},	//[31][6]
		{-0.25, -0.25, -0.25, 1},	//[32][7]
	};							
								
	Cube[0].u = topLeft.u;		
	Cube[0].v = topLeft.v;		

	Cube[1].v = topLeft.v;
	Cube[1].u = topLeft.u;

	Cube[2].v = topRight.v;
	Cube[2].u = topRight.u;

	Cube[3].v = topRight.v;
	Cube[3].u = topRight.u;

	Cube[4].v = bottomRight.v;
	Cube[4].u = bottomRight.u;

	Cube[5].v = bottomRight.v;
	Cube[5].u = bottomRight.u;

	Cube[6].v = bottomLeft.v;
	Cube[6].u = bottomLeft.u;

	Cube[7].v = bottomLeft.v;
	Cube[7].u = bottomLeft.u;

	Cube[8].u = topLeft.u;
	Cube[8].v = topLeft.v;

	Cube[9].v = topLeft.v;
	Cube[9].u = topLeft.u;

	Cube[10].v = topRight.v;
	Cube[10].u = topRight.u;

	Cube[11].v = topRight.v;
	Cube[11].u = topRight.u;

	Cube[12].v = bottomRight.v;
	Cube[12].u = bottomRight.u;

	Cube[13].v = bottomRight.v;
	Cube[13].u = bottomRight.u;

	Cube[14].v = bottomLeft.v;
	Cube[14].u = bottomLeft.u;

	Cube[15].v = bottomLeft.v;
	Cube[15].u = bottomLeft.u;

	Cube[16].u = topLeft.u;
	Cube[16].v = topLeft.v;

	Cube[17].v = topLeft.v;
	Cube[17].u = topLeft.u;

	Cube[18].v = topRight.v;
	Cube[18].u = topRight.u;

	Cube[19].v = topRight.v;
	Cube[19].u = topRight.u;

	Cube[20].v = bottomRight.v;
	Cube[20].u = bottomRight.u;
		 
	Cube[21].v = bottomRight.v;
	Cube[21].u = bottomRight.u;
		 
	Cube[23].v = bottomLeft.v;
	Cube[23].u = bottomLeft.u;
		 
	Cube[24].v = bottomLeft.v;
	Cube[24].u = bottomLeft.u;

	Cube[25].u = topLeft.u;
	Cube[25].v = topLeft.v;

	Cube[26].u = topLeft.u;
	Cube[26].v = topLeft.v;

	Cube[27].v = topRight.v;
	Cube[27].u = topRight.u;

	Cube[28].v = topRight.v;
	Cube[28].u = topRight.u;

	Cube[29].v = bottomRight.v;
	Cube[29].u = bottomRight.u;

	Cube[30].v = bottomRight.v;
	Cube[30].u = bottomRight.u;

	Cube[31].v = bottomLeft.v;
	Cube[31].u = bottomLeft.u;

	Cube[32].v = bottomLeft.v;
	Cube[32].u = bottomLeft.u;
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

		/*{{0.25, 0.25, 0.25, 1}, 0x00FF0000, 1,1 },
		{{0.25, -0.25, 0.25, 1}, 0x00FF0000, 1,0 },
		{{0.25, -0.25, -0.25, 1}, 0x00FF0000, 1,1 },
		{{-0.25, -0.25, -0.25, 1}, 0x00FF0000, 0,1 },
		{{-0.25, -0.25, 0.25, 1}, 0x00FF0000, 1,1 },
		{{-0.25, 0.25, 0.25, 1}, 0x00FF0000, 0,1 },*/


	};

	Matrix4x4 wGrid = Identity();
	Matrix4x4 Rotation = CreateRotationX(-18);
	Matrix4x4 Translation = CreateTranslation(0, 0, -1);
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
		PixelShader = PS_White;
		DrawLine(Cube[0], Cube[1]);//A-B Left square
		DrawLine(Cube[7], Cube[0]);//H-A Left square
		DrawLine(Cube[1], Cube[2]);//B-C
		DrawLine(Cube[2], Cube[3]);//C-D
		DrawLine(Cube[3], Cube[0]);//D-A
		DrawLine(Cube[3], Cube[4]);//D-E
		DrawLine(Cube[4], Cube[5]);//E-F
		DrawLine(Cube[5], Cube[6]);//F-G
		DrawLine(Cube[6], Cube[7]);//G-H
		DrawLine(Cube[7], Cube[4]);//H-E
		DrawLine(Cube[5], Cube[2]);//F-C
		DrawLine(Cube[6], Cube[1]);//G-B
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