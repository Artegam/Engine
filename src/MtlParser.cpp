#include <MtlParser.h>


map<string, Material> MtlParser::readMaterials(const char* filename){
	FILE* fichier;
	
	float r;
	float g;
	float b;
	float fValue;
	int iValue;
	char ligne[255];
	int selection = 0;
	string currMat;

	//TODO - ASCH - Bug ou problème de linkage de bibliothèque (SDL ?)
	//materials = new map<string, Material>;
	vMat = new Material("S");
	
	fichier = fopen(filename, "r");

	while(!feof(fichier)) {	
		fscanf(fichier, "%s", ligne);
		selection = 0;
		r=0.0;
		g=0.0;
		b=0.0;

		if (strcmp((const char*)ligne, (char*)"newmtl") == 0) selection = 1;
		if (strcmp((const char*)ligne, (char*)"Ka") == 0) selection = 2;
		if (strcmp((const char*)ligne, (char*)"Kd") == 0) selection = 3;
		if (strcmp((const char*)ligne, (char*)"Ks") == 0) selection = 4;
		if (strcmp((const char*)ligne, (char*)"Ns") == 0) selection = 5;
		if (strcmp((const char*)ligne, (char*)"Ni") == 0) selection = 6;
		if (strcmp((const char*)ligne, (char*)"d") == 0) selection = 7;
		if (strcmp((const char*)ligne, (char*)"illum") == 0) selection = 8;
		if (strcmp((const char*)ligne, (char*)"map_Kd") == 0) selection = 9;
		if (strcmp((const char*)ligne, (char*)"Tf") == 0) selection = 10;
				
		switch(selection) {
			//ASCH - 06/03/2014 - Le cas du newmtl
			case 1: 
				fscanf(fichier, "%s", ligne);
				vMat = new Material(ligne);
				currMat = ligne;
				materials.insert(std::pair<string,Material>(ligne, *vMat));
				//printf("\tmat: %s \t %s\n", ligne, materials.at(0).getNom().c_str());				
				break;
				
			//Ka
			case 2:
				fscanf(fichier, "%f %f %f", &r, &g, &b);
				materials[currMat].setAmbient(r, g, b);
				break;
			
			//Kd
			case 3: 
				fscanf(fichier, "%f %f %f", &r, &g, &b);
				materials[currMat].setDiffuse(r, g, b);
				break;

			//Ks
			case 4: 
				fscanf(fichier, "%f %f %f", &r, &g, &b);
				materials[currMat].setSpecular(r, g, b);			
				break;

			//Ns - Specular exponent - Ns exp
			case 5:
				fscanf(fichier, "%f", &fValue);
				materials[currMat].setSpecularExponent(fValue);						
				break;

			//Ni - Optical density / Indice of refraction
			case 6:
				fscanf(fichier, "%f", &fValue);
				materials[currMat].setIndiceOfRefraction(fValue);						
				break;
				
			//d - d factor
			case 7:
				fscanf(fichier, "%f", &fValue);
				materials[currMat].setDissolve(fValue);									
				break;
				
			//illum
			case 8:
				fscanf(fichier, "%d", &iValue);
				materials[currMat].setIlluminationModel(iValue);									
				break;
				
			//map_Kd - Material texture map - map_Ka, map_Kd, etc...
			case 9:
				fscanf(fichier, "%s", &ligne);
				materials[currMat].setMapKd(ligne);									
				break;
				
			//Tf - Transmission filter Tf r g b
			case 10:
				break;
		}
	}	
	return materials;
}