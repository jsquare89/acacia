#pragma once

#include "VertexBufferObject.h"


class OBJParser
{
public:
	VertexBufferObject getVBODatafromOBJ(const char *filepath);

	OBJParser();
	~OBJParser();

private:
	std::string OBJParser::getOBJstring(const char * filename);
	void scanObjFileIntoObjData(const char * filepath, OBJData &objData);
	void scanLineIntoObjData(std::string &lineBuffer, OBJData & objData);
	void scanVertexIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanNormalIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanUVIntoObjData(std::string &lineBuffer, OBJData &objData);
	void scanFaceIntoObjData(std::string &lineBuffer, OBJData &objData);
};

