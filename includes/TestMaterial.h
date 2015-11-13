#ifndef TESTMATERIAL_H
#define TESTMATERIAL_H

#include "UnitTest.h"
#include "Material.h"

class TestMaterial : public UnitTest {

	public:
		TestMaterial(string pNom);
		void executer();
		void checkNom();
		void checkAmbient();
		void checkDiffuse();
		void checkSpecular();
		void checkSpecularExponent();
		void checkDissolve();
		void checkIndiceOfRefraction();
		void checkIlluminationModel();
		void checkMapKd();

};

#endif