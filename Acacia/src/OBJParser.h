#pragma once

#include "VertexBufferObject.h"

struct ModelData {
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> texcoords;
	std::vector<unsigned int> indices;
};

class OBJParser
{
public:
	VertexBufferObject getVBODatafromOBJ(const char *ObjFilename);
	ModelData getModelData(const char * ObjFilename);
	OBJParser();
	~OBJParser();

private:
	std::string OBJParser::getOBJstring(const char * ObjFilename);
	void scanObjFileIntoObjData(const char * filepath, OBJData &objData);
	void scanLineIntoObjData(std::string &lineBuffer, OBJData & objData);
	void scanVertexIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanNormalIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanUVIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanFaceIntoObjData(std::string &lineBuffer, OBJData &objData);
	ModelData OBJParser::getModelDatafromOBJData(const OBJData& objData);
	void OBJParser::debugPrintData(const ModelData &data);
};

