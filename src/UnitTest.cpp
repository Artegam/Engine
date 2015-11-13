
#include <UnitTest.h>

//ASCH - 02/03/2015 - Implémentation de la classe de test unitaire
#include "stdio.h"


UnitTest::UnitTest() {
	nbSuccess = 0;
	nbFails = 0;
	nom = "Tout les tests";
}

UnitTest::UnitTest(string pNom) {
	nbSuccess = 0;
	nbFails = 0;
	nom = pNom;
}

void UnitTest::fail() {
	printf("\t ECHEC\n");
	nbFails++;
};

void UnitTest::success() {
	printf("\t SUCCES\n");
	nbSuccess++;
};

int UnitTest::getNbSuccess() {
	return nbSuccess;
}

int UnitTest::getNbFails() {
	return nbFails;
}

string UnitTest::getNom() {
	return nom;
}

string UnitTest::toString() {
	string retstr = "";
	char strtmp[250];
	
	retstr = "---------------------------------------------------------------\n";
	retstr += " Nom : " + nom + "\n";
	if (nbSuccess + nbFails > 0) {
		sprintf(strtmp, " Nb Succes : %3.1f%% (%d) \t Nb Echecs : %3.1f%% (%d)\n", ((double)nbSuccess / (nbSuccess + nbFails)) * 100.0, nbSuccess, ((double)nbFails / (nbSuccess + nbFails)) * 100.0, nbFails);
		retstr += strtmp;
	}
	else
		retstr += "Aucun test programme.\n";
	
	retstr += "---------------------------------------------------------------\n";
	return retstr;
}

void UnitTest::message(string msg) {
	string * spaces;
	if (msg.size() > 50)
		msg.resize(50);	
	else
		spaces = new string(50 - msg.size(), '.');
		
	printf("%s", msg.c_str());
	printf("%s", spaces->c_str());
}

void UnitTest::titre(string ttr){
	printf("\n%s\n", ttr.c_str());
	printf("%s\n", string(ttr.size(), '-').c_str());
}

void UnitTest::resultat() {
	printf("%s\n", toString().c_str());
}

void UnitTest::executer(){
}

void UnitTest::test(string msg, bool condition) {
	message(msg);
	condition?success():fail();
}

bool UnitTest::isEqual(float x, float y) {
	return fabs(x - y) < 0.000001;
}

bool UnitTest::isEqual(int x, int y) {
	return (x - y) == 0;
}
