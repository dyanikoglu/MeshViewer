#pragma once
#include "Angel/Angel.h"
#include <vector>
#include "MeshLoader.h"
#include "MemoryMapped.h"
#include <iostream>
#include <string.h>

using namespace std;

class MeshLoader {
public:
	bool loadMesh(string path);
	MeshLoader();
	vector<vec4> tempVertices;
	vector<vec4> vertices;
	GLint vertexCount;
	GLint faceCount;
	GLfloat minX;
	GLfloat maxX;
	GLfloat minY;
	GLfloat maxY;
	GLfloat minZ;
	GLfloat maxZ;
	vec3 meshCenter;
	vec3 meshSize;
	vector<vec4> normals;
	GLint metaData(string path);
};