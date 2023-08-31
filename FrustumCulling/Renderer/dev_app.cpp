#include "dev_app.h"
#include "math_types.h"
#include "debug_renderer.h"
#include "frustum_culling.h"
#include <iostream>
#include <DirectXMath.h>
#include <Windows.h>
#include "frustum_culling.h"
#include <stdlib.h>   
#include <time.h>     
using namespace DirectX;
//TODO include debug_renderer.h and pools.h and anything else you might need here

namespace end
{
	double delta_time = 0.0;
	end::sorted_pool_t<particle, 512> Emitter;
	end::pool_t<particle, 2048> Pool;
	end::sorted_pool_t<int, 512> redEmitter;
	end::sorted_pool_t<int, 512> greenEmitter;
	end::sorted_pool_t<int, 512> blueEmitter;
	end::sorted_pool_t<int, 512> yellowEmitter;
	dev_app_t dev;
	frustum_t frustum;
	aabb_t aabb;

	const int aabb_count = 5;

	aabb_t aabbs[10];



	float gravity = 9.8f;
	float deltaColor = 0.0f;
	float deltaRotate = 0.0f;
	float speed = 2.0f;
	const float CamSpeed = 3;
	int drawn = 0;

	float XprevPos = 0.0f;
	float YprevPos = 0.0f;

	double dev_app_t::get_delta_time()const
	{
		return delta_time;
	}

	dev_app_t::dev_app_t()
	{
		std::cout << "Log whatever you need here.\n"; // Don’t forget to include <iostream>
	}

	double calc_delta_time()
	{
		static std::chrono::time_point<std::chrono::high_resolution_clock> last_time = std::chrono::high_resolution_clock::now();

		std::chrono::time_point<std::chrono::high_resolution_clock> new_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = new_time - last_time;
		last_time = new_time;

		return min(1.0 / 15.0, elapsed_seconds.count());
	}

	float RAND_FLOAT(float min, float max)
	{
		float r = rand() / (float)RAND_MAX;

		return (max - min) * r + min;
	}


	void SortedInit(end::sorted_pool_t<particle, 512>& Emitter, float3 pos, float4 color)
	{
		for (int i = 0; i < 1; i++)
		{
			int sindex = Emitter.alloc();

			if (sindex != -1)
			{
				particle temp;
				temp.pos = pos;
				temp.lifetime = RAND_FLOAT(1, 1.5f);
				temp.color = color;
				temp.velocity = float3(RAND_FLOAT(-2, 2), RAND_FLOAT(8, 10), RAND_FLOAT(-2, 2));

				Emitter[sindex] = temp;
			}
		}

		for (int i = 0; i < Emitter.size(); i++)
		{
			if (Emitter[i].lifetime <= 0)
			{
				Emitter.free(i);
				i--;
			}
			else
			{
				Emitter[i].prev_pos = Emitter[i].pos;
				Emitter[i].velocity += float3(0, -1, 0) * gravity * (float)delta_time;
				Emitter[i].pos += Emitter[i].velocity * (float)delta_time;
				Emitter[i].lifetime -= (float)delta_time;
			}
		}

		for (size_t i = 0; i < Emitter.size(); i++)
		{
			end::debug_renderer::add_line(Emitter[i].prev_pos, Emitter[i].pos, Emitter[i].color);
		}
	}

	void FreeInit(end::pool_t<particle, 2048>& Pool, end::sorted_pool_t<int, 512>& emitter, const float3& pos, const float4& color)
	{
		for (int i = 0; i < 1; i++)
		{
			int findex = Pool.alloc();

			if (findex != -1)
			{
				int sindex = emitter.alloc();
				if (sindex != -1)
				{
					particle temp;
					temp.pos = pos;
					temp.lifetime = RAND_FLOAT(1, 1.5f);
					temp.color = color;
					temp.velocity = float3(RAND_FLOAT(-2, 2), RAND_FLOAT(8, 10), RAND_FLOAT(-2, 2));

					Pool[findex] = temp;
					emitter[sindex] = findex;

				}
				else
					Pool.free(findex);
			}

		}

		for (int i = 0; i < emitter.size(); i++)
		{
			if (Pool[emitter[i]].lifetime <= 0)
			{
				Pool.free(emitter[i]);
				emitter.free(i);
				i--;
			}
			else
			{
				Pool[emitter[i]].prev_pos = Pool[emitter[i]].pos;
				Pool[emitter[i]].velocity += float3(0, -1, 0) * gravity * (float)delta_time;
				Pool[emitter[i]].pos += Pool[emitter[i]].velocity * (float)delta_time;
				Pool[emitter[i]].lifetime -= (float)delta_time;
			}
		}

		for (size_t i = 0; i < emitter.size(); i++)
		{
			end::debug_renderer::add_line(Pool[emitter[i]].prev_pos, Pool[emitter[i]].pos, Pool[emitter[i]].color);
		}
	}

	float4x4 Identity()
	{
		float4x4 matrix = {
			float4(1,0,0,0),
			float4(0,1,0,0),
			float4(0,0,1,0),
			float4(0,0,0,1)
		};
		return matrix;
	}


	void LocalTranslateX(float4x4& matrix, float x)
	{
		float3 tempVec = matrix[0].xyz;
		tempVec *= x;

		matrix[3].xyz += tempVec;
	}

	void LocalTranslateY(float4x4& matrix, float y)
	{
		float3 tempVec = matrix[1].xyz;
		tempVec *= y;

		matrix[3].xyz += tempVec;
	}

	void LocalTranslateZ(float4x4& matrix, float z)
	{
		float3 tempVec = matrix[2].xyz;
		tempVec *= z;

		matrix[3].xyz += tempVec;
	}

	void RotateY(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationY(radians);
		matrix = (float4x4&)m;

		matrix[3] = pos;
	}

	void RotateX(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationX(radians);
		matrix = (float4x4&)m;

		matrix[3] = pos;
	}

	void RotateAndMultiplyX(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationX(radians);
		matrix = (float4x4&)XMMatrixMultiply((XMMATRIX&)m, (XMMATRIX&)matrix);
		matrix[3] = pos;
	}

	void RotateAndMultiplyY(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationY(radians);
		matrix = (float4x4&)XMMatrixMultiply((XMMATRIX&)m, (XMMATRIX&)matrix);
		matrix[3] = pos;
	}

	void RotateAndMultiplyZ(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationZ(radians);
		matrix = (float4x4&)XMMatrixMultiply((XMMATRIX&)m, (XMMATRIX&)matrix);
		matrix[3] = pos;
	}


	void RotateZ(float4x4& matrix, float radians)
	{
		float4 pos = matrix[3];
		XMMATRIX m = XMMatrixRotationZ(radians);
		matrix = (float4x4&)m;

		matrix[3] = pos;
	}

	void DrawAxis(float4x4 matrix, float scale)
	{
		float3 start = matrix[3].xyz;

		float3 xend = start + (matrix[0].xyz * scale);
		float3 yend = start + (matrix[1].xyz * scale);
		float3 zend = start + (matrix[2].xyz * scale);

		end::debug_renderer::add_line(start, xend, float4(1, 0, 0, 1));
		end::debug_renderer::add_line(start, yend, float4(0, 1, 0, 1));
		end::debug_renderer::add_line(start, zend, float4(0, 0, 1, 1));
	}

	//Eye is the position of, at is the target you are looking at
	void LookAt(float3 _eye, float3 _up, float3 _at, float4x4& _outMatrix)
	{
		float3 camForward;		//zaxis
		float3 camRight;		//xaxis
		float3 camUp;			//yaxis

		//camForward = targetPosition - eyePosition 
		camForward = _at - _eye;

		//Normalized the camForward
		camForward = normalize(camForward);

		//Cross the up and camForward
		camRight = cross(_up, camForward);

		//Normalized the camRight
		camRight = normalize(camRight);

		//Cross the up and camForward
		camUp = cross(camForward, camRight);

		//Outing the reference 
		_outMatrix[0].xyz = camRight;
		_outMatrix[1].xyz = camUp;
		_outMatrix[2].xyz = camForward;
		_outMatrix[3].xyz = _eye;
	}

	void Orthonormailze(float3 _eye, float3 _up, float4x4& _outMatrix)
	{
		float3 camForward = normalize(_outMatrix[2].xyz);		//zaxis
		float3 camRight;		//xaxis
		float3 camUp;			//yaxis

		//camForward = targetPosition - eyePosition 
		//camForward = _at - _eye;

		//Normalized the camForward
		//camForward = normalize(camForward);

		//Cross the up and camForward
		camRight = cross(_up, camForward);

		//Normalized the camRight
		camRight = normalize(camRight);

		//Cross the up and camForward
		camUp = cross(camForward, camRight);

		//Outing the reference 
		_outMatrix[0].xyz = camRight;
		_outMatrix[1].xyz = camUp;
		_outMatrix[2].xyz = camForward;
		_outMatrix[3].xyz = _eye;
	}

	void TurnTo(float4x4& outmatrix, float3 target, float speed)
	{
		float4x4 matrixX = Identity();
		float4x4 matrixY = Identity();
		float3 toTarget = normalize(target - outmatrix[3].xyz);

		float dotY = dot(toTarget, outmatrix[0].xyz);
		float dotX = dot(toTarget, outmatrix[1].xyz);

		//X rotate
		RotateX(matrixX, speed * -dotX);
		(XMMATRIX&)outmatrix = XMMatrixMultiply((XMMATRIX&)matrixX, (XMMATRIX&)outmatrix);

		//Y rotate
		RotateY(matrixY, speed * dotY);
		(XMMATRIX&)outmatrix = XMMatrixMultiply((XMMATRIX&)matrixY, (XMMATRIX&)outmatrix);

		Orthonormailze(outmatrix[3].xyz, { 0,1,0 }, outmatrix);
	}

	void dev_app_t::CameraMovement(float4x4& outMatrix)
	{
		if (keyState['W'])
			LocalTranslateZ(outMatrix, CamSpeed * (float)delta_time);
		if (keyState['S'])
			LocalTranslateZ(outMatrix, -CamSpeed * (float)delta_time);
		if (keyState['A'])
			LocalTranslateX(outMatrix, -CamSpeed * (float)delta_time);
		if (keyState['D'])
			LocalTranslateX(outMatrix, CamSpeed * (float)delta_time);
		if (mouseState[VK_RBUTTON])
		{
			float deltaX = Xpos - XprevPos;
			float deltaY = Ypos - YprevPos;

			RotateAndMultiplyX(outMatrix, deltaY * delta_time);
			RotateAndMultiplyY(outMatrix, deltaX * delta_time);
			Orthonormailze(outMatrix[3].xyz, { 0,1,0 }, outMatrix);
		}
		XprevPos = Xpos;
		YprevPos = Ypos;
	}

	void dev_app_t::Movement(float4x4& outMatrix, float rotateSpeed)
	{
		//37 left
		//38 up
		//39 right
		//40 down
		float3 pos = outMatrix[3].xyz;


		if (keyState[40])
			LocalTranslateZ(outMatrix, -speed * (float)delta_time);
		if (keyState[38])
			LocalTranslateZ(outMatrix, speed * (float)delta_time);
		if (keyState[39])
		{
			deltaRotate += (float)delta_time;
			RotateY(outMatrix, rotateSpeed);
		}
		if (keyState[37])
		{
			deltaRotate -= (float)delta_time;
			RotateY(outMatrix, rotateSpeed);
		}

		if (keyState['O'])
		{
			outMatrix = Identity();
		}
	}

	void Generateaabb(aabb_t& aabb)
	{
		float3 center = { RAND_FLOAT(-7,7), 0, RAND_FLOAT(-7,7) };
		float3 extents = { RAND_FLOAT(1,2), RAND_FLOAT(1,2), RAND_FLOAT(1,2) };

		aabb.min = center - extents;
		aabb.max = center + extents;
	}

	void Drawaabb(aabb_t aabb, float4 color)
	{
		float3 NTR = { aabb.max.x, aabb.max.y, aabb.min.z };
		float3 NTL = { aabb.min.x, aabb.max.y, aabb.min.z };
		float3 NBL = { aabb.min.x, aabb.min.y, aabb.min.z };
		float3 NBR = { aabb.max.x, aabb.min.y, aabb.min.z };
		float3 FTL = { aabb.min.x, aabb.max.y, aabb.max.z };
		float3 FTR = { aabb.max.x, aabb.max.y, aabb.max.z };
		float3 FBR = { aabb.max.x, aabb.min.y, aabb.max.z };
		float3 FBL = { aabb.min.x, aabb.min.y, aabb.max.z };


		//Near
		end::debug_renderer::add_line(NTL, NTR, color);
		end::debug_renderer::add_line(NTR, NBR, color);
		end::debug_renderer::add_line(NBR, NBL, color);
		end::debug_renderer::add_line(NBL, NTL, color);

		//Far
		end::debug_renderer::add_line(FTL, FTR, color);
		end::debug_renderer::add_line(FTR, FBR, color);
		end::debug_renderer::add_line(FBR, FBL, color);
		end::debug_renderer::add_line(FBL, FTL, color);

		//Left
		end::debug_renderer::add_line(FTL, NTL, color);
		end::debug_renderer::add_line(NBL, FBL, color);

		//Right
		end::debug_renderer::add_line(FTR, NTR, color);
		end::debug_renderer::add_line(FBR, NBR, color);
	}

	end::float4x4 Lookat = Identity();
	end::float4x4 Turnto = Identity();
	end::float4x4 Mouselook = Identity();
	end::float4x4 moveMatrix = Identity();



	void dev_app_t::update()
	{
		end::debug_renderer::clear_lines();
		delta_time = calc_delta_time();

		calculate_frustum(frustum, moveMatrix);


		//TODO do you Updates here

		for (int i = 0; i < sizeof(aabbs); i++)
		{
			if (drawn < aabb_count)
			{
				Generateaabb(aabbs[i]);
				drawn++;
			}
			float4 color = aabb_to_frustum(aabbs[i], frustum) ? float4(0, 1, 0, 1) : float4(1, 0, 0, 1);
			Drawaabb(aabbs[i], color);
		}




		deltaColor += (float)delta_time;
		if (deltaColor >= 1)
			deltaColor = 0;

		//Grid
		for (int i = 0; i < 21; i++)
		{
			end::debug_renderer::add_line(float3(-10, 0, -10 + i), float3(10, 0, -10 + i), float4(1, 1, 1, 1));
			end::debug_renderer::add_line(float3(-10 + i, 0, -10), float3(-10 + i, 0, 10), float4(1, 1, 1, 1));
		}

		//Turn to and Look at
		Turnto[3].xyz = { 5,3,0 };

		LookAt({ -5, 3,3 }, { 0,3,0 }, moveMatrix[3].xyz, Lookat);
		TurnTo(Turnto, moveMatrix[3].xyz, (float)delta_time);

		CameraMovement((float4x4&)(*viewMatrix));

		//Move matrix
		Movement(moveMatrix, deltaRotate);

		//Drawing the Axis
		DrawAxis(Lookat, 1);
		DrawAxis(Turnto, 1);
		DrawAxis(moveMatrix, 1);
	}
}
