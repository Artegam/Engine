#include <GL/GLee.h>
#include <GL/freeglut.h>
#include <windows.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <ObjParser.h>
#include <MtlParser.h>
#include <Objet3D.h>

//ASCH - 02/03/2015 - Test includes
#include <UnitTestLoader.h>

// Macro utile au VBO
#ifndef BUFFER_OFFSET
  #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using namespace std;

//Fonctions écrites en shader 4.0.0 pour le traitement des vao et vbo dans la carte graphique
const char* vertex_shader =
"#version 300\n"
""
"in vec4 vp;"
"in vec3 vn;"
"varying vec3 norm;"
"varying vec4 v;"
""
"void main () {"
"  gl_Position = gl_ModelViewProjectionMatrix * vp;"
"  norm = gl_NormalMatrix * normalize(vn);" //gl_NormalMatrix * //TODO Correction
"  v = gl_ModelViewMatrix * vp;"
"}";

const char* fragment_shader =
"#version 400\n"
"precision highp float;"
"in vec4 vKa;"
"in vec4 vKd;"
"in vec4 vKs;"
"out vec4 frag_colour;"
"varying vec4 v;"
"varying vec3 norm;"
"void main () {"
		//Diffuse
"    vec3 L = normalize(gl_LightSource[0].position.xyz - v.xyz);"
//"    vec4 Idiff = vec4(0.0, 0.512, 0.250, 0.0) * gl_LightSource[0].diffuse * max(dot(norm, L), 0.0);"
//"    vec4 Idiff = vec4(vKd.x, vKd.y, vKd.z, vKd.w) * gl_LightSource[0].diffuse * max(dot(norm, L), 0.0);"
//"    vec4 Idiff = vKd * gl_LightSource[0].diffuse * max(dot(norm, L), 0.0);"
"    vec4 Idiff = gl_LightSource[0].diffuse * max(dot(norm, L), 0.0);"
"    Idiff = clamp(Idiff, 0.0, 1.0);"
"    frag_colour = Idiff;"
"}";

// FIN Fonctions shaders


//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

//Variables
vector<Objet3D> objets;
map<string, Material> materials;
vector<Objet3D>::iterator it;
map<string, Material>::iterator im;
int angle;
const int delayms = 30;
long nbVertex = 0;
bool displayWireMode;
int uid;

//Shaders variables
GLuint shader_programme;
GLuint* vao;
GLuint vbo = 0;
GLuint vbo_c = 0;
GLuint vbo_Ka = 0;
GLuint vs; 
GLuint fs;

//Déclarations
void initLight(void);
void idle(void);
void Reshape(int w, int h);
void render(void);
void keyboard(unsigned char c, int x, int y);
void mouse(int button, int state, int x, int y);
void timerFunction(int arg);
GLuint loadingObject();
void cleanShaders();
void initShaders();

int main(int argc, char** argv) {

	ObjParser * parser = new ObjParser();
	MtlParser * mtl = new MtlParser();

	angle = -1.0;
	float valZoom = 0.0;

	// Pour un écran Widescreen ratio d'aspect = 16:9
	long width = 800;
	long height = 450;
	float zNear = 0.1;
	float zFar = 100.0;
	float zoomFactor = 1.0;
	
	//Execution des tests unitaires
	if (argv[1][0] == 't' && argc == 2) {
		UnitTestLoader * testsUnitaires = new UnitTestLoader();
		testsUnitaires->charger();
		testsUnitaires->executer();
		return 0;
	}

	//25/09/2015 - Lecture du terrain
	objets = parser->readFile(".\\obj\\terrain.obj", objets);
	
	//Lecture des fichiers obj et mtl
	if (argv[1] != NULL && argv[2] != NULL) {
		printf("MAIN: Lecture du fichier... \t %s\n", argv[1]);
		objets = parser->readFile(argv[1], objets);
		//printf("Lecture du fichier... \t %s\n", argv[2]);
		//materials = mtl->readMaterials(argv[2]);
	} else {
		printf("MAIN: Veuillez passer en argument le nom du fichier obj et mtl (exemple: ./essai3D ./obj/jaguard.obj ./mtl/jaguard.mtl\n");
		return 0;
	}
	
	for (int i = 0; i < objets.size(); i++)
		printf("MAIN: READ nbFaces obj %i : %d\n", i, objets[i].getNbFaces());
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(argv[1]);

	initShaders();
	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Initialisation des matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Réglages pour la profondeur de champ
	gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);

	initLight();
	gluLookAt(0.0, 5.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutDisplayFunc(render);
	//glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
 
	glutTimerFunc(delayms, timerFunction, 0);
 
	glutMainLoop();
	
	//ASCH  06/03/2014 - Libération de la mémoire
	parser->~ObjParser();
	mtl->~MtlParser();
}


void initLight(void) 
{
	
	//Shaders
	glShadeModel(GL_SMOOTH);

	//Lights
	GLfloat light_position[] = { 0.0, 10.0, 4.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_diffuse[] = { 0.25, 0.75, 0.25, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SHININESS, light_diffuse);
	
	//Activation de l'éclairage
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	//Surfaces
	
	//vertex Materials pour refleter la lumière (matériau par defaut)
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	
}

void idle(void) {
	glutSwapBuffers();
}

void render(void) {
	//glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(angle,0.0,1.0,0.0);

  glUseProgram (shader_programme);
  // draw points 0-3 from the currently bound VAO with current in-use shader
	for(int i=0;i < objets.size();i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays (GL_TRIANGLES, 0, objets[i].getNbVertex());
	}
	
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport( 0, 0, (GLint)w, (GLint)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y) {
	// ASCH - 29/09/2014 - La touche 27 est la touche echap
	if (c == 27) {
		//Desallocation
		printf("MAIN: Sortie du programme \n");
		cleanShaders();
		exit(0);
	}		

	if (c == 'l') {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
		displayWireMode = !displayWireMode;
	}
	
	if (c == 'p') {
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
		displayWireMode = !displayWireMode;
	}
	
	if (c == 'f') {		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
		displayWireMode = !displayWireMode;
	} 		
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_RIGHT_BUTTON) exit(0);
}

void timerFunction(int arg)
{
	render();
	glutPostRedisplay();
	glutTimerFunc(delayms, timerFunction, 0);
}

void cleanShaders() {
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glUseProgram(0);
	
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vbo_c);
	glDeleteBuffers(1, &vbo_Ka);
	
	glDeleteVertexArrays(objets.size(), vao);
	
	glDetachShader(shader_programme, vs);
	glDetachShader(shader_programme, fs);
	
	glDeleteShader(vs);
	glDeleteShader(fs);
	
	glDeleteProgram(shader_programme);
}

void initShaders() {
	printf("MAIN.initShaders()\n");
	// get version info
	const GLubyte* vendor = glGetString (GL_VENDOR); // Fournisseur
  const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("MAIN.initShaders: Fournisseur: %s\n", vendor);
  printf ("MAIN.initShaders: Renderer: %s\n", renderer);
  printf ("MAIN.initShaders: OpenGL version supported %s\n", version);
	// FIN get version info		

	//Creation des shaders
	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	
	GLint IsCompiled_VS;
	
	glGetShaderiv(vs, GL_COMPILE_STATUS, &IsCompiled_VS);
    if(IsCompiled_VS == FALSE)
			printf("MAIN.initShaders: Erreur de compilation de shader\n");
		else	
			printf("MAIN.initShaders: vs shader OK\n");
		
	fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);	
	
	glGetShaderiv(fs, GL_COMPILE_STATUS, &IsCompiled_VS);
		if(IsCompiled_VS == FALSE)
			printf("MAIN.initShaders: Erreur de compilation de shader\n");
		else
			printf("MAIN.initShaders: fs shader OK\n");
	
	//FIN Creation des shaders
	
	//Shader programme
	shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, vs);
	glAttachShader (shader_programme, fs);
	//glBindAttribLocation(shader_programme, 0, "in_Position");	

	//ASCH 24/09/2015 - Modification pour prendre en compte le multiobjet
	printf("---- taille : %d\n", objets.size());
	vao = new GLuint[objets.size()];

	//Création des tableaux en mémoire
	glGenVertexArrays (objets.size(), vao);
	
	// ASCH 20/04/2015 - Chargement des objets en mémoire graphique
	for(int i = 0; i < objets.size(); i++) {
		objets[i].construireVAO(vao[i], i);
		nbVertex += objets[i].getNbVertex();
		
		// insert location binding code here
		glBindAttribLocation (shader_programme, 0, "vp");
		glBindAttribLocation (shader_programme, 1, "vn");
		glBindAttribLocation (shader_programme, 2, "vKa");
		glBindAttribLocation (shader_programme, 3, "vKd");
		glBindAttribLocation (shader_programme, 4, "vKs");		
	}
	printf("MAIN: Nb d'objets : %d\n", objets.size());
	//printf("MAIN: Nombre total de vertex : %d\n", nbVertex);

	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);
	//FIN Shader programme
}
