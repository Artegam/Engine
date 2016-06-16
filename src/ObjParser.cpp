#include <ObjParser.h>

//ASCH - 17/10/2014 - Paramètres

//ASCH - 17/10/2014 - Méthodes

ObjParser::ObjParser() {
	m = new MessagesManager();
	className = (char*)"ObjParser";
}

vector<Objet3D> ObjParser::readFile (const char * filename, vector<Objet3D> pObjets) {

	FILE* fichier;
	char ligne[255];
	
	objets = pObjets;
	cptFaces = 0;
	cptObjects = 0;
	vObj = new Objet3D(); //Un objet par fichier
	vObj->setNom(filename);
	
	fichier = fopen(filename, "r");
	
	while(!feof(fichier)) {
		ligne[0] = '\0';
		fscanf(fichier, "%s", ligne);

		if(strcmp((const char*)ligne, (char*)"v") == 0)
			readVertex(fichier);

		if(strcmp((const char*)ligne, (char*)"vn") == 0)
			readVertexNormal(fichier);

		if(strcmp((const char*)ligne, (char*)"o") == 0)
			readObject(fichier);

		if(strcmp((const char*)ligne, (char*)"f") == 0)
			readFace(fichier);
		
		if(strcmp((const char*)ligne, (char*)"mtllib") == 0) {
			readMaterialLibrary(fichier);
			char mtlfilename[50];
			sprintf(mtlfilename, ".\\ressources\\%s", nomMtlLib);
			readMtlFile(mtlfilename);
		}
		
		if(strcmp((const char*)ligne, (char*)"usemtl") == 0)
			readMaterialUsed(fichier);
	}
	
	//ASCH 02/08/15 - Insère le dernier objet lu en mémoire.
	insertObject();
	cptFaces = 0;	
	fclose(fichier);
	return objets;
}

void ObjParser::readVertex(FILE* fichier){
	double x;
	double y;
	double z;
	double w = -1.0;

	fscanf(fichier, "%lf %lf %lf %lf", &x, &y, &z, &w);
	if(w > 0)
		vObj->ajouterVertex(x, y, z, w);
	else
		vObj->ajouterVertex(x, y, z, 1.0);
}

void ObjParser::readVertexNormal(FILE* fichier){
	double x;
	double y;
	double z;
	double w;

	fscanf(fichier, "%lf %lf %lf %lf", &x, &y, &z, &w);
	vObj->ajouterVertexNormal(x, y, z, w);
}

void ObjParser::readObject(FILE* fichier){
	char nom[255];
	
	fscanf(fichier, "%s", nom);	
	printf("\t - %s\n", nom);
	cptObjects++;
}

void ObjParser::readFace(FILE* fichier) {	
	char parametres[4][50];
	int numVertex[4];
	int numVertexTexture[4];
	int numVertexNormal[4];
	int nbParametres;
	int nbVertexInfo;
	char ligne[255] = " ";
	char car = 0;
	int cpt = 0;
	
	while(car != 10 && cpt < 255) { // or car != '\n' or car != '\r') {
		cpt++;
		car = fgetc(fichier);
		if (car != 10)
			ligne[cpt] = car;
	}
	
	// Ici erreur de lecture avec le nb de parametres variable.
	nbParametres = sscanf(ligne, "%s %s %s %s", parametres[0], parametres[1], parametres[2], parametres[3]);
	if (nbParametres == EOF)
		printf("Erreur de lecture : %s", ligne);

	if (nbParametres >= 3)
		vObj->ajouterFace(nbParametres, parametres, nomMaterialCourrant);

	cptFaces++;
}

void ObjParser::readMaterial(FILE* fichier) {
	//ASCH 28/05/2016 - Lire la définition d'un material
	m->message(MM_INFO, className, "Lecture de definition de material non definie");
}

void ObjParser::readMaterialUsed(FILE* fichier) {
	fscanf(fichier, "%s", &nomMaterialCourrant);
	sprintf(mBuffer, "nom material utilise : %s\n", nomMaterialCourrant);
	m->message(MM_INFO, className, mBuffer);
}

void ObjParser::readMaterialLibrary(FILE* fichier) {	
	fscanf(fichier, "%s", &nomMtlLib);
	sprintf(mBuffer, "Nom de mtllib : %s", nomMtlLib);
	m->message(MM_INFO, className, mBuffer);
}

void ObjParser::insertObject() {
	objets.insert(objets.end(), *vObj);
}

void ObjParser::readMtlFile(const char* filename) {
	sprintf(mBuffer, "Lecture du fichier %s...", filename);
	m->message(MM_INFO, className, mBuffer);
	
	FILE* fichier;
	char ligne[255];
	
	/* Exemple de declaration dans un fichier mtl
	# Blender MTL File: 'None'
	# Material Count: 2

	newmtl Bois
	Ns 96.078431
	Ka 0.000000 0.000000 0.000000
	Kd 0.640000 0.640000 0.640000
	Ks 0.500000 0.500000 0.500000
	Ni 1.000000
	d 1.000000
	illum 2
	*/	
	
	fichier = fopen(filename, "r");
	
	while(!feof(fichier)) {
		ligne[0] = '\0';
		fscanf(fichier, "%s", ligne);

		if(strcmp((const char*)ligne, (char*)"newmtl") == 0)
			readNewMaterial(fichier);

		if(strcmp((const char*)ligne, (char*)"Ns") == 0)
			readSpecularExponent(fichier);
	
		if(strcmp((const char*)ligne, (char*)"Ka") == 0)
			readAmbient(fichier);
			
		if(strcmp((const char*)ligne, (char*)"Kd") == 0)
			readDiffuse(fichier);
			
		if(strcmp((const char*)ligne, (char*)"Ks") == 0)
			readSpecular(fichier);
	
/*
		if(strcmp((const char*)ligne, (char*)"Ni") == 0)
			
		if(strcmp((const char*)ligne, (char*)"d") == 0)
			
		if(strcmp((const char*)ligne, (char*)"illum") == 0)
*/

	}
}

void ObjParser::readNewMaterial(FILE* fichier) {	
	char nomMaterial[50];
	//if(vObj->getNbMaterials() > 0) {
	fscanf(fichier, "%s", &nomMaterial);
	mat = 0;
	mat = new Material(nomMaterial);
}

void ObjParser::readSpecularExponent(FILE* fichier) {
	double val;
	fscanf(fichier, "%f", &val);
	mat->setSpecularExponent(val);
}

void ObjParser::readAmbient(FILE* fichier) {
	float r;
	float g;
	float b;
	fscanf(fichier, "%f %f %f", &r, &g, &b);
	mat->setAmbient(r, g, b);
}

void ObjParser::readDiffuse(FILE* fichier) {
	float r;
	float g;
	float b;
	fscanf(fichier, "%f %f %f", &r, &g, &b);
	mat->setDiffuse(r, g, b);
}

void ObjParser::readSpecular(FILE* fichier) {
	float r;
	float g;
	float b;
	fscanf(fichier, "%f %f %f", &r, &g, &b);
	mat->setSpecular(r, g, b);
	vObj->ajouterMaterial(*mat); //A faire sur l'instruction illum
}