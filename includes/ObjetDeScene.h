#ifndef OBJETDESCENE
#define OBJETDESCENE

#include <GL/glee.h>
#include <vector>

#include <ObjParser.h>
#include <Objet3D.h>
#include <Transformation.h>
#include <MessagesManager.h>
#include <ShaderManager.h>
#include <Material.h>
#include <Animation.h>

using namespace std;


class ObjetDeScene {
	
	public:
		ObjetDeScene(ShaderManager* sm);
		vector<Objet3D> getObjets();
		vector<Transformation> getTransformations();
		void addRotation(double pAngle, double pX, double pY, double pZ);
		void addAnimeRotation(double pAngle, double pX, double pY, double pZ, int pDuree);
		void addTranslation(double pX, double pY, double pZ);
		void addAnimeTranslation(double pX, double pY, double pZ, int pDuree);
		void clearTransformations();
		void chargerFichier(string fichierSrc);
		void printNbTranformations();
		void load();
		virtual void draw();
		
	protected:	
		vector<Objet3D> objets;
		vector<Transformation> transformations;
		vector<Animation> animations;
		//map<long, vector<Transformation> > transformations;
		
	private:
		ShaderManager* s;
		MessagesManager* m;
		char* className;
		char mBuffer[150];
		GLuint* vao;
		long nbVertex;
		//map<long, vector<Transformation> >::iterator itTransf;
		vector<Transformation>::iterator itTransf;
		vector<Animation>::iterator itAnime;
		GLint locColor;
		
		void calculateDiffuseColor();
};

#endif