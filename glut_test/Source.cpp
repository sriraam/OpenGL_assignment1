
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees
and is provided without guarantee or warrantee expressed or
implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include <iostream>
#include<math.h>
int viewport_mode;
int PROJECTION,Red,Green,Blue;
//static GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };  /* Red diffuse light. */
//GLfloat light_position[] = { 1.0, 1.0, 1.0,0.0 };  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
	{ -1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, -1.0 } };
/*{ 1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0, 1.0 } };*/
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
	{ 0, 1, 2, 3 },{ 3, 2, 6, 7 },{ 7, 6, 5, 4 },
	{ 4, 5, 1, 0 },{ 5, 6, 2, 1 },{ 7, 4, 0, 3 } };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void
drawBox(void)
{
	int i;
	if (viewport_mode == 1) {
		glViewport(0, 0, 640 / 2, 480 / 2);
		//glViewport(480 / 2, 640 / 2, 480, 640);
		for (i = 0; i < 6; i++) {
			glBegin(GL_QUADS);
			glColor3f(Red, Green, Blue);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glColor3f(0, 0, 1);
			glVertex3fv(&v[faces[i][1]][0]);
			glColor3f(1, 0, 0);
			glVertex3fv(&v[faces[i][2]][0]);
			glColor3f(0, 1, 0);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();

			glColor3f(1, 1, 1);
			glPointSize(5);
			glBegin(GL_LINE_LOOP);

			//	glNormal3fv(&n[i][0]);

			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}

		glViewport(0,0,640,480);
		for (i = 0; i < 6; i++) {
			glColor3f(0,0,0);
			glPointSize(5);
			glBegin(GL_LINE_LOOP);

			//	glNormal3fv(&n[i][0]);

			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
	}
	else {
		glViewport(0, 0, 640, 480);
		
		for (i = 0; i < 6; i++) {
			glBegin(GL_QUADS);
			glColor3f(Red, Green, Blue);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();

			glColor3f(1, 1, 1);
			glPointSize(5);
			glBegin(GL_LINE_LOOP);

			//	glNormal3fv(&n[i][0]);

			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
	}
}

void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawBox();
	glutSwapBuffers();
}
void menu(int id) {
	switch (id)
	{
	case 1:
		exit(0);
		break;
	case 2:
		Red = 1, Green = 0, Blue = 0;
		break;
	case 3:
		Red = 0, Green = 1, Blue = 0;
		break;
	case 4:
		Red = 0, Green = 0, Blue = 1;
		break;
	case 5:
		viewport_mode = 1;
		break;


	default:
		break;
	}
	glutPostRedisplay();
}

void init(void)
{
	Red = 1; Green = 0; Blue = 0;
	glClearColor(0, 1, 1, 1);
	/* Setup cube vertex data. */
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

	/* Enable a single OpenGL light. */
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHTING);

	glViewport(0, 0, 640, 480);
	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
		glOrtho(-5, 5, -5, 5, -5, 10);
		//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0);      /* up is in positive Y direction */

							/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glPushMatrix();
}
void callback_menu() {
	int sub_menu = glutCreateMenu(menu);
	glutAddMenuEntry("RED", 2);
	glutAddMenuEntry("GREEN", 3);
	glutAddMenuEntry("BLUE", 4);
	glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 1);
	glutAddSubMenu("COLORS", sub_menu);
	glutAddMenuEntry("Wire Frame",5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void handleKeys(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//glLoadIdentity();
	//If the user presses q
	if (key == 'q')
	{
		std::cout << "q is called";
		
		
		glRotatef(1, 0.0, 0.0, 1.0);
		
	}
	if (key == 's')
	{
		glScalef(2, 2, 2);
	}
	if (key == 'w')
	{
		//glMatrixMode(GL_MODELVIEW);
		
		glScalef(.5, .5, .5);
		//glRotatef(1, 0.0, 0.0, 1.0);
	}
	
	//glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
	if (key == 'e') {

	//	gluLookAt(5*cosf(3.14/180),  5.0, 5 * sinf(3.14 / 180),  /* eye is at (0,0,5) */
			gluLookAt(1, 1, 5,  /* eye is at (0,0,5) */
			0.0, 0.0, 0.0,      /* center is at (0,0,0) */
			0.0, 1.0, 0);      /* up is in positive Y direction */
	}
	glPushMatrix();
	if (key == 'r') {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if (PROJECTION == 0) {
			PROJECTION = 1;//perspective
			gluPerspective( /* field of view in degree */ 90.0,
				/* aspect ratio */ 1,
				/* Z near */1, /* Z far */ 8.0);
		}
		else if (PROJECTION == 1) {
			PROJECTION = 0;//ortho
			glOrtho(-4, 4, -4, 4, -5, 10);
		}
	
		//glPushMatrix();
		
	}
	
	//Update projection matrix
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0, 640 * gProjectionScale, 480 * gProjectionScale, 0.0, 1.0, -1.0);
	glutPostRedisplay();
}

int
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("red 3D lighted cube");
	
	
	glutKeyboardFunc(handleKeys);
	callback_menu();
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}