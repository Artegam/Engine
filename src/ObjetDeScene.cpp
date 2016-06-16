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
	rAngle = 0;
	rX = 0;
	rY = 0;
	rZ = 0;
	tX = 0;
	tY = 0;
	tZ = 0;
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

void ObjetDeScene::addTranslation(double pX, double pY, double pZ){
	Transformation * t = new Transformation('T', pX, pY, pZ, 0.0);
	transformations.insert(transformations.end(), *t);
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
	
	calculateTransformations();
	
	sprintf(mBuffer, "Nb d'objets : %d", objets.size());
	m->message(MM_INFO, className, mBuffer);	
	
}

void ObjetDeScene::draw() {

	// draw points 0-3 from the currently bound VAO with current in-use shader
	//for(int i = 0; i < objets.size(); i++) {
		glPushMatrix();
		glBindVertexArray(vao[0]);
	
		
		if (rAngle != 0)
			glRotatef(rAngle, rX, rY, rZ);
		
		glTranslatef(tX, tY, tZ);
		
		
		
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

void ObjetDeScene::calculateTransformations() {
		itTransf = transformations.begin();
		while(itTransf != transformations.end()) {
			//ASCH - 19/01/2016 - Applique les transformations sur les objets
			double * valeurs = itTransf->getValues();
			switch(itTransf->getType()) {
				case 'R':
					rAngle += valeurs[0];
					rX += valeurs[1];
					rY += valeurs[2];
					rZ += valeurs[3];
					break;
					
				case 'T':
					tX += valeurs[0];
					tY += valeurs[1];
					tZ += valeurs[2];
					break;
			}
			++itTransf;
		}	

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