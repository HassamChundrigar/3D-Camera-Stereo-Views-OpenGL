#include<stdlib.h>
#include<glut.h>
#include<Windows.h>
#include"stereoCam.h"
using namespace std;
stereoCam cam;
float viewingAngle, aspectRatio, nearPlane, farPlane, eyeDistance;
int draw = 2;
float angle = 0;
void drawings()
{
	glPushMatrix();
	glRotatef(angle, 1, 1, 1);

	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 0);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glTranslatef(-10, 0, 0);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glTranslatef(5, 5, 0);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glTranslatef(0, -10, 0);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glTranslatef(0, 5, 5);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glTranslatef(0, 0, -10);

	glPushMatrix();
	glRotatef(angle, 1, 1, 1);
	if (draw == 1)
		glutWireTeapot(1);
	if (draw == 2)
		glutWireSphere(1, 20, 20);
	glPopMatrix();

	glPopMatrix();
}
void view(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	cam.setViewPortLeft();
	drawings();
	cam.setViewPortRight();
	drawings();
	//angle++;
	Sleep(20);
	glutSwapBuffers();
	glutPostRedisplay();
}
void init(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Hassam Window");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	viewingAngle = 30.0; aspectRatio = 64.0 / 48.0; nearPlane = 0.5; farPlane = 50.0, eyeDistance = .5;
	cam.setShape(viewingAngle, aspectRatio, nearPlane, farPlane);
	cam.set(point3D(0, 0, 5), point3D(0, 0, 0), vector3D(0, 1, 0), eyeDistance);
}
void myKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':
		cam.move(0, 0, -0.1);
		break;
	case's':
		cam.move(0, 0, 0.1);
		break;
	case'a':
		cam.move(-0.1, 0, 0);
		break;
	case'd':
		cam.move(0.1, 0, 0);
		break;
	case 'q':
		cam.roll(1);
		break;
	case'e':
		cam.roll(-1);
		break;
	case'[':
		if (eyeDistance > 0)
			eyeDistance -= 0.05;
		cam.set(point3D(0, 0, 5), point3D(0, 0, 0), vector3D(0, 1, 0), eyeDistance);
		break;
	case']':
		if (eyeDistance < 5)
			eyeDistance += 0.05;
		cam.set(point3D(0, 0, 5), point3D(0, 0, 0), vector3D(0, 1, 0), eyeDistance);
		break;
	case'`':
		viewingAngle = 30.0; aspectRatio = 64.0 / 48.0; nearPlane = 0.5; farPlane = 50.0, eyeDistance = .5;
		cam.setShape(viewingAngle, aspectRatio, nearPlane, farPlane);
		break;
	}
	glutPostRedisplay();
}
void specialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		aspectRatio /= 0.95;
		break;
	case GLUT_KEY_LEFT:
		aspectRatio *= 0.95;
		break;
	case GLUT_KEY_UP:
		if (viewingAngle<60)
			viewingAngle++;
		break;
	case GLUT_KEY_DOWN:
		if (viewingAngle>30)
			viewingAngle--;
		break;
	}
	cam.setShape(viewingAngle, aspectRatio, nearPlane, farPlane);
	glutPostRedisplay();
}
int mouseLeftClick = 0;
int xPoint, yPoint;
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftClick = 1;
			xPoint = x; yPoint = glutGet(GLUT_WINDOW_HEIGHT) - y;
		}
		else if (state == GLUT_UP)
		{
			mouseLeftClick = 0;
			xPoint = 0; yPoint = 0;
		}
	}
	glutPostRedisplay();
}
void myMouseMotion(int x, int y)
{
	if (mouseLeftClick == 1)
	{
		float xDis = x - xPoint; float yDis = glutGet(GLUT_WINDOW_HEIGHT) - y - yPoint;
		float xAngle = (xDis / glutGet(GLUT_WINDOW_WIDTH)) * 360.0 / 1;
		float yAngle = (yDis / glutGet(GLUT_WINDOW_HEIGHT)) * 360.0 / 1;
		xPoint = x; yPoint = glutGet(GLUT_WINDOW_HEIGHT) - y;
		cam.pitch(yAngle);
		cam.yaw(xAngle);
	}
	glutPostRedisplay();
}
void menuEvents(int option)
{
	draw = option;
	glutPostRedisplay();
}

void initMenu()
{
	glutAddMenuEntry("Teapot", 1);
	glutAddMenuEntry("Sphere", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init();
	glutKeyboardFunc(myKey);
	glutMotionFunc(myMouseMotion);
	glutMouseFunc(myMouse);
	glutDisplayFunc(view);
	glutSpecialFunc(specialFunc);
	glutCreateMenu(menuEvents);
	initMenu();
	glutMainLoop();
	return 0;
}