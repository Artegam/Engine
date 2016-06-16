#ifndef OBJET3D
#define OBJET3D

#include <GL/glee.h>

#include <vector>
#include <algorithm>    // std::for_each
#include <stdio.h>
#include <map>

#include <Vertex.h>
#include <VertexNormal.h>
#include <Face.h>
#include <material.h>
#include <MessagesManager.h>

#ifndef BUFFER_OFFSET
  #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using namespace std;

class Objet3D {		
	public:
		Objet3D();
		~Objet3D();
	
		string getNom();
		long getNbFaces();
		GLuint* getVertexArrayBuffer();
		long getNbVertex();
		long getNbMaterials();
		vector<Face> getFaces();
		Material getMaterial(const char* materialName);
		map<string, Material> getMaterialMap();
		
		void setNom(string pNom);
		void setPosition(double pX, double pY, double pZ);

		void ajouterVertex(double pX, double pY, double pZ, double pW);
		void ajouterVertexNormal(double pX, double pY, double pZ, double pW);		
		void ajouterFace(int nbParametres, char parametres[4][50], char* nomMateriau);
		
		void initMaterial(map<string, Material> * mat);
		void ajouterMaterial(Material mat);
		
		void dessiner();
		void construireVAO(GLuint vao, int offset);
		void afficher();		

	private:				
		MessagesManager* m;
		char mBuffer[150];
		char* className;
		string nom;
		vector<Vertex> vertices;
		vector<VertexNormal> verticesNormal;
		vector<Face> faces;
		GLuint uid;
		GLuint vbo;		 // object		
		GLuint vbo_v;  // vertices
		GLuint vbo_vn; // vertices normals
		GLuint vbo_Ka; // colors Ambiant
		GLuint vbo_Kd; // colors Diffuse
		GLuint vbo_Ks; // colors Specular
		vector<Vertex> verticesBuffer;
		vector<VertexNormal> verticesNormalBuffer;
		map<string, Material> materials;
		char* currentMaterialName;
		int vbo_index;
		long nbTotalVertex;
		float* fvertices;
		int fvertices_size;
		int fverticesKa_size;
		int fverticesKd_size;
		int* objectIndices;
		int objectIndicesSize;
		double posX;
		double posY;
		double posZ;
		
		void charger();
		void position();
		
};

#endif
