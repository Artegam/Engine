
#include <UnitTestLoader.h>

//ASCH - 07/03/2015 - Ensemble de definitions de tests
#include <TestObjParser.h>
#include <TestMtlParser.h>
#include <TestMaterial.h>


void UnitTestLoader::executer() {
	root.executer();
	titre("Recapitulatif des tests");
	root.resultat();
}

void UnitTestLoader::charger() {
		UnitTest * test = new TestMaterial("Test de Material");
		root.addTest(test);
		
		test = new TestMtlParser("Test de MtlParser");
		root.addTest(test);
		
		test = new TestObjParser("Test de ObjParser");
		root.addTest(test);		
}
