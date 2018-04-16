#pragma once
#include "OBJParser.h"
class model
{
public:
	model(const ModelData &model);
	~model();

private:
	int vaoID;
	int vertexCount;
};

