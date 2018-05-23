#include "MeshViewApp.h"
#include <vector>

GLuint program;
GLuint  ModelView, Projection;
MeshViewApp* app;

void init(vector<string> fileNames) {
	program = InitShader("vshader.glsl", "fshader.glsl");
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