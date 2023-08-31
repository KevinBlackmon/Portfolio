#pragma once
#include <memory>
#include "view.h"
#include <vector>

#define FSGD_END_USE_D3D

namespace end
{
	// APIs/Platforms have their own types for representing a handle to a 'window'
	// They will generally all fit in the 8-bytes of a void*.
	// HWND is actually just a typedef/alias for a void*.
	using native_handle_type = void*;

	// Interface to the renderer
	class renderer_t
	{
	public:

		renderer_t(native_handle_type window_handle);
		//renderer_t(renderer_t&& other);

		~renderer_t();


		void draw();

		void addverts(std::vector<Terrian_vertex> terVert);

		void addTriangles(std::vector<Terrian_vertex> terVert,std::vector<end::Triangle>& triangles);

		view_t default_view;
		std::vector<end::Terrian_vertex> terVect;
		std::vector<end::Triangle> triangles;

		struct impl_t;
	
	private:

		// PImpl idiom ("Pointer to implementation")

		// 'impl' will define the implementation for the renderer elsewhere

		// Pointer to the implementation
		impl_t* p_impl = nullptr;
	};

	// The following types just defines scopes for enum values.
	// The enum values can be used as indices in arrays.
	// These enum values can be added to as needed.

	struct VIEWPORT {
		enum { DEFAULT = 0, COUNT };
	};

	struct CONSTANT_BUFFER {
		enum { MVP = 0, COUNT };
	};

	struct VERTEX_SHADER {
		enum { BUFFERLESS_CUBE = 0, COLORED_VERTEX, TERRAIN, COUNT };
	};

	struct PIXEL_SHADER {
		enum { BUFFERLESS_CUBE = 0, COLORED_VERTEX, TERRAIN, COUNT };
	};

	struct VIEW_RENDER_TARGET {
		enum { DEFAULT = 0, COUNT };
	};

	struct INDEX_BUFFER {
		enum { DEFAULT = 0, COUNT };
	};

	struct INPUT_LAYOUT {
		enum { COLORED_VERTEX = 0, TERRAIN, COUNT };
	};

	struct STATE_RASTERIZER {
		enum { DEFAULT = 0, WIREFRAME, COUNT };
	};

	struct VIEW_DEPTH_STENCIL {
		enum { DEFAULT = 0, COUNT };
	};

	struct STATE_DEPTH_STENCIL {
		enum { DEFAULT = 0, COUNT };
	};

	struct VERTEX_BUFFER {
		enum { COLORED_VERTEX = 0, TERRAIN, COUNT };
	};

	/* Add more as needed...
	enum STATE_SAMPLER{ DEFAULT = 0, COUNT };

	enum STATE_BLEND{ DEFAULT = 0, COUNT };
	*/
}