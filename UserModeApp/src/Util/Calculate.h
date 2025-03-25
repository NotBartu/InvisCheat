#pragma once
#include <map>
#include "Vector.h"
#include "../Hacks/driver.hpp"

// View Matrix Struct

struct view_matrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

// Screen

inline Vector3 world_to_screen(Vector3* v, view_matrix_t view_matrix) {
	float _x = view_matrix[0][0] * v->x + view_matrix[0][1] * v->y + view_matrix[0][2] * v->z + view_matrix[0][3];
	float _y = view_matrix[1][0] * v->x + view_matrix[1][1] * v->y + view_matrix[1][2] * v->z + view_matrix[1][3];

	float w = view_matrix[3][0] * v->x + view_matrix[3][1] * v->y + view_matrix[3][2] * v->z + view_matrix[3][3];

	float inv_w = 1.f / w;
	_x *= inv_w;
	_y *= inv_w;

	float x = 1920 * .5f;
	float y = 1080 * .5f;

	x += 0.5f * _x * 1920 + 0.5f;
	y -= 0.5f * _y * 1080 + 0.5f;

	return { x, y, w };
}

inline bool is_in_bounds(const Vector3& pos, int width, int heigh) {
	return pos.x >= 0 && pos.x <= width && pos.y >= 0 && pos.y <= heigh;
}

// Bones

std::map<std::string, int> BoneMap = {
	{"head", 6},
	{"neck_0", 5},
	{"spine_1", 4},
	{"spine_2", 2},
	{"pelvis", 0},
	{"arm_upper_L", 8},
	{"arm_lower_L", 9},
	{"hand_L", 10},
	{"arm_upper_R", 13},
	{"arm_lower_R", 14},
	{"hand_R", 15},
	{"leg_upper_L", 22},
	{"leg_lower_L", 23},
	{"ankle_L", 24},
	{"leg_upper_R", 25},
	{"leg_lower_R", 26},
	{"ankle_R", 27}
};

std::vector<std::pair<std::string, std::string>> BoneConnections = {
	{"neck_0", "spine_1"},
	{"spine_1", "spine_2"},
	{"spine_2", "pelvis"},
	{"spine_1", "arm_upper_L"},
	{"arm_upper_L", "arm_lower_L"},
	{"arm_lower_L", "hand_L"},
	{"spine_1", "arm_upper_R"},
	{"arm_upper_R", "arm_lower_R"},
	{"arm_lower_R", "hand_R"},
	{"pelvis", "leg_upper_L"},
	{"leg_upper_L", "leg_lower_L"},
	{"leg_lower_L", "ankle_L"},
	{"pelvis", "leg_upper_R"},
	{"leg_upper_R", "leg_lower_R"},
	{"leg_lower_R", "ankle_R"}
};

class CBones {
public:
	std::map<std::string, Vector3> BonePositions;
};

inline Vector3 ReadHead(const HANDLE driver_handle, const std::uintptr_t BoneArray, view_matrix_t view_matrix) {
	const uintptr_t BoneAddress = BoneArray + 6 * 32;
	Vector3 BonePosition = driver::read_memory<Vector3>(driver_handle, BoneAddress);
	const Vector3 BonePosition2D = world_to_screen(&BonePosition, view_matrix);

	return BonePosition2D;
}

inline CBones ReadBones(const HANDLE driver_handle, const std::uintptr_t BoneArray, view_matrix_t view_matrix) {
	int BoneIndex;
	std::uintptr_t BoneAddress;
	Vector3 BonePosition;
	CBones Bones;

	for (const auto & entry : BoneMap) {
		const std::string& boneName = entry.first;
		BoneIndex = entry.second;
		BoneAddress = BoneArray + BoneIndex * 32;
		BonePosition = driver::read_memory<Vector3>(driver_handle, BoneAddress);
		Bones.BonePositions[boneName] = world_to_screen(&BonePosition, view_matrix);
	}

	return Bones;
}