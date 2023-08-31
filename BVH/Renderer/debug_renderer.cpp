#include "debug_renderer.h"
#include <array>
#include <vector>

// Anonymous namespace
namespace
{
	// Declarations in an anonymous namespace are global BUT only have internal linkage.
	// In other words, these variables are global but are only visible in this source file.

	// Maximum number of debug lines at one time (i.e: Capacity)
	constexpr size_t MAX_LINE_VERTS = 4096 * 150;

	// CPU-side buffer of debug-line verts
	// Copied to the GPU and reset every frame.
	size_t line_vert_count = 0;
	std::array< end::colored_vertex, MAX_LINE_VERTS> line_verts;
	
}

namespace end
{
	namespace debug_renderer
	{
		//TODO Once you finish this file correctly, you should see a green checkmark when you run the game.
		void add_line(float3 point_a, float3 point_b, float4 color_a, float4 color_b)
		{
			//TODO Add points to debug_verts, increments debug_vert_count
			colored_vertex temp1;
			temp1.pos = point_a;
			temp1.color = color_a;

			colored_vertex temp2;
			temp2.pos = point_b;
			temp2.color = color_b;


			if (line_vert_count < MAX_LINE_VERTS)
			{
				line_verts[line_vert_count] = temp1;
				line_vert_count++;
				line_verts[line_vert_count] = temp2;
				line_vert_count++;
			}

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
			add_line(NTL, NTR, color);
			add_line(NTR, NBR, color);
			add_line(NBR, NBL, color);
			add_line(NBL, NTL, color);

			//Far
			add_line(FTL, FTR, color);
			add_line(FTR, FBR, color);
			add_line(FBR, FBL, color);
			add_line(FBL, FTL, color);

			//Left
			add_line(FTL, NTL, color);
			add_line(NBL, FBL, color);

			//Right
			add_line(FTR, NTR, color);
			add_line(FBR, NBR, color);
		}

		void clear_lines()
		{
			//TODO Resets debug_vert_count to 0
			line_vert_count = 0;
		}

		const colored_vertex* get_line_verts()
		{
			//TODO Returns the line vert array pointer
			return &line_verts[0];
		}

		size_t get_line_vert_count()
		{
			//TODO Returns how many vertices there are now
			return line_vert_count;
		}

		size_t get_line_vert_capacity()
		{
			//TODO returns the maximum size the line vert array
			return line_verts.size();
		}
	}
}