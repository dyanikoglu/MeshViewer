#include "MeshLoader.h"

//************************************
// Method:    metaData
// FullName:  MeshLoader::metaData
// Access:    public 
// Returns:   GLint
// Parameter: string path, path of the off file
// Map contents of off file into memory, then read just it's metadata
//************************************
GLint MeshLoader::metaData(string path) {
	// map file to memory
	MemoryMapped data(path, MemoryMapped::WholeFile, MemoryMapped::RandomAccess);
	
	if (!data.isValid()) {
		cout << "Invalid data" << endl;
		return -1;
	}

	// raw pointer to mapped memory
	char* buffer = (char*)data.getData();
	GLint result;
	string tempLine;
	GLint lineNum = 0;
	for (GLint i = 0; i < data.size(); i++) {
		// Build current line
		if (buffer[i] != '\n' && buffer[i] != '\r') {
			tempLine.push_back(buffer[i]);
		}
		// Parse current line
		else {
			if (lineNum == 0) {
				if (tempLine.compare("OFF") == 0) {
          i++;
					lineNum++;
					tempLine.clear();
				}
				else {
					cout << "File is not in OFF format" << endl;
					return -1;
				}
			}
			else if (lineNum == 1) {
				GLint firstSpace = tempLine.find(' ');
				GLint secondSpace = tempLine.find(' ', firstSpace + 1);
				result = stoi(tempLine.substr(firstSpace + 1, secondSpace)); // Face count
				data.~MemoryMapped();
				return result;
			}
		}
	}
}

//************************************
// Method:    loadMesh
// FullName:  MeshLoader::loadMesh
// Access:    public 
// Returns:   bool
// Parameter: string path, path of the off file
// Map contents of off file into memory, then read and store all data
//************************************
bool MeshLoader::loadMesh(string path) {
	// map file to memory
	MemoryMapped data(path, MemoryMapped::WholeFile, MemoryMapped::RandomAccess);

	if (!data.isValid()) {
		cout << "Invalid data" << endl;
		return false;
	}

	// raw pointer to mapped memory
	char* buffer = (char*)data.getData();
	string tempLine;
	GLint lineNum = 0;
	for (GLint i = 0; i < data.size(); i++) {
		// Build current line
		if (buffer[i] != '\n' && buffer[i] != '\r') {
			tempLine.push_back(buffer[i]);
		}
		// Parse current line
		else {
			// OFF Prefix
			if (lineNum == 0) {
				if (tempLine.compare("OFF") == 0) {
          i++;
					lineNum++;
				}
				else {
					cout << "File is not in OFF format" << endl;
					return false;
				}
			}
			// Metadata
			else if (lineNum == 1) {
				GLint firstSpace = tempLine.find(' ');
				GLint secondSpace = tempLine.find(' ', firstSpace+1);
				vertexCount = stoi(tempLine.substr(0, firstSpace));
				faceCount = stoi(tempLine.substr(firstSpace + 1, secondSpace));
        i++;
				lineNum++;
			}
			// Vertices
			else if(lineNum < vertexCount + 2) {
				GLint firstSpace = tempLine.find(' ');
				GLint secondSpace = tempLine.find(' ', firstSpace+1);
				GLfloat x = stof(tempLine.substr(0, firstSpace));
				GLfloat y = stof(tempLine.substr(firstSpace + 1, secondSpace));
				GLfloat z = stof(tempLine.substr(secondSpace + 1, tempLine.length()));

				// Check min, max positions
				if (x < minX) {
					minX = x;
				}
				if (x > maxX) {
					maxX = x;
				}
				if (y > maxY) {
					maxY = y;
				}
				if (y < minY) {
					minY = y;
				}
				if (z < minZ) {
					minZ = z;
				}
				if (z > maxZ) {
					maxZ = z;
				}
				// Check end

				tempVertices.emplace_back(vec4(x, y, z, 1.f));
        i++;
				lineNum++;
			}
			// Faces
			else {
				GLint firstSpace = tempLine.find(' ');
				GLint secondSpace = tempLine.find(' ', firstSpace+1);
				GLint thirdSpace = tempLine.find(' ', secondSpace+1);
				GLint v1 = stoi(tempLine.substr(firstSpace + 1, secondSpace));
				GLint v2 = stoi(tempLine.substr(secondSpace + 1, thirdSpace));
				GLint v3 = stoi(tempLine.substr(thirdSpace + 1, tempLine.length()));

				vertices.emplace_back(tempVertices[v1]);
				vertices.emplace_back(tempVertices[v2]);
				vertices.emplace_back(tempVertices[v3]);

				vec4 u = tempVertices[v3] - tempVertices[v2];
				vec4 v = tempVertices[v3] - tempVertices[v1];
				vec3 normal = normalize(cross(v, u));

				for (int i = 0; i < 3; i++) {
					this->normals.emplace_back(vec4(normal,0.0));
				}

        i++;
				lineNum++;
			}

			tempLine.clear();
		}
	}

	meshCenter = vec3((minX + maxX) / 2.f, (minY + maxY) / 2.f, (minZ + maxZ) / 2.f);
	meshSize = vec3(maxX - minX, maxY - minY, maxZ - minZ);

	data.~MemoryMapped();
	return true;
}

MeshLoader::MeshLoader() {
	this->maxX = -FLT_MAX;
	this->maxY = -FLT_MAX;
	this->maxZ = -FLT_MAX;
	this->minX = FLT_MAX;
	this->minY = FLT_MAX;
	this->minZ = FLT_MAX;
}