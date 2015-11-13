
#include <TestMaterial.h>


TestMaterial::TestMaterial(string pNom) {
	nbSuccess = 0;
	nbFails = 0;
	nom = pNom;
}

void TestMaterial::executer() {
	checkNom();
	checkAmbient();
	checkDiffuse();
	checkSpecular();
	checkSpecularExponent();
	checkDissolve();
	checkIlluminationModel();
	checkMapKd();
}

void TestMaterial::checkNom() {
	Material * t = new Material("pierre");
	message("Test du nom avec le constructeur...");
	(t->getNom() == "pierre")?success():fail();
	
	message("Test du nom avec setNom...");
	t->setNom("eau");
	(t->getNom() == "eau")?success():fail();
}

void TestMaterial::checkAmbient() {
	float	amb[3];
	Material * t = new Material("metal");
	
	message("Test de la propriete ambiant...");
	t->setAmbient(1.0, 2.0, 3.0);
	amb[0] = t->getAmbientR();
	amb[1] = t->getAmbientG();
	amb[2] = t->getAmbientB();
	(amb[0] == 1.0 && amb[1] == 2.0 && amb[2] == 3.0)?success():fail();
}

void TestMaterial::checkDiffuse() {
	float dif[3];
	Material * t = new Material("metal");
	
	message("Test de la propriete diffuse...");
	t->setDiffuse(3.0, 2.0, 1.0);
	dif[0] = t->getDiffuseR();
	dif[1] = t->getDiffuseG();
	dif[2] = t->getDiffuseB();
	(dif[0] == 3.0 && dif[1] == 2.0 && dif[2] == 1.0)?success():fail();
}

void TestMaterial::checkSpecular() {
	float spec[3];
	Material * t = new Material("metal");
	
	message("Test de la propriete specular...");
	t->setSpecular(4.0, 5.0, 6.0);
	spec[0] = t->getSpecularR();
	spec[1] = t->getSpecularG();
	spec[2] = t->getSpecularB();
	(spec[0] == 4.0 && spec[1] == 5.0 && spec[2] == 6.0)?success():fail();
}

void TestMaterial::checkSpecularExponent() {
	Material * t = new Material("metal");
	
	message("Test de la propriete specular exponent...");
	t->setSpecularExponent(0.725413);
	isEqual(t->getSpecularExponent(), 0.725413)?success():fail();
}

void TestMaterial::checkDissolve() {
	Material * t = new Material("metal");
	
	message("Test de la propriete dissolve...");
	t->setDissolve(0.345678);
	isEqual(t->getDissolve(), 0.345678)?success():fail();
}

void TestMaterial::checkIndiceOfRefraction() {
	Material * t = new Material("metal");
	
	message("Test de la propriete indice of refraction...");
	t->setIndiceOfRefraction(0.853686);
	isEqual(t->getIndiceOfRefraction(), 0.853686)?success():fail();
}

void TestMaterial::checkIlluminationModel() {
	Material * t = new Material("metal");
	
	message("Test de la propriete illumination model...");
	t->setIlluminationModel(3);
	t->getIlluminationModel() == 3?success():fail();
}

void TestMaterial::checkMapKd() {
	Material * t = new Material("metal");
	
	message("Test de la propriete texture map_Kd...");
	t->setMapKd("c:\temp\toto.txt");
	t->getMapKd() == "c:\temp\toto.txt"?success():fail();
}
