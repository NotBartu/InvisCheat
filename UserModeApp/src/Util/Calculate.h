#pragma once

// View Matrix Struct

struct ViewMatrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

// Screen

Vector3 world_to_screen(Vector3* v, ViewMatrix_t view_matrix);
bool is_in_bounds(const Vector3& pos, int width, int heigh);

// Bones

inline std::vector<std::pair<std::string, std::string>> BoneConnections = {
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

Vector3 ReadHead(const HANDLE driver_handle, const std::uintptr_t BoneArray, ViewMatrix_t view_matrix);
CBones ReadBones(const HANDLE driver_handle, const std::uintptr_t BoneArray, ViewMatrix_t view_matrix);