//$Author$
//$Date$
//$Version$
//$Rev$

#include <Objet3D.h>


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

long Objet3D::getNbFaces(){
	return faces.size();
}

GLuint* Objet3D::getVertexArrayBuffer(){
	//return vao;
	return 0;
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

void Objet3D::ajouterFace(int nbParametres, char parametres[4][50], string nomMateriau){
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
	}
}

void Objet3D::initMaterial(map<string, Material> * mat) {	
	materials = mat;	
}

void Objet3D::dessiner() {
}

void Objet3D::charger() {
	//ASCH - 16/04/15 - Recodage du chargement en mémoire de la carte graphique
	//---------------------------------------------------------
	
	//ASCH 23/03/2015 - Transformation des collections en tableaux
	//Vertices
	printf("OBJET3D::CHARGER()\n");
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
	
	//Calcul de la taille du tableau
	int fverticesKa_size = verticesBuffer.size() * 4;	
		
	float* fverticesKa = new float[fverticesKa_size - 1]; // On commence à 0
	float* fverticesKd = new float[fverticesKa_size - 1]; // On commence à 0
	float* fverticesKs = new float[fverticesKa_size - 1]; // On commence à 0		
	
	//La meme taille de tableau est utilisee (fverticesKa_size)
	vbo_Ka = 0;
	
	//Vertex - Ambiant
	glGenBuffers (1, &vbo_Ka);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ka);
	glBufferData (GL_ARRAY_BUFFER, fverticesKa_size * sizeof (float), fverticesKa, GL_STATIC_DRAW);		
	
	//printf("OBJET3D::CHARGER(): vbo_Ka OK\n");

	vbo_Ks = 0;
	//printf("OBJET3D::CHARGER(): vbo_Kd OK\n");
	
	//Vertex - Specular
	glGenBuffers (1, &vbo_Ks);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ks);
	glBufferData (GL_ARRAY_BUFFER, fverticesKa_size * sizeof (float), fverticesKs, GL_STATIC_DRAW);
	//printf("OBJET3D::CHARGER(): vbo_Ks OK\n");
	
	//----------------------------------------------------------------------------------------
	//Transformation de la collection vector en tableau de float
	
	//Calcul de la taille du tableau
	fvertices_size = verticesBuffer.size() * 8;
	//Réservation du tableau en mémoire
	fvertices = new float[fvertices_size - 1]; // On commence à 0
	//Init
	index = 0;	
	
	vector<Vertex>::iterator it;
	
	for(it = verticesBuffer.begin(); it != verticesBuffer.end(); it++) {
		fvertices[index] = it->getX();
		fvertices[index + 1] = it->getY();
		fvertices[index + 2] = it->getZ();
		fvertices[index + 3] = it->getW();		
		
		//Couleurs du vertex - Diffuse
		fverticesKd[index] = 0.0;
		fverticesKd[index + 1] = 0.0;
		fverticesKd[index + 2] = 0.0;
		fverticesKd[index + 3] = 0.0;
		
		index += 4;
	}	
	//printf("OBJET3D::CHARGER(): transformation vertices OK\n");	

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
	
	//Eclairage - Couleur diffuse
	// On utilise la même taille que pour la couleur ambiante (fverticesKa_size)
	vbo_Kd = 0;
	
	glGenBuffers (1, &vbo_Kd);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Kd);
	glBufferData (GL_ARRAY_BUFFER, fverticesKa_size * sizeof (float), fverticesKd, GL_STATIC_DRAW);			
	
	// Désallocations
	delete[] fverticesNormals;
	delete[] fvertices;
}


void Objet3D::construireVAO(GLuint vao, int offset) {	
	printf("OBJET3D::CONSTRUIREVAO()\n");
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
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ka);	
	glVertexAttribPointer (2, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	//Diffuse
	glEnableVertexAttribArray (3);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Kd);	
	glVertexAttribPointer (3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	//Specular
	glEnableVertexAttribArray (4);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_Ks);	
	glVertexAttribPointer (4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glEnableVertexAttribArray (0);
	glBindVertexArray(0); //termine le binding pour ce vertex array
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