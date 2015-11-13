#ifndef FACE_H
#define FACE_H

#include <GL/glee.h> //Bibliothèque opengl
#include <vector>

#include <string>
#include <Vertex.h>
#include <VertexNormal.h>

using namespace std;

class Face {
	private:
		vector<long> vertexNums;
		vector<long> vertexTextNums;
		vector<long> vertexNormalNums;
		string materialName;		

	public:
		void setMaterialName(string pMaterialName);

		string getMaterialName();

		void ajouterNumVertex(long numVertex);
		void ajouterNumVertexTexture(long numVertexTexture);
		void ajouterNumVertexNormal(long numVertexNormal);

		void dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal);
		void charger(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal, vector<Vertex> *pVerticesResult, int *nbVertex);
		void chargerNormales(vector<VertexNormal> pVerticesNormal, vector<VertexNormal> *pVerticesResult, int *nbVertex);
		
		void chargerIndicesDansTabMemoire(int* tabMemoire, int &pointeur);
};

#endif
