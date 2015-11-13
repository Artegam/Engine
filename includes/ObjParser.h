
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Objet3D.h"


class ObjParser {
	private:
		vector<Objet3D> objets;
		Objet3D * vObj;
		long cptFaces;
		long cptObjects;
		string nomMat;
	
		void insertObject();

	public:
	
		//ObjParser();
		//~ObjParser();
		vector<Objet3D> readFile (const char * filename, vector<Objet3D> pObjets);
		void readVertex(FILE* fichier);
		void readVertexNormal(FILE* fichier);
		void readObject(FILE* fichier);
		void readFace(FILE* fichier);
		void readMaterial(FILE* fichier);
};
