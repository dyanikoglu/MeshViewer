#pragma once
#include "Angel/Angel.h"
#include "MeshLoader.h"
#include "Materials.h"
#include "Camera.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

class MeshViewApp {
public:
	enum DrawMode {
		VERTEX = 0,
		EDGE = 1,
		FACE = 2
	};

	MeshViewApp(GLuint program, vector<string> filePaths);
	void draw();
	void nextFrame();
	DrawMode drawMode;
	GLuint program_ptr;
	GLuint totalVertexCount; // Total vertex count of loaded meshes
	GLuint totalNormalCount; // Total normal count of loaded meshes
	GLuint totalFaceCount; // Total face count of loaded meshes
	GLuint ModelView_ptr;
	GLuint Projection_ptr;
	mat4 projection; // Projection matrix
	vec4 ambient_product;
	vec4 diffuse_product;
	vec4 specular_product;
	vec4 light_position;
	Material mat;
	void calculateLighting();
	void switchMesh(GLint i);
	MeshLoader* meshLoader;

	GLfloat yRotation; // y rotation of model
	vec4 offset; // Offset of mesh from center
	GLfloat scale; // Scale of mesh

	vector<string> meshList; // Name of each loaded mesh
	vector<GLuint> meshOffsets; // Buffer offset of each loaded mesh
	vector<vec3> meshSizes; // Unit size of each loaded mesh
	vector<vec3> meshCenters; // Center coordinates of each loaded mesh
	vector<GLuint> meshVertexCounts; // Vertex count of each loaded mesh
	GLint meshCursor; // Index of current loaded mesh

	Camera* camera;
	bool load();
};