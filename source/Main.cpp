#include "MeshViewApp.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


GLuint program;
GLuint  ModelView, Projection;
MeshViewApp* app;

std::string readFile(const char *filePath) {
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);

  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    return "";
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}


GLuint LoadShader(const char *vertex_path, const char *fragment_path) {
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = readFile(vertex_path);
  std::string fragShaderStr = readFile(fragment_path);
  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader
  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);
  // Check vertex shader
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  std::cout << &vertShaderError[0] << std::endl;

  // Compile fragment shader
  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  std::cout << &fragShaderError[0] << std::endl;

  std::cout << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> programError((logLength > 1) ? logLength : 1);
  glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
  std::cout << &programError[0] << std::endl;

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  return program;
}

void init(vector<string> fileNames) {
	program = LoadShader("./source/vshader.glsl", "./source/fshader.glsl");
	glUseProgram(program);

	app = new MeshViewApp(program, fileNames);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.f, 1.f, 1.f, 1.f); // white background
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	app->draw();
	glutSwapBuffers();
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		app->yRotation -= 2;
		break;
	case GLUT_KEY_RIGHT:
		app->yRotation += 2;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'N':
	case 'n':
		app->switchMesh(1);
		break;
	case 'P':
	case 'p':
		app->switchMesh(-1);
		break;
	case 'V':
	case 'v':
		app->drawMode = app->VERTEX;
		break;
	case 'E':
	case 'e':
		app->drawMode = app->EDGE;
		break;
	case 'F':
	case 'f':
		app->drawMode = app->FACE;
		break;
	case 'x':
		app->offset += vec4(1, 0, 0, 0);
		break;
	case 'X':
		app->offset += vec4(-1, 0, 0, 0);
		break;
	case 'y':
		app->offset += vec4(0, 1, 0, 0);
		break;
	case 'Y':
		app->offset += vec4(0, -1, 0, 0);
		break;
	case 'z':
		app->offset += vec4(0, 0, 1, 0);
		break;
	case 'Z':
		app->offset += vec4(0, 0, -1, 0);
		break;
	case 's':
		app->scale *= 0.5;
		break;
	case 'S':
		app->scale *= 2;
		break;
	default:
		break;
	}
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	mat4 projection = Perspective(60 * (float)width / height, (float)width / height, 0.01f, 1000.0f);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}

void timer(GLint) {
	app->nextFrame();
	glutPostRedisplay();
	glutTimerFunc(1000.f / 60.f, timer, 0); // 60 FPS
}

GLfloat prevX = 0;
void motion(int x, int y) {
	if (x > 1360) {
		prevX = 650;
		glutWarpPointer(650, y);
	}
	if (x < 15) {
		prevX = 650;
		glutWarpPointer(650, y);
	}
	app->camera->position = RotateY((x - prevX) / 10.f) * app->camera->position;
	prevX = x;
}

void mouseWheel(int button, int dir, int x, int y) {
	if (dir > 0) {
		app->camera->position = vec4(app->camera->position.x * 1.01, app->camera->position.y, app->camera->position.z * 1.01, 1.f);
	}
	else {
		app->camera->position = vec4(app->camera->position.x * 0.99, app->camera->position.y, app->camera->position.z * 0.99, 1.f);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "At least one file name should be specified" << endl;
		exit(0);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(750, 750);
	glutCreateWindow("Mesh Viewer");
	glewExperimental = GL_TRUE;
	glewInit();

	vector<string> fileNames;

	for (int i = 1; i < argc; i++) {
		fileNames.emplace_back(argv[i]);
	}

	init(fileNames);
	glutTimerFunc(1000.f / 60.f, timer, 0); // 60 FPS
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutPassiveMotionFunc(motion);
	glutMouseWheelFunc(mouseWheel);
	glutFullScreen();

	glutMainLoop();
	return 0;
}