//$Author$
//$Date$
//$Version$
//$Rev$

#include <Objet3D.h>

Objet3D::Objet3D() {
	className = (char*)"Objet3D";
	
	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;
	
	currentMaterialName = (char*)"";
	
	m = new MessagesManager();
	m->setVerbose(false);
}

Objet3D::~Objet3D() {
	glDeleteBuffers(1, &vbo_v);
}

void afficherVertex(Vertex& v);

string Objet3D::getNom() {
	return nom;
}

void Objet3D::setNom(string pNom) {
	nom = pNom;
}

void Objet3D::setPosition(double pX, double pY, double pZ) {
	posX = pX;
	posY = pY;
	posZ = pZ;
	position();
}

long Objet3D::getNbFaces(){
	return faces.size();
}

GLuint* Objet3D::getVertexArrayBuffer(){
	//return vao;
	return 0;
}

long Objet3D::getNbMaterials(){
	return materials.size();
}

vector<Face> Objet3D::getFaces() {
	return faces;
}

Material Objet3D::getMaterial(const char* materialName) {
	map<string,Material>::iterator it;
	it = materials.find(materialName);
	return it->second;
}

void Objet3D::ajouterVertex(double pX, double pY, double pZ, double pW){
	Vertex * v = new Vertex();

	v->setX(pX);
	v->setY(pY);
	v->setZ(pZ);
	
	if (pW > 0) v->setW(pW);

	vertices.insert(vertices.end(), *v);
}

void Objet3D::ajouterVertexNormal(double pX, double pY, double pZ, double pW){
	VertexNormal * vn = new VertexNormal();

	vn->setX(pX);
	vn->setY(pY);
	vn->setZ(pZ);
	if (pW > 0) vn->setW(pW);
	verticesNormal.insert(verticesNormal.end(), *vn);
}

void Objet3D::ajouterFace(int nbParametres, char parametres[4][50], char* nomMateriau){
	int numVertex[4];
	int numVertexTexture[4];
	int numVertexNormal[4];
	int nbVertexInfo;
	int numCas;

	if (nbParametres > 0) {
			
		Face f;

		for(int cpt = 0; cpt < nbParametres;cpt++) {
			numCas = 0;
			nbVertexInfo = sscanf(parametres[cpt], "%d//%d", &numVertex[cpt], &numVertexNormal[cpt]);
			switch(nbVertexInfo){
				case 1:
					nbVertexInfo = sscanf(parametres[cpt], "%d/%d/%d", &numVertex[cpt], &numVertexTexture[cpt], &numVertexNormal[cpt]);
					numCas = nbVertexInfo;
					break;

				case 2:
					numCas = 4;
					break;
			}

			switch(numCas){
				case 1: // cas v
					f.ajouterNumVertex(numVertex[cpt]);
					break;

				case 2: // cas v/vt
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexTexture(numVertexTexture[cpt]);
					break;

				case 3: // cas v/vt/vn
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexTexture(numVertexTexture[cpt]);
					f.ajouterNumVertexNormal(numVertexNormal[cpt]);
					break;

				case 4: // cas v//vn
					f.ajouterNumVertex(numVertex[cpt]);
					f.ajouterNumVertexNormal(numVertexNormal[cpt]);
					break;
			}
			//ASCH - 09/05/2015 - Dans tous les cas ajouter le materiau
			f.setMaterialName(nomMateriau);
		}
		faces.insert(faces.end(), f);
		//Ajoute le nombre de vertex pour un material et le mets a jour	
		Material mat = materials.find(nomMateriau)->second;
		mat.addVertices(f.getNbVertex());		
		materials.erase(nomMateriau);
		materials.insert(pair<string,Material>(mat.getNom(), mat));
		
	}
}

void Objet3D::initMaterial(map<string, Material> * mat) {	
	//materials = mat;	
}

void Objet3D::ajouterMaterial(Material mat) {
	materials.insert(pair<string,Material>(mat.getNom(), mat));
	m->message(MM_INFO, className, "Material ajouté");
	m->message(MM_INFO, className, mat.getNom().c_str());
	//Ambient
	sprintf(mBuffer, "A %f %f %f", mat.getAmbientR(), mat.getAmbientG(), mat.getAmbientB());
	m->message(MM_INFO, className, mBuffer);
	//Diffus
	sprintf(mBuffer, "D %f %f %f", mat.getDiffuseR(), mat.getDiffuseG(), mat.getDiffuseB());
	m->message(MM_INFO, className, mBuffer);
	//speculaire
	sprintf(mBuffer, "S %f %f %f", mat.getSpecularR(), mat.getSpecularG(), mat.getSpecularB());
	m->message(MM_INFO, className, mBuffer);
	//Controle de l'initialisation du vertice
}

void Objet3D::dessiner() {
}

void Objet3D::charger() {
	//ASCH - 16/04/15 - Recodage du chargement en mémoire de la carte graphique
	//---------------------------------------------------------
	
	//ASCH 23/03/2015 - Transformation des collections en tableaux
	//Vertices
	//printf("OBJET3D::CHARGER()\n");
	m->message(MM_INFO, className, "CHARGER()");
	
	//charger en fonction des faces
	vector<Face>::iterator itf;
	
	int nbVertex;
	int nbVertexNormal;
		
	//Init
	long index = 0;	
	map<string, Material>::iterator im;
	vector<Material> mats;
	
	//Pour l'exercice on prends des faces triangles à 3 sommets
	objectIndicesSize = faces.size() * 3;
	int pointeur = 0;
	
	objectIndices = new int[objectIndicesSize - 1];
	
	for(itf = faces.begin(); itf != faces.end(); itf++) {		
		//itf->chargerIndicesDansTabMemoire(objectIndices, pointeur);
		//printf("valeur du pointeur : %d\n", pointeur);
		itf->charger(vertices, verticesNormal, &verticesBuffer, &nbVertex);	
		itf->chargerNormales(verticesNormal, &verticesNormalBuffer, &nbVertexNormal);
	}
	
		
	//----------------------------------------------------------------------------------------
	//Transformation de la collection vector en tableau de float
	
	//Calcul de la taille du tableau
	fvertices_size = verticesBuffer.size() * 4;
	//Réservation du tableau en mémoire
	fvertices = new float[fvertices_size - 1]; // On commence à 0
	
	//Calcul de la taille du tableau
	fverticesKd_size = verticesBuffer.size() * 3;	
		
	// float* fverticesKa = new float[fverticesKa_size - 1]; // On commence à 0
	float* fverticesKd = new float[fverticesKd_size - 1]; // On commence à 0
	// float* fverticesKs = new float[fverticesKa_size - 1]; // On commence à 0			
	
	
	//Init
	index = 0;	
	long indexKd = 0;	
	
	vector<Vertex>::iterator it;
	
	for(it = verticesBuffer.begin(); it != verticesBuffer.end(); it++) {
		fvertices[index] = it->getX();
		fvertices[index + 1] = it->getY();
		fvertices[index + 2] = it->getZ();
		fvertices[index + 3] = it->getW();		

		//Couleurs du vertex - Diffuse
		// ne fonctionne pas comme ça - voir les materials		
		fverticesKd[indexKd] = materials.find(it->getMaterialName())->second.getDiffuseR();
		fverticesKd[indexKd + 1] = materials.find(it->getMaterialName())->second.getDiffuseG();
		fverticesKd[indexKd + 2] = materials.find(it->getMaterialName())->second.getDiffuseB();

		index += 4;
		indexKd +=3;
	}	
	

	//printf("OBJET3D::CHARGER(): transformation vertices OK\n");	
	char s[150];
	sprintf(s, "%s %f", "valeur du Kd.x", fverticesKd[0]);
	m->message(MM_INFO, className, s);
	
	sprintf(s, "valeur du Kd.y %f", fverticesKd[1]);
	m->message(MM_INFO, className, s);
	
	sprintf(s, "valeur du Kd.z %f", fverticesKd[2]);
	m->message(MM_INFO, className, s);
	
	sprintf(s, "valeur du Kd.a %f", fverticesKd[3]);
	m->message(MM_INFO, className, s);
	
	
	/*
	printf("OBJET3D::CHARGER(): valeur du Ka.x %f\n", fverticesKa[0]);
	printf("OBJET3D::CHARGER(): valeur du Ka.y %f\n", fverticesKa[1]);
	printf("OBJET3D::CHARGER(): valeur du Ka.z %f\n", fverticesKa[2]);
	printf("OBJET3D::CHARGER(): valeur du Ka.a %f\n", fverticesKa[3]);
	*/
	//----------------------------------------------------------------------------------------
	// Calcul pour les vecteurs normaux
	
	//Calcul de la taille du tableau
	//Nb de vertex = Nb de normales
	int fverticesN_size = verticesBuffer.size() * 3;
	//Réservation du tableau en mémoire
	float* fverticesNormals = new float[fverticesN_size - 1];
	
	//Init
	index = 0;	
	
	vector<VertexNormal>::iterator itn;
	
	for(itn = verticesNormalBuffer.begin(); itn != verticesNormalBuffer.end(); itn++) {
		fverticesNormals[index] = itn->getX();
		fverticesNormals[index + 1] = itn->getY();
		fverticesNormals[index + 2] = itn->getZ();
		index += 3;
	}	
	//printf("OBJET3D::CHARGER(): Transformation vecteurs normaux OK\n");		
	//----------------------------------------------------------------------------------------
	
	//Vertex
	vbo_v = 0;
	
	glGenBuffers (1, &vbo_v);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_v);
	glBufferData (GL_ARRAY_BUFFER, fvertices_size * sizeof (float), fvertices, GL_STATIC_DRAW);
	//printf("OBJET3D::CHARGER(): vbo_v OK\n");
	
	//tableau des vecteurs normaux
	vbo_vn = 0;
	
	glGenBuffers (1, &vbo_vn);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_vn);
	glBufferData (GL_ARRAY_BUFFER, fverticesN_size * sizeof (float), fverticesNormals, GL_STATIC_DRAW);	

	/*
	//Eclairage - Couleur ambiante
	// On utilise la même taille que pour la couleur ambiante (fverticesKa_size)
	vbo_Ka = 0;
	
	glGenBuffers (1, &vbo_Ka);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ka);
	glBufferData (GL_ARRAY_BUFFER, fverticesKa_size * sizeof (float), fverticesKa, GL_STATIC_DRAW);			
	*/
	
	//Eclairage - Couleur diffuse
	// On utilise la même taille que pour la couleur ambiante (fverticesKa_size)
	vbo_Kd = 0;
	
	glGenBuffers (1, &vbo_Kd);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Kd);
	glBufferData (GL_ARRAY_BUFFER, fverticesKd_size * sizeof (float), fverticesKd, GL_STATIC_DRAW);			
	
	/*
	vbo_Ks = 0;
	//printf("OBJET3D::CHARGER(): vbo_Kd OK\n");
	
	//Vertex - Specular
	glGenBuffers (1, &vbo_Ks);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ks);
	glBufferData (GL_ARRAY_BUFFER, fverticesKa_size * sizeof (float), fverticesKs, GL_STATIC_DRAW);
	//printf("OBJET3D::CHARGER(): vbo_Ks OK\n");	
	*/
	// Désallocations
	delete[] fverticesNormals;
	delete[] fvertices;
//	delete[] fverticesKa;
	delete[] fverticesKd;
}


void Objet3D::construireVAO(GLuint vao, int offset) {	

	m->message(MM_INFO, className, "construireVAO(GLuint vao, int offset)");
	glBindVertexArray (vao);
	
	charger();
	
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_v);
	glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_vn);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	
	//ASCH - 10/05/2015 - Materiau
	//Ambient
	glEnableVertexAttribArray (2);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Kd);	
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	/*
	//Diffuse
	glEnableVertexAttribArray (3);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Kd);	
	glVertexAttribPointer (3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	//Specular
	glEnableVertexAttribArray (4);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ks);	
	glVertexAttribPointer (4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	*/
	
	glEnableVertexAttribArray (0);
	glBindVertexArray(0); //termine le binding pour ce vertex array (unbind)
	verticesNormalBuffer.clear();
}


void Objet3D::afficher() {
	/*
	printf("OBJET3D::AFFICHER()\n");
	// Verrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, uid);
	
	// Accès aux vertices dans la mémoire vidéo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer(3, GL_FLOAT, 0, fvertices); 
	
	glDrawBuffer(GL_FRONT_AND_BACK);
	//glDrawElements(GL_TRIANGLES, objectIndicesSize, GL_UNSIGNED_BYTE, objectIndices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
			
	// Déverrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	printf("OBJET3D::FIN AFFICHER()\n");
	*/
}

long Objet3D::getNbVertex(){
	return verticesBuffer.size();
}

//ASCH - 12/12/2015 - positionne l'objet dans la scene (cf. setPosition)
void Objet3D::position() {
	// Calcul de la translation
	vector<Vertex>::iterator it;
		
	for(it = vertices.begin(); it != vertices.end(); it++) {
		it->setX(it->getX() + posX);
		it->setY(it->getY() + posY);
		it->setZ(it->getZ() + posZ);
	}
	
}

map<string, Material> Objet3D::getMaterialMap() {
	return materials;
}