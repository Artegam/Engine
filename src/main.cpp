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
#include <Rail.h>
#include <Terrain.h>

//TODO - A simplifier
#include <ObjetDeScene.h>
#include <Transformation.h>
#include <ShaderManager.h>
#include <KeyboardManager.h>
#include <MessagesManager.h>

//ASCH - 02/03/2015 - Test includes
#include <UnitTestLoader.h>

// Macro utile au VBO
#ifndef BUFFER_OFFSET
  #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using namespace std;

//Ligne de commande de compilation
//g++ monPremierEssai.cpp -lGL -lglut -o monPremierEssai

//Variables
vector<Objet3D> objets;
vector<ObjetDeScene*> objetsDeScene;

//vector<Transformation> transformations;
map<string, Material> materials;
map<long, vector<Transformation> > transformations;

map<long, vector<Transformation> >::iterator itTransf;

const int delayms = 30;
long nbVertex = 0;
int uid;
int windowID;

Rail * rail;

//Shaders variables
ShaderManager sm;
KeyboardManager km;
MessagesManager mm;
char mBuffer[150];
char className[5] = "MAIN";
GLuint shader_programme;
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
void messageProgression(int pourcent);
//void test();
void desallocation();
void ajouterDansListeDAffichage(ObjetDeScene * obj);
void fabriquerListeAffichage(vector<ObjetDeScene*> lst);
void dessiner(ObjetDeScene * obj);
void charger(ObjetDeScene * obj);
void chargerScene();

void vBitmapOutput(int x, int y, const char *str, void *font);

int main(int argc, char** argv) {

	ObjParser * parser = new ObjParser();
	MtlParser * mtl = new MtlParser();


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
	
	chargerScene();
	/*
	for (int i = 0; i < objets.size(); i++) {
		sprintf(mBuffer, "READ nbFaces obj %i : %d", i, objets[i].getNbFaces());
		mm.message(MM_INFO, className, mBuffer);
	}
	*/
		//printf("MAIN: READ nbFaces obj %i : %d\n", i, objets[i].getNbFaces());

	//Initialisation des paramètres graphiques
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_LUMINANCE);
	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	windowID = glutCreateWindow(argv[1]);

	initShaders();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Initialisation des matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Réglages pour la profondeur de champ
	gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar);
	
	glMatrixMode(GL_COLOR);
	glMatrixMode(GL_MODELVIEW);

	initLight();
	//gluLookAt(0.0, 5.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0);

	mm.message(MM_INFO, className, "trace avant display");
	glutDisplayFunc(render);
	mm.message(MM_INFO, className, "trace apres display");
	
	//glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
 
	mm.message(MM_INFO, className, "trace apres glutfunc");
 
	glutTimerFunc(delayms, timerFunction, 0); 
	mm.message(MM_INFO, className, "trace avant Loop");
	glutMainLoop();
	mm.message(MM_INFO, className, "trace apres Loop");
	
	//ASCH  06/03/2014 - Libération de la mémoire
	parser->~ObjParser();
	mtl->~MtlParser();
	
	mm.message(MM_INFO, className, "terminee");
}


void initLight(void) 
{	
	GLfloat light_position[] = {10.0, 10.0, -10.0, 1.0};
	GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; // Puissance de la lumière
	GLfloat light_spec[] = {1.0, 1.0, 1.0, 1.0}; 
	GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	
	//Shaders
	glShadeModel(GL_SMOOTH);

	//Lights positions
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//Lights colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);	
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	
	
	//Activation de l'éclairage
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Activation des materiaux
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_ALPHA_TEST);
	
	glDisable(GL_CULL_FACE);
	
	//Pour la composante Alpha
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//fin composante alpha
	

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColorMaterial(GL_FRONT, GL_EMISSION);
	glColorMaterial(GL_FRONT, GL_SHININESS);
	
	//Surfaces	
	//vertex Materials pour refleter la lumière (matériau par defaut)
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
}

void idle(void) {
	glutSwapBuffers();
}

void render(void) {
	
	//glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
  glUseProgram (shader_programme);		
		
	for_each(objetsDeScene.begin(), objetsDeScene.end(), dessiner);

	glutSwapBuffers();
}

/*
DOCUMENTATION

  float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
  float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
  float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
  float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
	

  glRotatef(g_fTeapotAngle, 0, 0, 1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
  glColor4fv(colorBlue);
  glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
  DrawCubeWithTextureCoords(1.0);

  // Child object (teapot) ... relative transform, and render
  glPushMatrix();
  glTranslatef(2, 0, 0);
  glRotatef(g_fTeapotAngle2, 1, 1, 0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
  glColor4fv(colorBronzeDiff);
  glBindTexture(GL_TEXTURE_2D, 0);
  glutSolidTeapot(0.3);
  glPopMatrix();	
*/


void Reshape(int w, int h) {
	glViewport( 0, 0, (GLint)w, (GLint)h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y) {
	km.executer(c, x, y);
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

void initShaders() {	
	//ASCH - 25/05/2016 - Initialisation des shaders	
	sm.init();
	shader_programme = sm.getShader_programme();
	vs = sm.getVertexShader(); 
	fs = sm.getFragShader();	
	
	//ASCH 25/05/2016 - Chargement des objets de scene
	for_each(objetsDeScene.begin(), objetsDeScene.end(), charger);
	
	/* A CONTROLER DANS LA CLASSE ObjetDeScene ou shaderManager
	//ASCH 24/09/2015 - Modification pour prendre en compte le multiobjet
	printf("---- taille : %d\n", objets.size());
	vao = new GLuint[objets.size()];

	//Création des tableaux en mémoire
	glGenVertexArrays (objets.size(), vao);
	
	// ASCH 20/04/2015 - Chargement des objets en mémoire graphique
	for(int i = 0; i < objets.size(); i++) {
		objets[i].construireVAO(vao[i], i);
		nbVertex += objets[i].getNbVertex();
	}	
	*/
}

void messageProgression(int pourcent) {
	sprintf(mBuffer, "Chargement... %d %%", pourcent);
	mm.message(MM_INFO, className, mBuffer);
}
/*
void test(){
	glPushMatrix();
		glBindVertexArray(vao[3]);
		glTranslatef(0.0, 0.0, 2.0);
		glDrawArrays (GL_TRIANGLES, 0, objets[3].getNbVertex());
	glPopMatrix();	
}
*/
void desallocation(){
	rail->~Rail();
}

void ajouterDansListeDAffichage(ObjetDeScene * obj) {
	vector<Objet3D> objetsAAjouter = obj->getObjets();
	for(int i=0;i < objetsAAjouter.size();i++) {
		objets.insert(objets.end(), objetsAAjouter[i]);
		vector<Transformation> t = obj->getTransformations();		
		transformations.insert(transformations.end(), std::pair<long,vector<Transformation> >(objets.size()-1, t)); //Ajoute les transformations
	}
}

void fabriquerListeAffichage(vector<ObjetDeScene*> lst){
	objets.clear();
	for(int i = 0; i < lst.size(); i++) {
		ajouterDansListeDAffichage(lst[i]);
	}
}

void dessiner(ObjetDeScene * obj) {
	obj->draw();
}

void charger(ObjetDeScene * obj) {
	obj->load();
}


//-------------------RECHERCHES A FAIRE-----------------------------------------------
void vBitmapOutput(int x, int y, const char *str, void *font)
{
	int len,i; // len donne la longueur de la chaîne de caractères

	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);
	
	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(str); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) 
		glutBitmapCharacter(font,str[i]); // Affiche chaque caractère de la chaîne
	
}

void chargerScene(){

	/*
	ObjetDeScene * obj = new ObjetDeScene();
	obj->chargerFichier(".\\ressources\\terrain.obj");
	objetsDeScene.insert(objetsDeScene.end(), *obj);
	obj->printNbTranformations();
	obj->addTranslation(1.0, 0.0, 0.0);
	obj->printNbTranformations();
	printf("---\n");
	objetsDeScene[0].printNbTranformations();
	printf("***\n");
	
	//remplace l'objet modifié dans la liste
	objetsDeScene.erase(objetsDeScene.end());
	objetsDeScene.insert(objetsDeScene.end(), *obj);
	objetsDeScene[0].printNbTranformations();
	printf("###\n");
	*/

	
	ObjetDeScene * obj = new Terrain(&sm);
	objetsDeScene.insert(objetsDeScene.end(), obj);

/*	
	rail = new Rail(&sm);
	rail->addRotation(45.0, 0.0, 1.0, 0.0);
	objetsDeScene.insert(objetsDeScene.end(), rail);

	
	//Ajoute un second rail
	rail = new Rail(&sm);
	rail->addTranslation(5.0, 0.0, 0.0);
	objetsDeScene.insert(objetsDeScene.end(), rail);
*/	

	obj = new ObjetDeScene(&sm);
	obj->chargerFichier(".\\ressources\\cube.obj");
	obj->addTranslation(10.0, 10.0, -10.0);
	obj->addAnimeRotation(1.0, 0.0, 1.0, 0.0, -1); // rotation pendant 250 tics suivant l'axe Y de 1 degrees
	objetsDeScene.insert(objetsDeScene.end(), obj);
	
	obj = new ObjetDeScene(&sm);
	obj->chargerFichier(".\\ressources\\coin_de_mur_de_chateau.obj");
	objetsDeScene.insert(objetsDeScene.end(), obj);	
	

	obj = new ObjetDeScene(&sm);
	obj->chargerFichier(".\\ressources\\rail_double_virage45.obj");
	// obj->chargerFichier(".\\ressources\\Blaster_triangles.obj");
	//obj->chargerFichier(".\\ressources\\rail_triangles.obj");
	objetsDeScene.insert(objetsDeScene.end(), obj);
	
	//ASCH 25/05/2016 - OBSOLETE
	//Fabrique la liste d'affichage pour les objets 3D
	//fabriquerListeAffichage(objetsDeScene);
	
	messageProgression(100);
	
	//printf("nb objets : %d\n", objets.size());
	mm.message(MM_INFO, className, "Positions calculees...");
	sprintf(mBuffer, "nb d'objets de scene : %d", objetsDeScene.size());
	mm.message(MM_INFO, className, mBuffer);

	//10/12/15 - Fichier pourri ? Options de génération du fichier dans blender ?
	//objets = parser->readFile(".\\ressources\\dewoitine2.obj", objets);	

}