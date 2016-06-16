#ifndef OBJPARSER
#define OBJPARSER

#include <stdio.h>
#include <string.h>
#include <vector>
#include "Objet3D.h"
#include <MessagesManager.h>
#include <Material.h>

class ObjParser {

	public:	
		//ObjParser();
		//~ObjParser();
		vector<Objet3D> readFile (const char * filename, vector<Objet3D> pObjets);
		ObjParser();
		
	private:
		vector<Objet3D> objets;
		Objet3D * vObj;
		long cptFaces;
		long cptObjects;
		char nomMaterialCourrant[50];
		char * className;
		MessagesManager* m;
		char nomMtlLib[50];
		char mBuffer[150];
		Material* mat;
	
		void readVertex(FILE* fichier);
		void readVertexNormal(FILE* fichier);
		void readObject(FILE* fichier);
		void readFace(FILE* fichier);
		void readMaterial(FILE* fichier);	
		void readMaterialUsed(FILE* fichier);	
		void readMaterialLibrary(FILE* fichier);
		void insertObject();		
		void readMtlFile(const char* filename);
		
		void readNewMaterial(FILE* fichier);
		void readSpecularExponent(FILE* fichier);
		void readAmbient(FILE* fichier);
		void readDiffuse(FILE* fichier);
		void readSpecular(FILE* fichier);
		
};

#endif