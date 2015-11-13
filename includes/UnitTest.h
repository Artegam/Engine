#ifndef UNITTEST_H
#define UNITTEST_H

//ASCH - 02/03/2015 - Création de la classe de test unitaire

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

class UnitTest {

	protected:
		int nbSuccess;
		int nbFails;
		string nom;
		
	public:
		UnitTest();
		UnitTest(string pNom);
		void fail();
		void success();
		int getNbSuccess();
		int getNbFails();
		string getNom();
		string toString();
		void message(string msg);
		void titre(string ttr);
		void resultat();
		virtual void executer();
		void test(string msg, bool condition);
		bool isEqual(float x, float y);
		bool isEqual(int x, int y);

};

#endif