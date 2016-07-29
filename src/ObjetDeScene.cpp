//$Author$
//$Date$
//$Version$
//$Rev$

#include <ObjetDeScene.h>

ObjetDeScene::ObjetDeScene(ShaderManager* sm) {
	className = (char*)"ObjetDeScene";
	m = new MessagesManager();
	s = sm;
	nbVertex = 0;
}

void ObjetDeScene::chargerFichier(string fichierSrc) {
	if(fichierSrc != "") {
		ObjParser* parser = new ObjParser();
		objets = parser->readFile(fichierSrc.c_str(), objets);

		//desalloc parser
		parser->~ObjParser();
	}
}

//ASCH - 14/01/2015 - Permet de récupérer les objets graphiques d'un objet (métier par exemple rail)
vector<Objet3D> ObjetDeScene::getObjets() {
	return objets;
}

vector<Transformation> ObjetDeScene::getTransformations() {
	return transformations;
}

void ObjetDeScene::addRotation(double pAngle, double pX, double pY, double pZ){
	Transformation * t = new Transformation('R', pAngle, pX, pY, pZ);
	transformations.insert(transformations.end(), *t);
	//transformations.insert(transformations.end(), std::pair<long,vector<Transformation> >(objets.size()-1, t)); //Ajoute les transformations
}

void ObjetDeScene::addAnimeRotation(double pAngle, double pX, double pY, double pZ, int pDuree){
	Animation * a = new Animation('R', pAngle, pX, pY, pZ, pDuree);
	animations.insert(animations.end(), *a);
}

void ObjetDeScene::addTranslation(double pX, double pY, double pZ){
	Transformation * t = new Transformation('T', pX, pY, pZ, 0.0);
	transformations.insert(transformations.end(), *t);
}

void ObjetDeScene::addAnimeTranslation(double pX, double pY, double pZ, int pDuree){
	Animation * a = new Animation('T', pX, pY, pZ, 0.0, pDuree);
	animations.insert(animations.end(), *a);	
}

void ObjetDeScene::clearTransformations(){
	transformations.clear();
}

void ObjetDeScene::printNbTranformations() {
	sprintf(mBuffer, "Nb transformations : %d", transformations.size());
	m->message(MM_INFO, className, mBuffer);
}

void ObjetDeScene::load() {
		//ASCH 24/09/2015 - Modification pour prendre en compte le multiobjet
	sprintf(mBuffer, "---- taille : %d", objets.size());
	m->message(MM_INFO, className, mBuffer);
	vao = new GLuint[objets.size()];

	//Création des tableaux en mémoire
	glGenVertexArrays (objets.size(), vao);
	
	// ASCH 20/04/2015 - Chargement des objets en mémoire graphique
	for(int i = 0; i < objets.size(); i++) {
		objets[i].construireVAO(vao[i], i);
		nbVertex += objets[i].getNbVertex();
	}	
	
	sprintf(mBuffer, "Nb d'objets : %d", objets.size());
	m->message(MM_INFO, className, mBuffer);	
	
}

void ObjetDeScene::draw() {

	// draw points 0-3 from the currently bound VAO with current in-use shader
	//for(int i = 0; i < objets.size(); i++) {
		glPushMatrix();
		glBindVertexArray(vao[0]);
	
	
	// ASCH - 29/07/2016 - Test de la fonction Executer de la classe Transformation	
		itTransf = transformations.begin();
		while(itTransf != transformations.end()) {
			itTransf->Executer();
			++itTransf;
		}		
	
		itAnime = animations.begin();
		while(itAnime != animations.end()) {
			itAnime->Executer();
			++itAnime;
		}		
		
		/*
		
		//pour exercice 2
		//Fixe une couleur
		if (i==1)
			glUniform4f(locColor, 0.3, 0.8, 0.3, 1.0);	
		if (i==2)
			glUniform4f(locColor, 0.3, 0.3, 0.8, 1.0);	
		if (i>2)
			glUniform4f(locColor, 0.3, 0.3, 0.3, 1.0);	
		//fin exercice 2
		*/		
		
		//Dessine un objet
		// glDrawArrays (GL_TRIANGLES, 0, objets[0].getNbVertex());

		//test
		
		//pour exercice 2 - Attention glLinkProgram doit être exécuté avant
		//locColor = glGetUniformLocation((GLuint)s->getShader_programme(), "vKa");
		/* pour l'instant
		if (locColor == -1)
			m->message(MM_ERR, className, "variable uniform vKa");
		*/
		
		calculateDiffuseColor();
		
		/*
		glUniform4f(locColor, 0.8, 0.3, 0.3, 1.0);	
		glDrawArrays (GL_TRIANGLES, 0, 12);
		glUniform4f(locColor, 0.3, 0.3, 0.8, 1.0);	
		glDrawArrays (GL_TRIANGLES, 12, objets[0].getNbVertex() - 12);
		*/
		// fin test
		glPopMatrix();
	//}	
	
}

void ObjetDeScene::calculateDiffuseColor() {
	
	//long vIndice = 0;
	//glDrawArrays (GL_TRIANGLES, vIndice, objets[0].getNbVertex());
	
		map<string, Material> mats = objets[0].getMaterialMap();
		map<string, Material>::iterator itMats;
		long nbVerticesCumule = 0;
		Material mat;
		for (itMats = mats.begin(); itMats != mats.end(); itMats++) {
			mat = itMats->second;
			//printf("( %f, %f)\n", nbVerticesCumule, mat.getNbVertices());
			//glUniform4f(locColor, mat.getDiffuseR(), mat.getDiffuseG(), mat.getDiffuseB(), 1.0);			
			
			// glUniform4f(locColor, 0.3, 0.3, 0.3, 1.0);			
			glDrawArrays (GL_TRIANGLES, nbVerticesCumule, mat.getNbVertices());
			nbVerticesCumule += mat.getNbVertices();
		}
	
}