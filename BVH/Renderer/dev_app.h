#pragma once
//#include <cstdint>
#include <chrono>
#include "math_types.h"
#include "../pools.h"
#include <bitset>
#include "bvh.h"


//struct end::bounding_volume_hierarchy_t;

namespace end
{
	// Simple app class for development and testing purposes
	struct dev_app_t
	{
		void Movement(float4x4& outMatrix, float rotateSpeed);
		void CameraMovement(float4x4& outMatrix);
		void CreateBVH(bounding_volume_hierarchy_t& bvh);
		void LoadTerrain();
		void update();

		dev_app_t();

		double get_delta_time()const;
		std::bitset<256> keyState;
		std::bitset<15> mouseState;

		float Xpos = 0;
		float Ypos = 0;
		float4x4_a* viewMatrix;
		//bounding_volume_hierarchy_t* devBVH;
		std::vector<end::Terrian_vertex> terrainVertsptr;
		std::vector<end::Triangle> trianglesptr;
		bounding_volume_hierarchy_t BVH;
		
	};

	struct particle
	{
		end::float3 pos;
		end::float3 prev_pos;
		end::float4 color;
		end::float3 velocity;
		float lifetime = 0;
		//could add lifetime if you’d like
	};

	struct Emitter
	{
		end::float3 spawn_pos;
		end::float4 spawn_color;
		// indices into the shared_pool 
		end::sorted_pool_t<int16_t, 256> indices;
	};



}