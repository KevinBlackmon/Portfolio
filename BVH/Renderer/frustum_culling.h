#pragma once
#include <math.h>
#include "math_types.h"
#include <array>
#include "view.h"
#include "debug_renderer.h"

// Note: You are free to make adjustments/additions to the declarations provided here.

namespace end
{
	using frustum_t = std::array<plane_t, 6>;

	// Calculates the plane of a triangle from three points.
	plane_t calculate_plane(float3 a, float3 b, float3 c)
	{
		float3 Normal = normalize(cross((c - a), (b - a)));
		
		return plane_t{ Normal, dot(Normal, a)};
	}

	// Calculates a frustum (6 planes) from the input view parameter.
	//
	// Calculate the eight corner points of the frustum. 
	// Use your debug renderer to draw the edges.
	// 
	// Calculate the frustum planes.
	// Use your debug renderer to draw the plane normals as line segments.

	enum Sides
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back
	};

	void calculate_frustum(frustum_t& frustum, const float4x4& view)
	{
		float fov = 3.14 / 3.0f;
		float AR = 16.0f / 9.0f;
		float NearDist = 1;
		float FarDist = 10;
		float nHeight = tan(fov * 0.5f) * NearDist;
		float fHeight = tan(fov * 0.5f) * FarDist;
		float nWidth = nHeight * AR;
		float fWidth = fHeight * AR;


		float3 nCenter = view[3].xyz + view[2].xyz * NearDist;
		float3 fCenter = view[3].xyz + view[2].xyz * FarDist;

		//Near
		float3 NTL = nCenter + view[1].xyz * (nHeight * 0.5f) - view[0].xyz * (nWidth * 0.5f);
		float3 NTR = NTL + view[0].xyz * nWidth;
		float3 NBR = NTR - view[1].xyz * nHeight;
		float3 NBL = NTL - view[1].xyz * nHeight;

		//Far
		float3 FTL = fCenter + view[1].xyz * (fHeight * 0.5f) - view[0].xyz * (fWidth * 0.5f);
		float3 FTR = FTL + view[0].xyz * fWidth;
		float3 FBR = FTR - view[1].xyz * fHeight;
		float3 FBL = FTL - view[1].xyz * fHeight;

		//Calulate the planes
		frustum[Sides::Top] = calculate_plane(NTR, NTL, FTR);
		frustum[Sides::Bottom] = calculate_plane(NBL, NBR, FBR);
		frustum[Sides::Left] = calculate_plane(NBL, FBL, NTL);
		frustum[Sides::Right] = calculate_plane(FBR, NBR, NTR);
		frustum[Sides::Front] = calculate_plane(NBL, NTL, NBR);
		frustum[Sides::Back] = calculate_plane(FBL, FBR, FTL);

		//Calculate the normals
		float3 rCenter = (NTR + NBR + FTR + FBR) * 0.25;
		float3 lCenter = (NTL + NBL + FTL + FBL) * 0.25;
		float3 tCenter = (NTR + NTL + FTR + FTL) * 0.25;
		float3 bCenter = (NBR + NBL + FBR + FBL) * 0.25;
		float3 frontCenter = (NTR + NTL + NBR + NBL) * 0.25;
		float3 backCenter = (FTR + FTL + FBR + FBL) * 0.25;

		//Normals
		end::debug_renderer::add_line(rCenter, rCenter + frustum[Sides::Right].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));
		end::debug_renderer::add_line(lCenter, lCenter + frustum[Sides::Left].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));
		end::debug_renderer::add_line(tCenter, tCenter + frustum[Sides::Top].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));
		end::debug_renderer::add_line(bCenter, bCenter + frustum[Sides::Bottom].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));
		end::debug_renderer::add_line(frontCenter, frontCenter + frustum[Sides::Front].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));
		end::debug_renderer::add_line(backCenter, backCenter + frustum[Sides::Back].normal, float4(1, 1, 1, 1), float4(0, 0, 1, 1));

		//Near
		end::debug_renderer::add_line(NTL, NTR, float4(1,1,1,1));
		end::debug_renderer::add_line(NTL, NBL, float4(1,1,1,1));
		end::debug_renderer::add_line(NBL, NBR, float4(1,1,1,1));
		end::debug_renderer::add_line(NBR, NTR, float4(1,1,1,1));

		//Far
		end::debug_renderer::add_line(FTL, FTR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FTL, FBL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBL, FBR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBR, FTR, float4(1, 1, 1, 1));

		//Top
		end::debug_renderer::add_line(NTL, FTL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FTL, FTR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FTR, NTR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(NTR, NTL, float4(1, 1, 1, 1));

		//Bottom
		end::debug_renderer::add_line(NBL, FBL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBL, FBR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBR, NBR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(NBR, NBL, float4(1, 1, 1, 1));

		//Left Side
		end::debug_renderer::add_line(NTL, FTL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FTL, FBL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBL, NBL, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(NBL, NTL, float4(1, 1, 1, 1));

		//Right Side
		end::debug_renderer::add_line(NTR, FTR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FTR, FBR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(FBR, NBR, float4(1, 1, 1, 1));
		end::debug_renderer::add_line(NBR, NTR, float4(1, 1, 1, 1));
	}

	// Calculates which side of a plane the sphere is on.
	//
	// Returns -1 if the sphere is completely behind the plane.
	// Returns 1 if the sphere is completely in front of the plane.
	// Otherwise returns 0 (Sphere overlaps the plane)
	int classify_sphere_to_plane(const sphere_t& sphere, const plane_t& plane)
	{
		float ans = dot(sphere.center, plane.normal) - plane.offset;
		if (ans  < -sphere.radius)
			return -1;
		else if (ans > sphere.radius)
			return 1;

		return 0;
	}

	// Calculates which side of a plane the aabb is on.
	//
	// Returns -1 if the aabb is completely behind the plane.
	// Returns 1 if the aabb is completely in front of the plane.
	// Otherwise returns 0 (aabb overlaps the plane)
	// MUST BE IMPLEMENTED UsING THE PROJECTED RADIUS TEST
	int classify_aabb_to_plane(const aabb_t& aabb, const plane_t& plane)
	{
		float3 center = (aabb.max + aabb.min) * 0.5f;
		float3 extents = aabb.max - center;

		float absX = abs(plane.normal.x);
		float absY = abs(plane.normal.y);
		float absZ = abs(plane.normal.z);

		float3 absNrm = { absX, absY, absZ };

		return classify_sphere_to_plane(sphere_t{ center,dot(absNrm, extents) }, plane);
	}

	// Determines if the aabb is inside the frustum.
	//
	// Returns false if the aabb is completely behind any plane.
	// Otherwise returns true.
	bool aabb_to_frustum(const aabb_t& aabb, const frustum_t& frustum)
	{
		for (size_t i = 0; i < frustum.size(); i++)
		{
			if (classify_aabb_to_plane(aabb, frustum[i]) < 0)
				return false;
		}
		return true;
	}
}