#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

using namespace std;

class Material {
	private:
		string nom;
		float ambiant_r, ambiant_g, ambiant_b;
		float diffuse_r, diffuse_g, diffuse_b;
		float specular_r, specular_g, specular_b;
		float Ns, Ni, d;
		int illum;
		string mapKd;

	public:
		Material();
		Material(string pNom);
		
		string getNom();
		
		float getAmbientR();
		float getAmbientG();
		float getAmbientB();
		float getDiffuseR();
		float getDiffuseG();
		float getDiffuseB();
		float getSpecularR();
		float getSpecularG();
		float getSpecularB();
		float getSpecularExponent();
		float getDissolve();
		float getIndiceOfRefraction();
		int getIlluminationModel();
		string getMapKd();
		
		void setNom(string pNom);
		void setAmbient(float pR, float pG, float pB);
		void setSpecular(float pR, float pG, float pB);
		void setDiffuse(float pR, float pG, float pB);
		void setSpecularExponent(float pNs);
		void setDissolve(float pFactor);
		void setIndiceOfRefraction(float pNi);
		void setIlluminationModel(int pIllum);
		void setMapKd(string pFullFilename);
};

#endif