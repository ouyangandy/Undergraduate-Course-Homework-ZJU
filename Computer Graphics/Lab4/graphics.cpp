#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl/glut.h"
#include "stanford_bunny.h"

float eye[] = { 0, 4, 6 };
float center[] = { 0, 0, 0 };
float fDistance = 0.2f;
float fRotate = 0;
bool bAnim = false;
bool bDrawList = false;
GLint tableList = 0;
GLint rabbitList = 0;
int number = 1;
int row = 1;

void DrawTable() // 桌子大小 5 × 4
{
	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	if (row >= 5)
		glTranslatef(0, 0, (-row + 4.0) / 2.0);
	if (row < 5)
		glScalef(5, 1, 4);
	else
		glScalef(5, 1, row);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.5, 1);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	if (row < 5)
		glTranslatef(1.5, 1.5, -1);
	else
		glTranslatef(1.5, 1.5, -row + 3.0);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	if (row < 5)
		glTranslatef(-1.5, 1.5, -1);
	else
		glTranslatef(-1.5, 1.5, -row + 3.0);
	glScalef(1, 3, 1);
	glutSolidCube(1.0);
	glPopMatrix();
}

GLint GenTableList()
{
	GLint listid = glGenLists(2);
	glNewList(listid, GL_COMPILE);
	DrawTable();
	glEndList();
	glNewList(listid + 1, GL_COMPILE);
	DrawBunny();
	glEndList();
	return listid;
}

void Draw_Table_List()
{
	glPushMatrix();
	glTranslatef(2.1, 4.5, 1.5);
	glScalef(2, 2, 2);

	for (int i = 1; i <= number; ++i)
	{
		glCallList(rabbitList);
		if (i % 4 == 0)
			glTranslatef(2.1f, 0.0f, -0.5f);
		else
			glTranslatef(-0.7f, 0.0f, 0.0f);
	}

	glPopMatrix();
	glCallList(tableList);
}

void DrawScene() // 纵向间隔1.0 横向间隔1.4
{
	glPushMatrix();
	glTranslatef(2.1, 4.5, 1.5);
	glScalef(2, 2, 2);

	for (int i = 1; i <= number; ++i)
	{
		DrawBunny();
		if (i % 4 == 0)
			glTranslatef(2.1f, 0.0f, -0.5f);
		else
			glTranslatef(-0.7f, 0.0f, 0.0f);
	}

	glPopMatrix();
	DrawTable();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45, whRatio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'a':
	{
		eye[0] += fDistance;
		center[0] += fDistance;
		break;
	}
	case 'd':
	{
		eye[0] -= fDistance;
		center[0] -= fDistance;
		break;
	}
	case 'w':
	{
		eye[1] -= fDistance;
		center[1] -= fDistance;
		break;
	}
	case 's':
	{
		eye[1] += fDistance;
		center[1] += fDistance;
		break;
	}
	case 'z':
	{
		eye[2] *= 0.95;
		break;
	}
	case 'c':
	{
		eye[2] *= 1.05;
		break;
	}
	case 'l':
	{
		bDrawList = !bDrawList;	// 切换显示列表和非显示列表绘制方式
		break;
	}
	case ' ':
	{
		bAnim = !bAnim;
		break;
	}
	case 'i':
	{
		number++;
		row = (number + 3) / 4;
		break;
	}
	case 'j':
	{
		number--;
		if (number <= 1)number = 1;
		row = (number + 3) / 4;
		break;
	}
	default: break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy_s(mode, "display list");
	else
		strcpy_s(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME); // Get Time
	if (time - timebase > 1000) {
		sprintf_s(buffer, "FPS:%4.2f %s",
			frame*1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0, 480, 0, 480, -1, 1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10, 10);
	for (c = buffer; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Draw char
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5, 0, 1);							// Background Color
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0, 5, 50)，Y轴向上

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat gray[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_pos[] = { 10, 10, 10, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glEnable(GL_LIGHT0);

	if (bAnim)
		fRotate += 0.5f;
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis

	glScalef(0.4, 0.4, 0.4);
	if (!bDrawList)
		DrawScene();						// old way
	else
		Draw_Table_List();                  // new way

	getFPS();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Exercise 4");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	tableList = GenTableList();
	rabbitList = tableList + 1;
	glutMainLoop();
	return 0;
}


