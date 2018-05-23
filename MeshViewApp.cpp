#include "MeshViewApp.h"

//************************************
// Method:    MeshViewApp
// FullName:  MeshViewApp::MeshViewApp
// Access:    public 
// Parameter: GLuint program
// Parameter: vector<string> fileNames, name of each file to be loaded
// Initializes the application by loading requested meshes
//************************************
MeshViewApp::MeshViewApp(GLuint program, vector<string> fileNames) {
	this->drawMode = FACE;
	mat = Material(Material::type(rand() % 10));

	this->offset = vec4();
	this->yRotation = 0.f;
	this->scale = 1.f;

	this->program_ptr = program;

	for (auto & fileName : fileNames) {
		this->meshList.emplace_back(fileName);
	}

	this->totalVertexCount = 0;
	this->totalFaceCount = 0;
	this->totalNormalCount = 0;
	this->meshCursor = -1;

	camera = new Camera();

	if (this->load() == false) {
		exit(1);
	}

	switchMesh(1);

	this->light_position = vec4(0, 0, 20, 1.0);

	glUniform4fv(glGetUniformLocation(program_ptr, "LightPosition"), 1, this->light_position);

	ModelView_ptr = glGetUniformLocation(program_ptr, "ModelView");
	Projection_ptr = glGetUniformLocation(program_ptr, "Projection");

	projection = Perspective(60, 1, 0.1, 1000);
	glUniformMatrix4fv(Projection_ptr, 1, GL_TRUE, projection);

	calculateLighting();
}

//************************************
// Method:    load
// FullName:  MeshViewApp::load
// Access:    public 
// Returns:   bool
// Loads a single mesh into GPU buffer
//************************************
bool MeshViewApp::load() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Get metadata of meshes
	this->meshLoader = new MeshLoader();
	for (auto & path : meshList) {
		GLint faceCount = this->meshLoader->metaData(path);

		if (faceCount == -1) {
			return false;
		}

		totalVertexCount += faceCount * 3;
		totalNormalCount += faceCount * 3;
		totalFaceCount += faceCount;
	}

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, totalVertexCount * sizeof(vec4) + totalNormalCount * sizeof(vec4), NULL, GL_STATIC_DRAW);

	// Put vertices & normals into buffer
	GLuint tempOffset = 0;
	GLuint tempIndex = 0;
	for (auto & path : meshList) {
		this->meshLoader = new MeshLoader();

		if (this->meshLoader->loadMesh(path) == false) {
			return false;
		}
		
		this->meshCenters.emplace_back(this->meshLoader->meshCenter);
		this->meshSizes.emplace_back(this->meshLoader->meshSize);
		this->meshOffsets.emplace_back(tempIndex);
		this->meshVertexCounts.emplace_back(this->meshLoader->vertices.size());
		
		glBufferSubData(GL_ARRAY_BUFFER, tempOffset, sizeof(vec4) * this->meshLoader->vertices.size(), this->meshLoader->vertices.front());
		glBufferSubData(GL_ARRAY_BUFFER, totalVertexCount * sizeof(vec4) + tempOffset , sizeof(vec4) * this->meshLoader->normals.size(), this->meshLoader->normals.front());
		
		tempOffset += sizeof(vec4) * this->meshLoader->vertices.size();
		tempIndex += this->meshLoader->vertices.size();
	}

	GLuint vPosition = glGetAttribLocation(program_ptr, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program_ptr, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tempOffset));

	return true;
}

//************************************
// Method:    calculateLighting
// FullName:  MeshViewApp::calculateLighting
// Access:    public 
// Returns:   void
// Calculates global lighting
//************************************
void MeshViewApp::calculateLighting() {
	this->ambient_product = mat.light_ambient * mat.material_ambient;
	this->diffuse_product = mat.light_diffuse * mat.material_diffuse;
	this->specular_product = mat.light_specular * mat.material_specular;
}

void MeshViewApp::draw() {
	glUniform4fv(glGetUniformLocation(program_ptr, "LightPosition"), 1, camera->view * this->light_position);

	glUniform4fv(glGetUniformLocation(program_ptr, "AmbientProduct"), 1, this->ambient_product);
	glUniform4fv(glGetUniformLocation(program_ptr, "DiffuseProduct"), 1, this->diffuse_product);
	glUniform4fv(glGetUniformLocation(program_ptr, "SpecularProduct"), 1, this->specular_product);
	glUniform1f(glGetUniformLocation(program_ptr, "Shininess"), this->mat.material_shininess);

	// If object is far away from it's center:
	if (abs(this->meshCenters[meshCursor].x) > 3 || abs(this->meshCenters[meshCursor].z) > 3) {
		glUniformMatrix4fv(ModelView_ptr, 1, GL_TRUE, camera->view * Translate(this->offset) * Translate(0, this->meshCenters[meshCursor].y, 0) * RotateY(this->yRotation) * Scale(this->scale) *  Translate(-this->meshCenters[meshCursor]));
	}
	//Otherwise:
	else {
		glUniformMatrix4fv(ModelView_ptr, 1, GL_TRUE, camera->view * Translate(this->offset) * Translate(this->meshCenters[meshCursor]) * RotateY(this->yRotation) * Scale(this->scale) *  Translate(-this->meshCenters[meshCursor]));
	}

	// Draw the mesh according to selected drawing mode
	switch (drawMode) {
	case MeshViewApp::VERTEX:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case MeshViewApp::EDGE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	default:
	case MeshViewApp::FACE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}

	// Enable face culling to improve performance
	glEnable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, meshOffsets[meshCursor], meshVertexCounts[meshCursor]);
	glDisable(GL_CULL_FACE);
}

//************************************
// Method:    switchMesh
// FullName:  MeshViewApp::switchMesh
// Access:    public 
// Returns:   void
// Parameter: GLint i, Index of the new mesh
// Switches to the next or previous mesh
//************************************
void MeshViewApp::switchMesh(GLint i) {
	this->meshCursor += i;
	if (meshCursor < 0) {
		this->meshCursor = meshList.size() - 1;
	}
	else if(meshCursor >= meshList.size()) {
		this->meshCursor = 0;
	}

	this->offset = vec4();
	this->yRotation = 0.f;
	this->scale = 1.f;

	mat = Material(Material::type(rand() % 9));
	calculateLighting();

	this->camera->focal = vec4(0, this->meshCenters[meshCursor].y, 0, 1);

	GLfloat maxSize = MAX(this->meshSizes[meshCursor].x, this->meshSizes[meshCursor].z);
	maxSize = MAX(maxSize, this->meshSizes[meshCursor].y);

	projection = Perspective(60, 1, 0.1, maxSize*5000);
	glUniformMatrix4fv(Projection_ptr, 1, GL_TRUE, projection);

	this->camera->position = vec4(0, this->meshCenters[meshCursor].y, 1.75 * maxSize, 1.f);
}

void MeshViewApp::nextFrame() {
	this->camera->update();
}