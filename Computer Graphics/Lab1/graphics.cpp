#include <cmath>
#include "gl/glut.h"

#define pi 3.1415926

struct Vector2f
{
	GLfloat x;
	GLfloat y;

	Vector2f()
	{

	}

	Vector2f(GLfloat x, GLfloat y)
	{
		this->x = x;
		this->y = y;
	}
};

void DrawStar(Vector2f centerPos, GLfloat radium, GLfloat rotateAngle);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(244.0f / 255.0f, 0, 2.0f / 255.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.9, 0.6, 0.5);
	glVertex3f(0.9, 0.6, 0.5);
	glVertex3f(0.9, -0.6, 0.5);
	glVertex3f(-0.9, -0.6, 0.5);
	glEnd();

	glColor3f(250.0f / 255.0f, 244.0f / 255.0f, 8.0f / 255.0f);
	DrawStar(Vector2f(-0.6, 0.3), 0.18, 0);
	DrawStar(Vector2f(-0.3, 0.06), 0.06, 0.4 * pi - atan(5.0f / 4.0f));
	DrawStar(Vector2f(-0.18, 0.18), 0.06, 0.4 * pi - atan(7.0f / 2.0f));
	DrawStar(Vector2f(-0.18, 0.36), 0.06, atan(7.0f / 1.0f) - 0.6 * pi);
	DrawStar(Vector2f(-0.3, 0.48), 0.06, atan(5.0f / 3.0f) - 0.2 * pi);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple GLUT App");
	
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
void DrawStar(Vector2f centerPos, GLfloat radium, GLfloat rotateAngle)
{
	GLfloat smallRadium = radium * cos(0.4 * pi) / cos(0.2 * pi);

	Vector2f vertex1, vertex2, vertex3, vertex4, vertex5, vertex6, vertex7, vertex8, vertex9, vertex10;

	vertex1.x = centerPos.x + radium * sin(0.0 * pi + rotateAngle);
	vertex1.y = centerPos.y + radium * cos(0.0 * pi + rotateAngle);
	vertex2.x = centerPos.x + radium * sin(0.4 * pi + rotateAngle);
	vertex2.y = centerPos.y + radium * cos(0.4 * pi + rotateAngle);
	vertex3.x = centerPos.x + radium * sin(0.8 * pi + rotateAngle);
	vertex3.y = centerPos.y + radium * cos(0.8 * pi + rotateAngle);
	vertex4.x = centerPos.x + radium * sin(1.2 * pi + rotateAngle);
	vertex4.y = centerPos.y + radium * cos(1.2 * pi + rotateAngle);
	vertex5.x = centerPos.x + radium * sin(1.6 * pi + rotateAngle);
	vertex5.y = centerPos.y + radium * cos(1.6 * pi + rotateAngle);
	vertex6.x = centerPos.x + smallRadium * sin(0.2 * pi + rotateAngle);
	vertex6.y = centerPos.y + smallRadium * cos(0.2 * pi + rotateAngle);
	vertex7.x = centerPos.x + smallRadium * sin(0.6 * pi + rotateAngle);
	vertex7.y = centerPos.y + smallRadium * cos(0.6 * pi + rotateAngle);
	vertex8.x = centerPos.x + smallRadium * sin(1.0 * pi + rotateAngle);
	vertex8.y = centerPos.y + smallRadium * cos(1.0 * pi + rotateAngle);
	vertex9.x = centerPos.x + smallRadium * sin(1.4 * pi + rotateAngle);
	vertex9.y = centerPos.y + smallRadium * cos(1.4 * pi + rotateAngle);
	vertex10.x = centerPos.x + smallRadium * sin(1.8 * pi + rotateAngle);
	vertex10.y = centerPos.y + smallRadium * cos(1.8 * pi + rotateAngle);

	glBegin(GL_TRIANGLES);
	glVertex3f(vertex1.x, vertex1.y, 0.5);
	glVertex3f(vertex4.x, vertex4.y, 0.5);
	glVertex3f(vertex7.x, vertex7.y, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(vertex1.x, vertex1.y, 0.5);
	glVertex3f(vertex3.x, vertex3.y, 0.5);
	glVertex3f(vertex9.x, vertex9.y, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(vertex2.x, vertex2.y, 0.5);
	glVertex3f(vertex5.x, vertex5.y, 0.5);
	glVertex3f(vertex8.x, vertex8.y, 0.5);
	glEnd();
}