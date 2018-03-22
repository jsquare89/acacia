#include "stdafx.h"
#include "OBJParser.h"
#include <sstream>
#include <fstream>

VertexBufferObject OBJParser::getVBODatafromOBJ(const char * filename)
{
	VertexBufferObject VBO;
	OBJData objData;
	scanObjFileIntoObjData(getOBJstring(filename).c_str(), objData);
	VBO.populateData(objData);
	return VBO;
}

OBJParser::OBJParser()
{
}


OBJParser::~OBJParser()
{
}

std::string OBJParser::getOBJstring(const char * filename)
{
	std::string filepath = "res/meshes/";
	filepath.append(filename);
	filepath.append(".obj");
	return filepath;
}

void OBJParser::scanObjFileIntoObjData(const char * filepath, OBJData &objData)
{
	std::ifstream stream(filepath, std::ios::binary);
	if (!stream)
	{
		printf("LoadOBJ error : could not open file");
		return;
	}

	std::string line;
	while (std::getline(stream, line))
	{
		scanLineIntoObjData(line, objData);
	}
	stream.close();
}

void OBJParser::scanLineIntoObjData(std::string &line, OBJData & objData)
{
	std::stringstream strStream(line);
	const char* buf = line.c_str();

	if (line.size() > 0)
	{
		std::string buftemp;
		strStream >> buftemp;

		if (buftemp == "#")
		{
			//do nothing
		}
		else if (buftemp == "mtllib")
		{
			//do nothing
		}
		else if (buftemp == "v")
		{
			scanVertexIntoObjData(line, objData);
		}
		else if (buftemp == "vt")
		{
			scanUVIntoObjData(line, objData);
		}
		else if (buftemp == "vn")
		{
			scanNormalIntoObjData(line, objData);
		}
		else if (buftemp == "f")
		{
			scanFaceIntoObjData(line, objData);
		}

	}
}

void OBJParser::scanVertexIntoObjData(std::string &line, OBJData &objData)
{
	glm::vec3 temp3DPoint;
	sscanf_s(&line[2], "%f%f%f", &temp3DPoint.x, &temp3DPoint.y, &temp3DPoint.z);
	objData.tempData.vertices.push_back(temp3DPoint);
}

void OBJParser::scanNormalIntoObjData(std::string &line, OBJData &objData)
{
	glm::vec3 temp3DPoint;
	sscanf_s(&line[2], "%f%f%f", &temp3DPoint.x, &temp3DPoint.y, &temp3DPoint.z);
	objData.tempData.normals.push_back(temp3DPoint);
}

void OBJParser::scanUVIntoObjData(std::string &line, OBJData &objData)
{
	glm::vec2 temp2DPoint;
	sscanf_s(&line[2], "%f%f", &temp2DPoint.x, &temp2DPoint.y);
	temp2DPoint.y = 1.0f - temp2DPoint.y;
	objData.tempData.uvs.push_back(temp2DPoint);
}

void OBJParser::scanFaceIntoObjData(std::string &line, OBJData &objData)
{
	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	sscanf_s(&line[2], "%i/%i/%i %i/%i/%i %i/%i/%i", &vertexIndex[0],
		&uvIndex[0],
		&normalIndex[0],
		&vertexIndex[1],
		&uvIndex[1],
		&normalIndex[1],
		&vertexIndex[2],
		&uvIndex[2],
		&normalIndex[2]);
	objData.faceData.vertexIndices.push_back(--vertexIndex[0]);
	objData.faceData.vertexIndices.push_back(--vertexIndex[1]);
	objData.faceData.vertexIndices.push_back(--vertexIndex[2]);
	objData.faceData.uvIndices.push_back(--uvIndex[0]);
	objData.faceData.uvIndices.push_back(--uvIndex[1]);
	objData.faceData.uvIndices.push_back(--uvIndex[2]);
	objData.faceData.normalIndices.push_back(--normalIndex[0]);
	objData.faceData.normalIndices.push_back(--normalIndex[1]);
	objData.faceData.normalIndices.push_back(--normalIndex[2]);
}
