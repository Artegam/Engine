#include <ObjParser.h>

//ASCH - 17/10/2014 - Paramètres

//ASCH - 17/10/2014 - Méthodes
vector<Objet3D> ObjParser::readFile (const char * filename, vector<Objet3D> pObjets) {

	FILE* fichier;
	char ligne[255];
	
	objets = pObjets;
	cptFaces = 0;
	cptObjects = 0;
	vObj = new Objet3D(); //Un objet par fichier
	vObj->setNom(filename);
	printf("OBJPARSER::READFILE() nombre de points : %d\n", vObj->getNbVertex());
	
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
		
		if(strcmp((const char*)ligne, (char*)"usemtl") == 0)
			readMaterial(fichier);
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
		vObj->ajouterFace(nbParametres, parametres, "");

	cptFaces++;
}

void ObjParser::readMaterial(FILE* fichier) {
	printf("READMATERIAL()\n");
}

void ObjParser::insertObject() {
	objets.insert(objets.end(), *vObj);
}