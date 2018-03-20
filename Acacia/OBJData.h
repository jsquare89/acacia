#pragma once
#include <GL/glew.h>
#include <vector>

struct FaceData {
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;
};

struct TempData {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};

struct OBJData
{
	FaceData faceData;
	TempData tempData;
};