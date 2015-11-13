
#include <TestMtlParser.h>

#include <MtlParser.h>
#include <Material.h>

#include "stdio.h"

#include <map>


TestMtlParser::TestMtlParser(string pNom) {
	nbSuccess = 0;
	nbFails = 0;
	nom = pNom;
}


void TestMtlParser::executer() {

	MtlParser * parser = new MtlParser();
	map<string, Material> materials;
	
	materials = parser->readMaterials(".\\mtl\\jaguard.mtl");
	
	titre("Test de lecture du fichier");
	test("Chargement du fichier de test des materiaux...", materials.size() > 0);
	test("Test du nombre de materiaux retournes", materials.size() == 16);

	titre("Test des materiaux");
	test("Material", materials["Material"].getNom().compare("Material") == 0);
	test("Material.001", materials["Material.001"].getNom().compare("Material.001") == 0);
	test("Material.002", materials["Material.002"].getNom().compare("Material.002") == 0);
	test("Material.003", materials["Material.003"].getNom().compare("Material.003") == 0);
	test("Material.004", materials["Material.004"].getNom().compare("Material.004") == 0);
	test("Material.005", materials["Material.005"].getNom().compare("Material.005") == 0);
	test("Material.006", materials["Material.006"].getNom().compare("Material.006") == 0);
	test("Material.007", materials["Material.007"].getNom().compare("Material.007") == 0);
	test("Material.008", materials["Material.008"].getNom().compare("Material.008") == 0);
	test("Material.009", materials["Material.009"].getNom().compare("Material.009") == 0);
	test("Material.010", materials["Material.010"].getNom().compare("Material.010") == 0);
	test("Material.011", materials["Material.011"].getNom().compare("Material.011") == 0);
	test("Material.012", materials["Material.012"].getNom().compare("Material.012") == 0);
	test("Material.013", materials["Material.013"].getNom().compare("Material.013") == 0);
	test("Material.014", materials["Material.014"].getNom().compare("Material.014") == 0);
	test("None", materials["None"].getNom().compare("None") == 0);
	
	
	
	titre("Test des couleurs ambiantes");
	float amb[3];
	
	amb[0] = materials["Material"].getAmbientR();
	amb[1] = materials["Material"].getAmbientG();
	amb[2] = materials["Material"].getAmbientB();
	test(materials["Material"].getNom(), isEqual(amb[0], 0.0) && isEqual(amb[1], 0.0) && isEqual(amb[2], 0.0));
	amb[0] = materials["Material.001"].getAmbientR();
	amb[1] = materials["Material.001"].getAmbientG();
	amb[2] = materials["Material.001"].getAmbientB();
	test(materials["Material.001"].getNom(), isEqual(amb[0], 0.0) && isEqual(amb[1], 0.0) && isEqual(amb[2], 0.0));
	amb[0] = materials["Material.002"].getAmbientR();
	amb[1] = materials["Material.002"].getAmbientG();
	amb[2] = materials["Material.002"].getAmbientB();
	test(materials["Material.002"].getNom(), isEqual(amb[0], 0.0) && isEqual(amb[1], 0.0) && isEqual(amb[2], 0.0));
	amb[0] = materials["Material.003"].getAmbientR();
	amb[1] = materials["Material.003"].getAmbientG();
	amb[2] = materials["Material.003"].getAmbientB();
	test(materials["Material.003"].getNom(), isEqual(amb[0], 0.0) && isEqual(amb[1], 0.0) && isEqual(amb[2], 0.0));

	
	
	titre("Test des couleurs diffuses");
	float dif[3];
	
	dif[0] = materials["Material"].getDiffuseR();
	dif[1] = materials["Material"].getDiffuseG();
	dif[2] = materials["Material"].getDiffuseB();	
	test(materials["Material"].getNom(), isEqual(dif[0], 0.569629) && isEqual(dif[1], 0.575564) && isEqual(dif[2], 0.578806));
	dif[0] = materials["Material.001"].getDiffuseR();
	dif[1] = materials["Material.001"].getDiffuseG();
	dif[2] = materials["Material.001"].getDiffuseB();
	test(materials["Material.001"].getNom(), isEqual(dif[0], 0.493364) && isEqual(dif[1], 0.506375) && isEqual(dif[2], 0.519799));
	dif[0] = materials["Material.002"].getDiffuseR();
	dif[1] = materials["Material.002"].getDiffuseG();
	dif[2] = materials["Material.002"].getDiffuseB();
	test(materials["Material.002"].getNom(), isEqual(dif[0], 0.712616) && isEqual(dif[1], 0.699611) && isEqual(dif[2], 0.714142));
	dif[0] = materials["Material.003"].getDiffuseR();
	dif[1] = materials["Material.003"].getDiffuseG();
	dif[2] = materials["Material.003"].getDiffuseB();
	test(materials["Material.003"].getNom(), isEqual(dif[0], 0.400182) && isEqual(dif[1], 0.375929) && isEqual(dif[2], 0.351675));


	
	titre("Test des couleurs speculaires");
	float spec[3];
	
	spec[0] = materials["Material"].getSpecularR();
	spec[1] = materials["Material"].getSpecularG();
	spec[2] = materials["Material"].getSpecularB();
	test(materials["Material"].getNom(), isEqual(spec[0], 0.0) && isEqual(spec[1], 0.0) && isEqual(spec[2], 0.0));
	spec[0] = materials["Material.001"].getSpecularR();
	spec[1] = materials["Material.001"].getSpecularG();
	spec[2] = materials["Material.001"].getSpecularB();
	test(materials["Material.001"].getNom(), isEqual(spec[0], 0.649115) && isEqual(spec[1], 0.649115) && isEqual(spec[2], 0.649115));
	spec[0] = materials["Material.002"].getSpecularR();
	spec[1] = materials["Material.002"].getSpecularG();
	spec[2] = materials["Material.002"].getSpecularB();
	test(materials["Material.002"].getNom(), isEqual(spec[0], 0.0) && isEqual(spec[1], 0.0) && isEqual(spec[2], 0.0));
	spec[0] = materials["Material.003"].getSpecularR();
	spec[1] = materials["Material.003"].getSpecularG();
	spec[2] = materials["Material.003"].getSpecularB();
	test(materials["Material.003"].getNom(), isEqual(spec[0], 0.0) && isEqual(spec[1], 0.0) && isEqual(spec[2], 0.0));

	
	
	titre("Test des exponentielles speculaires");
	float exp;
	
	exp = materials["Material"].getSpecularExponent();
	test(materials["Material"].getNom(), isEqual(exp, 0.0));
	exp = materials["Material.001"].getSpecularExponent();
	test(materials["Material.001"].getNom(), isEqual(exp, 243.137255));
	exp = materials["Material.012"].getSpecularExponent();
	test(materials["Material.012"].getNom(), isEqual(exp, 96.078431));

	
	
	titre("Test des indices de refraction");
	float ni;
	
	ni = materials["Material"].getIndiceOfRefraction();
	test(materials["Material"].getNom(), isEqual(ni, 1.0));
	ni = materials["Material.013"].getIndiceOfRefraction();
	test(materials["Material.013"].getNom(), isEqual(ni, 1.0));
	ni = materials["None"].getIndiceOfRefraction();
	test(materials["None"].getNom(), isEqual(ni, 0.0));
	
	
	
	titre("Test des modeles d'illumination");
	int illum;
	
	illum = materials["Material"].getIlluminationModel();
	test(materials["Material"].getNom(), isEqual(illum, 1));
	illum = materials["Material.001"].getIlluminationModel();
	test(materials["Material.001"].getNom(), isEqual(illum, 2));
	illum = materials["Material.002"].getIlluminationModel();
	test(materials["Material.002"].getNom(), isEqual(illum, 1));

	
	
	titre("Test des textures map_Kd");
	string map;
	
	map = materials["Material"].getMapKd();
	test(materials["Material"].getNom(), map == "/media/tonio/DATA_Tiroir/BlenderCave/sepecatjaguard/textures/retsete.jpg");
	map = materials["Material.001"].getMapKd();
	test(materials["Material.001"].getNom(), map == "");
	map = materials["Material.002"].getMapKd();
	test(materials["Material.002"].getNom(), map == "/media/tonio/DATA_Tiroir/BlenderCave/sepecatjaguard/textures/retsete.jpg");
	map = materials["Material.003"].getMapKd();
	test(materials["Material.003"].getNom(), map == "/media/tonio/DATA_Tiroir/BlenderCave/sepecatjaguard/textures/trainavant.jpg");
	
}

