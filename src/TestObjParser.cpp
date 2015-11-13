
#include <TestObjParser.h>

#include <ObjParser.h>
#include <Material.h>

#include "stdio.h"

#include <map>


TestObjParser::TestObjParser(string pNom) {
	nbSuccess = 0;
	nbFails = 0;
	nom = pNom;
}


void TestObjParser::executer() {
	ObjParser * parser = new ObjParser();
	vector<Objet3D> objets;
	objets = parser->readFile(".\\obj\\test.obj", objets);
	
	//ecrire les tests
	titre("Test lecture du fichier");
	test("Nb d'objets > 0", objets.size() > 0);
	
	parser->~ObjParser();
	
}