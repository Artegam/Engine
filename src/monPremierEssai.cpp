#include <windows.h>
#include <GL/glut.h>
#include <iostream>
//#include "ObjParser.h"


using namespace std;

//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {

	//ObjParser * parser = new ObjParser(); 

	//parser->readFile("./rail.obj");
	//parser->~ObjParser();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 480);
  glutCreateWindow("premierEssai");

  glutDisplayFunc(render);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(-0.5, -0.5);
    glColor3f(0, 1, 0);
    glVertex2f(0.5, -0.5);
    glColor3f(0, 0, 1);
    glVertex2f(0.0, 0.5);
  glEnd();

  glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y){
  // ASCH - 29/09/2014 - La touche 27 est la touche echap
  if (c == 27) {
    exit(0);
  }
}

void mouse(int button, int state, int x, int y){
  if(button == GLUT_RIGHT_BUTTON) {
    exit(0);
  }
}


