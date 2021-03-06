#include "gl/glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;

void Draw_Triangle() // This function draws a triangle with RGB colors
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

void Draw_Cuboid(double x, double y, double z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	double cx = x / 2.0;
	double cy = y / 2.0;
	double cz = z / 2.0;
	glBegin(GL_QUADS);
	// 左面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-cx, cy, -cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-cx, cy, cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy, cz);
	// 右面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx, cy, -cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx, cy, cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(cx, -cy, cz);
	// 上面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, cy, -cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx, cy, -cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx, cy, cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy, cz);
	// 下面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx, -cy, cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy, cz);
	// 前面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx, cy, -cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy, -cz);
	// 后面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, cz);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx, -cy, cz);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx, cy, cz);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy, cz);
	glEnd();
}

void Draw_Table() // This function draws a table
{
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glTranslatef(0.15, 0.1, 0);
	Draw_Cuboid(0.1, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glTranslatef(-0.15, 0.1, 0);
	Draw_Cuboid(0.1, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glTranslatef(0.15, -0.1, 0);
	Draw_Cuboid(0.1, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glTranslatef(-0.15, -0.1, 0);
	Draw_Cuboid(0.1, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	Draw_Cuboid(0.5, 0.4, 0.1);
	glPopMatrix();
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

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
	// If want display in wireframe mode
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	// left table
	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, -6.0f);		// Place the triangle Left
	glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
	glScalef(2.0f, 2.0f, 2.0f);
	Draw_Table();
	glPopMatrix();

	// middle table
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glScalef(2.0f, 2.0f, 2.0f);
	Draw_Table();
	glPopMatrix();

	// right table
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -6.0f);			// Place the triangle at Center
	glScalef(fScale, fScale, fScale);			// Rotate around Y axis
	glScalef(2.0f, 2.0f, 2.0f);
	Draw_Table();
	glPopMatrix();

	fTranslate += 0.005f;
	fRotate += 0.5f;
	fScale -= 0.01f;

	if (fTranslate > 0.5f) fTranslate = 0.0f;
	if (fScale < 0.5f) fScale = 1.0f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}