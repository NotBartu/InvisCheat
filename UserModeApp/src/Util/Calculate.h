#pragma once

// View Matrix Struct

struct view_matrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

// Screen

Vector3 world_to_screen(Vector3* v, view_matrix_t view_matrix);
bool is_in_bounds(const Vector3& pos, int width, int heigh);

// Bones

class CBones {
public:
	std::map<std::string, Vector3> BonePositions;
};

Vector3 ReadHead(const HANDLE driver_handle, const std::uintptr_t BoneArray, view_matrix_t view_matrix);
CBones ReadBones(const HANDLE driver_handle, const std::uintptr_t BoneArray, view_matrix_t view_matrix);