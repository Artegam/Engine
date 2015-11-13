/************************************************/
/*	Source : http://www.games-creators.org/	*/
/************************************************/
 
//#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
 
#define WIDTH 640
#define HEIGHT 480
 
void Display();
void Reshape(int,int);
void Idle();
void Init();
void Creer_Cube();
 
int id_cube=0;
int angle=0;
 
////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[ ])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // mode double buffering + z-buffer
 
  glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Scène 3D Animée");
 
	Init();
 
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
 
	glutMainLoop();
	return 0;
}
 
void Init()
{
	glEnable(GL_DEPTH_TEST);
	Creer_Cube();
}
 
void Creer_Cube()
{
	id_cube=glGenLists(1);
	glNewList (id_cube,GL_COMPILE); 
	glBegin(GL_QUADS); 
	glColor3d(1,0,0);
	glVertex3i(1,1,1);
	glVertex3i(1,-1,1);
	glVertex3i(-1,-1,1);
	glVertex3i(-1,1,1);
 
	glColor3d(0,1,0);
	glVertex3i(1,1,-1);
	glVertex3i(1,-1,-1);
	glVertex3i(-1,-1,-1);
	glVertex3i(-1,1,-1);
 
	glColor3d(0,0,1);
	glVertex3i(1,1,1);
	glVertex3i(1,-1,1);
	glVertex3i(1,-1,-1);
	glVertex3i(1,1,-1);
 
	glColor3d(0,1,1);
	glVertex3i(-1,1,1);
	glVertex3i(-1,-1,1);
	glVertex3i(-1,-1,-1);
	glVertex3i(-1,1,-1);
 
	glColor3d(1,1,0);
	glVertex3i(-1,1,-1);
	glVertex3i(-1,1,1);
	glVertex3i(1,1,1);
	glVertex3i(1,1,-1);
 
	glColor3d(1,0,1);
	glVertex3i(-1,-1,-1);
	glVertex3i(-1,-1,1);
	glVertex3i(1,-1,1);
	glVertex3i(1,-1,-1);
 
	glEnd(); 
	glEndList(); 
}
 
void Idle()
{
	angle+=5;
	if (angle>360) angle=0;
	glutPostRedisplay();
}
 
void Display()
{
	glClearColor(0,0,0,0); // selectionne la couleur noire (qui est celle par défaut)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10,15,15,0,0,0,0,1,0);
 
	glCallList(id_cube);
 
	glPushMatrix();
	glRotated(angle,0,1,0);
	glTranslatef(0,0,-5);
	glScaled(0.5,0.5,0.5);
	glCallList(id_cube);
	glPopMatrix();
 
	glPushMatrix();
	glRotated(angle,0,1,0);
	glTranslatef(0,0,5);
	glRotated(angle,0,1,0);
	glScaled(0.5,0.5,0.5);
	glCallList(id_cube);
	glPopMatrix();
 
	glutSwapBuffers();
	glFlush();
}
 
void Reshape(int w, int h) 
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION); // Choisit la matrice de projection
	glLoadIdentity();
	gluPerspective(45.0,(float) w/h,1.,100.);
	glMatrixMode(GL_MODELVIEW); // on revient sur la matrice MODELVIEW
	glLoadIdentity();	
}
