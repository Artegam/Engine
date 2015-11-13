
#include <TestObjet3D.h>

#include <Objet3D.h>
#include <Material.h>

#include "stdio.h"

#include <map>


TestObjet3D::TestObjet3D(string pNom) {
	nbSuccess = 0;
	nbFails = 0;
	nom = pNom;
}


void TestObjet3D::executer() {
	Objet3D * obj = new Objet3D();
	
	//Pas d'accès aux vertex donc test impossible
	//titre("Test du materiau");
	//obj->ajouterVertex(1.0, 2.0, 3.0, 0.5, "materiau de test");
	
	//.compare("Material.014") == 0
	
}