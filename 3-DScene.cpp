//Braxton Morrow
//SNHU Spring/Summer 2022
//CS 330
//Final Project

#include <iostream>         
#include <cstdlib>         
#include <GL/glew.h>       
#include <GLFW/glfw3.h>     
#include <glut.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLAD/glad/glad.h>
#include <glutplane.c>

sing namespace std; // Standard namespace
/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif
// Unnamed namespace
namespace
{
	const char* const WINDOW_TITLE = "Tutorial 4.4"; // Macro for window title
	// Variables for window width and height
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	// Stores the GL data relative to a given mesh
	struct GLMesh
	{
		GLuint vao; // Handle for the vertex array object
		GLuint vbo; // Handle for the vertex buffer object
		GLuint nVertices; // Number of indices of the mesh
	};
	// Main GLFW window
	GLFWwindow* gWindow = nullptr;
	// Triangle mesh data
	GLMesh gMesh;
	// Shader program
	GLuint gProgramId;
	// camera
	glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 gCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 gCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float gLastX = WINDOW_WIDTH / 2.0f;
	float gLastY = WINDOW_HEIGHT / 2.0f;
	bool gFirstMouse = true;
	// timing
	float gDeltaTime = 0.0f; // time between current frame and last frame
	float gLastFrame = 0.0f;
}
/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */

bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// Sets the background color of the window to black (it will be implicitely used by glClear)
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// render loop
// -----------
while (!glfwWindowShouldClose(gWindow))
{
	// per-frame timing
	// --------------------
	float currentFrame = glfwGetTime();
	gDeltaTime = currentFrame - gLastFrame;
	gLastFrame = currentFrame;
	// input
	// -----
	UProcessInput(gWindow);
	// Render this frame
	URender();
	glfwPollEvents();
}
}
// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	// GLFW: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// GLFW: window creation
	// ---------------------
	* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL,
		NULL);
	if (*window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// GLEW: initialize
	// ----------------
	// Note: if using GLEW version 1.13 or earlier
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}
	// Displays GPU OpenGL version
	cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;
	return true;
}
// process all input: query GLFW whether relevant keys are pressed/released this frameand react accordingly
void UProcessInput(GLFWwindow* window) {
	static const float cameraSpeed = 2.5f;
	float cameraOffset = cameraSpeed * gDeltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	glm::vec3 gCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 gCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 gCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCameraPos -= cameraSpeed * gCameraUp * cameraOffset;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCameraPos += cameraSpeed * gCameraUp * cameraOffset;
}
// glfw: whenever the window size changed (by OS or user resize) this callback
function executes
void UResizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
	if (gFirstMouse) {
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}
	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom
	to top
		gLastX = xpos;
	gLastY = ypos;
	gCamera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	gCamera.ProcessMouseScroll(yoffset);
}
// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT: {
		if (action == GLFW_PRESS)
			cout << "Left mouse button pressed" << endl;
		else
			cout << "Left mouse button released" << endl;
	}
							   break;
	case GLFW_MOUSE_BUTTON_MIDDLE: {
		if (action == GLFW_PRESS)
			cout << "Middle mouse button pressed" << endl;
		else
			cout << "Middle mouse button released" << endl;
	}
								 break;
	case GLFW_MOUSE_BUTTON_RIGHT: {
		if (action == GLFW_PRESS)
			cout << "Right mouse button pressed" << endl;
		else
			cout << "Right mouse button released" << endl;
	}
								break;
	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
//regular light
void lightSettings1(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 40.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

//make this light colored
void lightSettings2(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 40.0 };
	GLfloat light_position[] = { -1.0, -1.0, -1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void drawBush() {

	// Draw bush : color greenish yellow
	glColor3f(0.5f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.75f, 0.0f); 
	glutSolidSphere(3.0f, 100, 100);
	glEnd();

}
void drawBush() {

	// Draw bush : greenish yellow
	glColor3f(0.5f, 1.0f, 0.0f);
	glTranslatef(-3.0f, 0.75f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);
	glEnd();

}
void drawBush() {

	// Draw bush : color green
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(4.0f, 0.75f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);
	glEnd();

}
void drawBush() {

	// Draw bush : color green
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(-4.0f, 0.75f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);
	glEnd();
	glColor3f(0.0f, 1.0f, 0.0f);
}
static void drawPlane(int w, int h) {
	int i, j;
	float dw = 1.0 / w;
	float dh = 1.0 / h;

	//dark green
	glColor3f(0.0f, 0.5f, 0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	for (j = 0; j < h; ++j) {
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= w; ++i) {
			glVertex2f(dw * i, dh * (j + 1));
			glVertex2f(dw * i, dh * j);
		}
		glEnd();
	}
}

drawPlane(16, 16);

//this is the wall
void wallPiece() {
	glutSolidCube(GLdouble 1.0f);
	glTranslatef(0.0f, 1.f, 0.0f);
	//brown
	glColor3f(58.0f, 29.0f, 0.0f);
}
void glutSolidCube(GLdouble 1.0f) {
	glTranslatef(1.0f, 1.f, 0.0f);
	//brown
	glColor3f(58.0f, 29.0f, 0.0f);
}
void wallPiece() {
	glutSolidCube(GLdouble 1.0f);
	glTranslatef(-1.0f, 1.f, 0.0f);
	//brown
	glColor3f(58.0f, 29.0f, 0.0f);
}
void wallPiece() {
	glutSolidCube(GLdouble 1.0f);
	glTranslatef(2.0f, 1.f, 0.0f);
	//brown
	glColor3f(58.0f, 29.0f, 0.0f);
}
void wallPiece() {
	glutSolidCube(GLdouble 1.0f);
	glTranslatef(-2.0f, 1.f, 0.0f);
	//brown
	glColor3f(58.0f, 29.0f, 0.0f);
}

void pyramid(int wireframe) {

	if (wireframe) {
		// Set wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else {
		// Set fill-mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//dark green
		glColor3f(0.0f, 0.5f, 0.0f);
	}

	// Draw the base square
	glBegin(GL_QUADS);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glEnd();

	// Draw four side triangles
	glBegin(GL_TRIANGLE_FAN);

	// the commond point of the four triangles
	glVertex3f(0, 1.4, 0);

	// Base points of each triangle
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);

	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);

	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);

	//rotate upside down
	gl.glRotatef(1.0f, 0.0f, 0.0f, 3.1415f);
	gl.glRotatef(0.0f, 0.0f, 1.0f, 3.1415f);
	gl.glTranslatef(-5.0f, 0.75f, 0.0f);
	glEnd();
}

void pyramid(int wireframe) {

	if (wireframe) {
		// Set wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else {
		// Set fill-mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//dark green
		glColor3f(0.0f, 0.5f, 0.0f);
	}

	// Draw the base square
	glBegin(GL_QUADS);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glEnd();

	// Draw four side triangles
	glBegin(GL_TRIANGLE_FAN);

	// the commond point of the four triangles
	glVertex3f(0, 1.4, 0);

	// Base points of each triangle
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);

	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);

	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);

	//rotate upside down
	gl.glRotatef(1.0f, 0.0f, 0.0f, 3.1415f);
	gl.glRotatef(0.0f, 0.0f, 1.0f, 3.1415f);
	gl.glTranslatef(5.0f, 0.75f, 0.0f);
	glEnd();
}

void backTree() {
	GLUquadric* behindWallTree = gluNewQuadric();
	gluCylinder(behindWallTree, 1.0f, 2.0f, 2.0f, 100, 100);
	glColor3f(149.0f, 53.0f, 83.0f);
	gl.glTranslatef(0.0f, 1.75f, 0.0f);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
			1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(200, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}