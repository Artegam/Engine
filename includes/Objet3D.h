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

#ifndef BUFFER_OFFSET
  #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using namespace std;

class Objet3D {
	private:
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
		map<string, Material> * materials;
		int vbo_index;
		long nbTotalVertex;
		float* fvertices;
		int fvertices_size;
		int* objectIndices;
		int objectIndicesSize;
		
		void charger();
		
	public:
		~Objet3D();
	
		string getNom();
		long getNbFaces();
		GLuint* getVertexArrayBuffer();
		long getNbVertex();
		
		void setNom(string pNom);

		void ajouterVertex(double pX, double pY, double pZ, double pW);
		void ajouterVertexNormal(double pX, double pY, double pZ, double pW);		
		void ajouterFace(int nbParametres, char parametres[4][50], string nomMateriau);
		
		void initMaterial(map<string, Material> * mat);
		void dessiner();
		void construireVAO(GLuint vao, int offset);
		void afficher();
};

#endif
