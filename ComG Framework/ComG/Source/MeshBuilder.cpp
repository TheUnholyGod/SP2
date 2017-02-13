#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float size = 1.f)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(1, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 1); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(1, 1); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(1, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 1); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);

	v.texCoord.Set(0, 0);
	v.texCoord.Set(1, 0);
	v.texCoord.Set(1, 1);
	v.texCoord.Set(0, 1);


	for (unsigned i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color,float size = 1.f)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, float radius, int numOfSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360 / numOfSlices;

	for (int slice = 0; slice <= numOfSlices; slice += anglePerSlice)
	{
		float theta = slice*anglePerSlice;
		float x = radius*cos(Math::DegreeToRadian(theta));
		float z = radius*sin(Math::DegreeToRadian(theta));
		v.pos.Set(x, 0, z);	v.color = color; vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);	v.color = color; vertex_buffer_data.push_back(v);
	}

	for (unsigned i = 0; i <= numOfSlices * 2; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, float radius, int numOfSlices, int noOfStacks)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float phi, theta;
	int anglePerSlice = 360.0f / numOfSlices;
	int anglePerStack = 180.0f / noOfStacks;

	for (int stack = 0; stack < noOfStacks + 1; stack++)
	{
		phi = -90.0f + stack*anglePerStack;
		for (int slices = 0; slices < numOfSlices + 1; slices++)
		{
			theta = slices*anglePerSlice;
			float x = radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
			float y = radius * sin(Math::DegreeToRadian(phi));
			float z = radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));

			v.pos.Set(x, y, z); v.color = color;  v.normal.Set(0, 1, 0);
			vertex_buffer_data.push_back(v);

			x = radius * cos(Math::DegreeToRadian(phi + anglePerStack)) * cos(Math::DegreeToRadian(theta));
			y = radius * sin(Math::DegreeToRadian(phi + anglePerStack));
			z = radius * cos(Math::DegreeToRadian(phi + anglePerStack)) * sin(Math::DegreeToRadian(theta));

			v.pos.Set(x, y, z); v.color = color; v.normal.Set(0, 1, 0);
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned i = 0; i <= (numOfSlices + 1) * (noOfStacks + 1) * 2; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float outerRadius, float innerRadius, int numOfSlices)
{

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360 / numOfSlices;


	for (int slice = 0; slice <= numOfSlices; slice += anglePerSlice)
	{
		float theta = slice*anglePerSlice;

		float x = outerRadius*cos(Math::DegreeToRadian(theta));
		float z = outerRadius*sin(Math::DegreeToRadian(theta));
		v.pos.Set(x, 0, z);	v.color = color; vertex_buffer_data.push_back(v);

		float x2 = innerRadius*cos(Math::DegreeToRadian(theta));
		float z2 = innerRadius*sin(Math::DegreeToRadian(theta));
		v.pos.Set(x2, 0, z2); v.color = color; vertex_buffer_data.push_back(v);
	}

	for (unsigned int i = 0; i < (numOfSlices + 1) * 2; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, float radius, int numOfSlices, int noOfStacks)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float phi, theta;
	int anglePerSlice = 360.0f / numOfSlices;
	int anglePerStack = 90.0f / noOfStacks;

	for (int stack = 0; stack < noOfStacks + 1; stack++)
	{
		phi = stack*anglePerStack;
		for (int slices = 0; slices < numOfSlices + 1; slices++)
		{
			theta = slices*anglePerSlice;
			float x = radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
			float y = radius * sin(Math::DegreeToRadian(phi));
			float z = radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));

			v.pos.Set(x, y, z); v.color = color; vertex_buffer_data.push_back(v);

			x = radius * cos(Math::DegreeToRadian(phi + anglePerStack)) * cos(Math::DegreeToRadian(theta));
			y = radius * sin(Math::DegreeToRadian(phi + anglePerStack));
			z = radius * cos(Math::DegreeToRadian(phi + anglePerStack)) * sin(Math::DegreeToRadian(theta));

			v.pos.Set(x, y, z); v.color = color; vertex_buffer_data.push_back(v);
		}
	}

	for (int slice = 0; slice < numOfSlices + 1; slice++)
	{
		float theta = slice*anglePerSlice;
		float x = radius*cos(Math::DegreeToRadian(theta));
		float z = radius*sin(Math::DegreeToRadian(theta));
		v.pos.Set(0, 0, 0);	v.color = color; vertex_buffer_data.push_back(v);
		v.pos.Set(x, 0, z);	v.color = color; vertex_buffer_data.push_back(v);
	}

	for (unsigned i = 0; i <= ((numOfSlices + 1) * (noOfStacks + 1) * 2) + ((numOfSlices + 1) * 2); ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned int numSlices, float BaseRadius, float TopRadius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	//BOTTOM
	float anglePerSlice = 360.0f / numSlices;
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(BaseRadius * cos(Math::DegreeToRadian(theta)), (-height) * 0.5f, BaseRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	v.pos.Set(0, (-height)*0.5f, 0);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);


	//CURVE
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(BaseRadius * cos(Math::DegreeToRadian(theta)), (-height) * 0.5f, BaseRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);

		v.pos.Set(TopRadius * cos(Math::DegreeToRadian(theta)), (height)* 0.5f, TopRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}

	//TOP
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(TopRadius * cos(Math::DegreeToRadian(theta)), (height)* 0.5f, TopRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		if (TopRadius == 0.0f)
		{
			v.normal.Set(height * cos(Math::DegreeToRadian(theta)), BaseRadius, height * sin(Math::DegreeToRadian(theta)));
			v.normal.Normalize();
		}
		else
			v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

	}

	v.pos.Set(0, (height)* 0.5f, 0);
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(numSlices + 1);
		index_buffer_data.push_back(slice);
	}
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(numSlices + 2 + slice * 2);
		index_buffer_data.push_back(numSlices + 2 + slice * 2 + 1);
	}
	for (unsigned slice = 0; slice <= numSlices; slice++)
	{
		index_buffer_data.push_back(numSlices + 2 + numSlices * 2 + 1 + slice + 1);
		index_buffer_data.push_back((numSlices + 2) + (numSlices)* 2 + 1 + numSlices + 2);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}


Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) 
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex>vertex_buffer_data;
	std::vector<unsigned>index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			v.pos.Set(0.5f, -0.5f, 0.0f); v.normal.Set(0, 0, 1); v.texCoord.Set((j + 1) * 0.0625, (numRow - i - 1)* 0.0625); vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, -0.5f, 0.0f); v.normal.Set(0, 0, 1); v.texCoord.Set((j)* 0.0625, (numRow - i - 1) * 0.0625);  vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, 0.5f, 0.0f); v.normal.Set(0, 0, 1); v.texCoord.Set(j * 0.0625, (numRow - i)* 0.0625); vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, 0.5f, 0.0f); v.normal.Set(0, 0, 1); v.texCoord.Set((j + 1) * 0.0625, (numRow - i)* 0.0625); vertex_buffer_data.push_back(v);

			index_buffer_data.push_back((i*numCol + j) * 4 + 0);
			index_buffer_data.push_back((i*numCol + j) * 4 + 1);
			index_buffer_data.push_back((i*numCol + j) * 4 + 2);
			index_buffer_data.push_back((i*numCol + j) * 4 + 0);
			index_buffer_data.push_back((i*numCol + j) * 4 + 2);
			index_buffer_data.push_back((i*numCol + j) * 4 + 3);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()*sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size()*sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad1(const std::string &meshName, Color color, float size	)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(100, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 100); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(100, 100); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f*size, 0.0f, 0.5f*size); v.texCoord.Set(100, 0); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f*size, 0.0f, -0.5f*size); v.texCoord.Set(0, 100); v.color = color; v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);

	v.texCoord.Set(0, 0);
	v.texCoord.Set(1, 0);
	v.texCoord.Set(1, 1);
	v.texCoord.Set(0, 1);


	for (unsigned i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, float radius, float height, float tilt, float numOfSlices)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float anglePerSlice = 360.0f / numOfSlices;
	for (unsigned slice = 0; slice < numOfSlices + 1; ++slice)
	{
		float theta = slice * anglePerSlice;
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), radius, height * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height, tilt);
		v.color = color;
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), radius, height * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}

	v.pos.Set(0, 0, 0);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < numOfSlices + 1; ++i)
	{
		index_buffer_data.push_back(2 * i);
		index_buffer_data.push_back(2 * 1 + 1);
	}

	for (unsigned i = 0; i < numOfSlices + 1; ++i)
	{
		index_buffer_data.push_back(2 * (numOfSlices + 1) + 1);
		index_buffer_data.push_back(2 * i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}