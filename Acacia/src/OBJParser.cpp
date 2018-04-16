#include "stdafx.h"
#include "OBJParser.h"
#include <sstream>
#include <fstream>

VertexBufferObject OBJParser::getVBODatafromOBJ(const char * ObjFilename)
{
	VertexBufferObject VBO;
	OBJData objData;
	scanObjFileIntoObjData(getOBJstring(ObjFilename).c_str(), objData);
	VBO.populateData(objData);
	return VBO;
}

ModelData OBJParser::getModelData(const char * ObjFilename)
{
	ModelData model;
	OBJData obj;
	scanObjFileIntoObjData(getOBJstring(ObjFilename).c_str(), obj);
	model = getModelDatafromOBJData(obj);
	return model;
}

ModelData OBJParser::getModelDatafromOBJData(const OBJData &obj)
{
	ModelData model;
	for (unsigned int i = 0; i < obj.faceData.vertexIndices.size(); i++)
	{
		glm::vec2 texcoord(obj.tempData.uvs[obj.faceData.uvIndices[i]]);
		glm::vec3 normal(obj.tempData.normals[obj.faceData.normalIndices[i]]);
		model.texcoords.push_back(texcoord.x);
		model.texcoords.push_back(texcoord.y);
		model.normals.push_back(normal.x);
		model.normals.push_back(normal.y);
		model.normals.push_back(normal.z);
		model.indices.push_back(obj.faceData.vertexIndices[i]);
	}

	for (unsigned int i = 0; i < obj.tempData.vertices.size(); i++)
	{
		model.positions.push_back(obj.tempData.vertices[i].x);
		model.positions.push_back(obj.tempData.vertices[i].y);
		model.positions.push_back(obj.tempData.vertices[i].z);
	}
	return model;
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

void OBJParser::debugPrintData(const ModelData &data)
{
	std::cout << "Vertices" << std::endl;
	for (unsigned int i = 0; i < data.positions.size(); i++)
	{
		if (i % 3 == 0)
		{
			std::cout << std::endl;
			std::cout << "v ";
		}
		std::cout << data.positions[i] << " ";
	}

	std::cout << "\n\nUVs";
	for (unsigned int i = 0; i < data.texcoords.size(); i++)
	{
		if (i % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << "vt ";
		}
		std::cout << data.texcoords[i] << " ";
	}

	std::cout << "\n\nNormals";
	for (unsigned int i = 0; i < data.normals.size(); i++)
	{
		if (i % 3 == 0)
		{
			std::cout << std::endl;
			std::cout << "vn ";
		}
		std::cout << data.normals[i] << " ";
	}

	
	std::cout << std::endl;
}