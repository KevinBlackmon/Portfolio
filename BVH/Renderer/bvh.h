
#include <cstdint>
#include <cassert>
#include <vector>
#include "math_types.h"
#include "debug_renderer.h"
#include<algorithm>

//aabb_t{ float3 min; float3 max; };

namespace end
{
	// bvh_node_t
	//
	// BVH will be stored as a vector/array of this type
	// A node will always be at a higher index/address than its parent
	class bvh_node_t
	{
	public:
		// TODO: This constructor is the only function for you to implement in this file.
		bvh_node_t(bvh_node_t* root, uint32_t left_index, uint32_t right_index)
		{
			_left = left_index;
			_right = right_index;
			//TODO The root pointer is the array of the entire bvh
			//Build the aabb that encapsulates the left and right's aabb's
			_aabb = buildAABB(root[left_index].aabb(), root[right_index].aabb());
		}

		bvh_node_t(const aabb_t& bounds, uint32_t id) : _aabb{ bounds }, _id{ id } {}

		bvh_node_t() = default;
		bvh_node_t(const bvh_node_t&) = default;

		aabb_t buildAABB(aabb_t aabb1, aabb_t aabb2)
		{
			aabb_t rootAABB;

			// setting the max                                 true          false
			rootAABB.max.x = (aabb1.max.x >= aabb2.max.x) ? aabb1.max.x : aabb2.max.x;
			rootAABB.max.y = (aabb1.max.y >= aabb2.max.y) ? aabb1.max.y : aabb2.max.y;
			rootAABB.max.z = (aabb1.max.z >= aabb2.max.z) ? aabb1.max.z : aabb2.max.z;

			rootAABB.min.x = (aabb1.min.x <= aabb2.min.x) ? aabb1.min.x : aabb2.min.x;
			rootAABB.min.y = (aabb1.min.y <= aabb2.min.y) ? aabb1.min.y : aabb2.min.y;
			rootAABB.min.z = (aabb1.min.z <= aabb2.min.z) ? aabb1.min.z : aabb2.min.z;

			return rootAABB;
		}



		// Root must be at [0], so parent index must be invalid
		inline bool is_root()const { return _parent == UINT32_MAX; }

		inline bool is_branch()const { return _is_branch; }

		inline bool is_leaf()const { return !is_branch(); }

		inline uint32_t element_id()const
		{
			assert(is_leaf());
			return _id;
		}

		inline uint32_t& left()
		{
			//assert(is_branch());
			return _left;
		}

		inline uint32_t left()const
		{
			assert(is_branch());
			return _left;
		}

		inline uint32_t& right()
		{
			//assert(is_branch());
			return _right;
		}

		inline uint32_t right()const
		{
			assert(is_branch());
			return _right;
		}

		inline uint32_t parent()const
		{
			//assert(!is_root());
			return _parent;
		}

		uint32_t& parent()
		{
			//assert(!is_root());
			return _parent;
		}

		aabb_t& aabb()
		{
			return _aabb;
		}

		const aabb_t& aabb()const
		{
			return _aabb;
		}

	public:

		// Indices for connected nodes
		uint32_t _parent = UINT32_MAX;

		// Index for left child.
		// Branches must have two children.
		// If "this" is a leaf, _left/_is_branch will be 0.
		union
		{
			uint32_t _left = 0;
			uint32_t _is_branch;
		};

		// Index for right child.
		// Branches must have two children.
		// If "this" is a leaf, _right/_id stores the element id.
		union
		{
			uint32_t _right = 0;
			uint32_t _id;
		};

		// AABB for this node
		aabb_t _aabb;
	};

	struct bounding_volume_hierarchy_t
	{
		std::vector<bvh_node_t> bvh;

		inline bvh_node_t& node_at(uint32_t i) { return bvh[i]; }

		inline size_t node_count()const { return bvh.size(); }

		static float cost(const bvh_node_t& a, const bvh_node_t& b)
		{
			aabb_t aabb1 = a.aabb();
			aabb_t aabb2 = b.aabb();

			//Calculated center points
			float3 Center1 = (aabb1.max + aabb1.min) * 0.5f;
			float3 Center2 = (aabb2.max + aabb2.min) * 0.5f;

			return abs(Center1.x - Center2.x) + abs(Center1.y - Center2.y) + abs(Center1.z - Center2.z);
		}

		float Max(float a, float b)
		{
			return (a > b) ? a : b;
		}

		float Min(float a, float b)
		{
			return (a < b) ? a : b;
		}

		aabb_t buildAABB(Triangle _triangle)
		{
			aabb_t rootAABB;

			// setting the max                                 true          false
			float Xmax = Max(_triangle.alpha.x, Max(_triangle.beta.x, _triangle.gamma.x));
			float Ymax = Max(_triangle.alpha.y, Max(_triangle.beta.y, _triangle.gamma.y));
			float Zmax = Max(_triangle.alpha.z, Max(_triangle.beta.z, _triangle.gamma.z));

			float Xmin = Min(_triangle.alpha.x, Min(_triangle.beta.x, _triangle.gamma.x));
			float Ymin = Min(_triangle.alpha.y, Min(_triangle.beta.y, _triangle.gamma.y));
			float Zmin = Min(_triangle.alpha.z, Min(_triangle.beta.z, _triangle.gamma.z));

			if (abs(Ymax - Ymin) <= 0.01f)
				Ymax += 0.01f;

			rootAABB.max = { Xmax, Ymax, Zmax };
			rootAABB.min = { Xmin, Ymin, Zmin };

			return rootAABB;
		}

		//TODO
		//You will need to create a traversal function to render the aabb's as they collide on the way down
		//You could create a callback function as well and that function does the collision tests and drawws the aabb lines
		//a recursive depth-first function could work



		// Add an aabb/element_id pair to the bvh
		void insert(const aabb_t& aabb, uint32_t element_id)
		{
			//TODO
			//create a bvh node using the passed in parameters(do not call new)
			bvh_node_t bvhNode(aabb, element_id);
			bvhNode.parent() = 0;

			//TODO
			//if its the first node, it becomes the root. So just push it into bvh vector, then return
			if (bvh.size() == 0)
			{
				bvh.push_back(bvhNode);
				return;
			}
			//TODO
			//start at index 0 of the bvh (root)
			//while the current node is a branch, 
			//Modify this node's aabb that encapsulates the current node, and the aabb that was passed in
			//figure out if you are going with the left or right child
			//change your index to be the one you have chosen.
			int index = 0;
			while (bvh[index].is_branch())
			{
				bvh[index].aabb() = bvh[index].buildAABB(bvh[index].aabb(), bvhNode.aabb());

				//Get the cost of the left and right and whichever is lower that is the way to go
				float leftCost = cost(bvh[bvh[index].left()], bvhNode);
				float rightCost = cost(bvh[bvh[index].right()], bvhNode);

				if (leftCost < rightCost)
					index = bvh[index].left();
				else
					index = bvh[index].right();


			}


			//TODO
			//Once you have left that while loop, you now hold onto a leaf node index where we will add the node to
			//the 2 new nodes' indices(left and right child) will be the newly created indices once you push back twice on the bvh vector
			//the current node (who is now a branch) needs to be sized to fit the two new nodes(left and right, remember don't need to call new).
			//set the parents of these two nodes
			int left_index = bvh.size();
			int right_index = bvh.size() + 1;

			bvh.push_back(bvhNode);
			bvh.push_back(bvh[index]);

			bvh[index]._aabb = bvh[index].buildAABB(bvh[index].aabb(), bvhNode.aabb());
			bvh[index]._left = left_index;
			bvh[index]._right = right_index;
			bvh[left_index].parent() = bvh[right_index].parent() = index;
		}
	};

	// Declares a short-hand alias
	using bvh_t = bounding_volume_hierarchy_t;
}