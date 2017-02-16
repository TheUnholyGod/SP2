#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float size);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float size);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, float radius = 1, int numOfSlices = 360);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, float radius = 1, int numOfSlices = 36, int noOfStacks = 20);
	static Mesh* GenerateRing(const std::string &meshName, Color color, float outerRadius = 10.0f, float innerRadius = 5.0f, int numOfSlices = 360);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, float radius = 1, int numOfSlices = 36, int noOfStacks = 20);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned int numSlices, float BaseRadius, float TopRadius, float height);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateQuad1(const std::string &meshName, Color color, float size = 1.f);
	static Mesh* GenerateCone(const std::string &meshName, Color color, float radius = 1.f, float height = 1.f, float tilt = 0.f, float numOfSlices = 36.f);
};

#endif