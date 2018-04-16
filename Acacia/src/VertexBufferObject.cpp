#include "stdafx.h"
#include "VertexBufferObject.h"


void VertexBufferObject::create(GLenum usage)
{
	id = 0;
	
	if (data.positions.empty())
	{
		printf("Error, no VBO positon data. Cannot create VBO");
		return;
	}

	calculateSize();
	calculateOffset();

	glGenBuffers(1, &id);
	if (id == 0)
	{
		printf("Error, no VBO positon data. Cannot create VBO");
		return;
	}
	else
	{
		bindBuffer(usage);
	}
}


void VertexBufferObject::calculateSize()
{
	size.positions = data.positions.size() * sizeof(glm::vec3);
	if (!data.normals.empty())
		size.normals = data.normals.size() * sizeof(glm::vec3);
	if (!data.positions.empty())
		size.texcoords = data.texcoords.size() * sizeof(glm::vec2);
	if (!data.positions.empty())
		size.tangents = data.tangents.size() * sizeof(glm::vec3);
}

void VertexBufferObject::calculateOffset()
{
	offset.positions = 0;
	offset.normals = offset.positions + size.positions;
	offset.texcoords = offset.normals + size.normals;
	offset.tangents = offset.texcoords + size.texcoords;
}

void VertexBufferObject::bindBuffer(const GLenum &usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size.positions + size.normals + size.texcoords + size.tangents, 0, usage);

	glBufferSubData(GL_ARRAY_BUFFER, offset.positions, size.positions, (const GLvoid*)(&data.positions[0]));
	if (data.normals.size())
		glBufferSubData(GL_ARRAY_BUFFER, offset.normals, size.normals, (const GLvoid*)(&data.normals[0]));
	if (data.texcoords.size())
		glBufferSubData(GL_ARRAY_BUFFER, offset.texcoords, size.texcoords, (const GLvoid*)(&data.texcoords[0]));
	if (data.tangents.size())
		glBufferSubData(GL_ARRAY_BUFFER, offset.tangents, size.tangents, (const GLvoid*)(&data.tangents[0]));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::cout << "VBO Bind Buffer - id=" << id << std::endl;
}


void VertexBufferObject::destroy()
{
	glDeleteBuffers(1, &id);
	id = 0;
	data.positions.clear();
	data.normals.clear();
	data.texcoords.clear();
	data.tangents.clear();
}


void VertexBufferObject::populateData(const OBJData & objData)
{
	for (unsigned int i = 0; i < objData.faceData.vertexIndices.size(); i++)
	{
		//glm::vec3 vertex(objData.tempData.vertices[objData.faceData.vertexIndices[i]]);
		glm::vec2 texcoord(objData.tempData.uvs[objData.faceData.uvIndices[i]]);
		glm::vec3 normal(objData.tempData.normals[objData.faceData.normalIndices[i]]);
		//data.positions.push_back(vertex);
		
		data.indices.push_back(objData.faceData.vertexIndices[i]);
		data.texcoords.push_back(texcoord);
		data.normals.push_back(normal);
		
	}
	
	for (unsigned int i = 0; i < objData.tempData.vertices.size(); i++)
	{
		data.positions.push_back(objData.tempData.vertices[i]);
	}

	// TDO: Remove Debug
	std::cout << "Successfully Populated VBO" << std::endl;
	debugPrintData();
}

void VertexBufferObject::debugPrintData()
{
	std::cout << "Vertices" << std::endl;
	for each (glm::vec3 vertex in data.positions)
	{
		std::cout << glm::to_string(vertex) << std::endl;
	}
	std::cout << "Normals" << std::endl;
	for each (glm::vec3 normal in data.normals)
	{
		std::cout << glm::to_string(normal) << std::endl;
	}
	std::cout << "UVs" << std::endl;
	for each (glm::vec2 uv in data.texcoords)
	{
		std::cout << glm::to_string(uv) << std::endl;
	}
	std::cout << "Indices" << std::endl;
	for each (unsigned int index in data.indices)
	{
		std::cout << index << ", ";
	}
	std::cout << std::endl;
}

VertexBufferObject::VertexBufferObject()
{
	
}

VertexBufferObject::~VertexBufferObject()
{
}

unsigned int VertexBufferObject::getDataPositionSize()
{
	return data.positions.size();
}

void * VertexBufferObject::getIndices()
{
	return &data.indices;
}

void VertexBufferObject::enable() const
{
	if (id)
		enableVertexBufferObject();
	else
		disableVertexArray();
}

void VertexBufferObject::disable() const
{
	if (id)
		disableVertexBufferObject();
	else
		enableVertexArray();
}

void VertexBufferObject::enableVertexBufferObject() const
{
	unsigned int slot = 0;
	glBindBuffer(GL_ARRAY_BUFFER, id);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)offset.positions);
	// Old Code: OpenGL 2.1 standard
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, (const GLvoid*)offset.positions);
	// TODO: change normal, texcoord, tanget to attribPointer instead of client state
	if (!data.normals.empty())
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, (const GLvoid*)offset.normals);
	}

	if (!data.texcoords.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, (const GLvoid*) offset.texcoords);
	}

	if (!data.tangents.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT, 0, (const GLvoid*) offset.tangents);
	}
}

void VertexBufferObject::disableVertexBufferObject() const
{
	unsigned int slot = 0;

	if (!data.texcoords.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (!data.tangents.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (!data.normals.empty())
		glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::enableVertexArray() const
{
	unsigned int slot = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &(data.positions[0].x));

	if (!data.normals.empty())
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, &(data.normals[0].x));
	}

	if (!data.texcoords.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, &(data.texcoords[0].x));
	}

	if (!data.tangents.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT, 0, &(data.tangents[0].x));
	}
}

void VertexBufferObject::disableVertexArray() const
{
	unsigned int slot = 0;

	if (!data.texcoords.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (!data.tangents.empty())
	{
		glClientActiveTexture(GL_TEXTURE0 + slot++);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (!data.normals.empty())
		glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);
}
