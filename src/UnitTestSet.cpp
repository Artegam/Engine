
#include <UnitTestSet.h>


void UnitTestSet::executer() {
	
	//ASCH - 07/03/2015 - execution du groupe de tests unitaires
	for (vector<UnitTest *>::iterator it = testGroup.begin(); it != testGroup.end(); ++it) {
		(*it)->executer();
		(*it)->resultat();
		nbSuccess += (*it)->getNbSuccess();
		nbFails += (*it)->getNbFails();
	}
	
}

void UnitTestSet::resultat(){
	
	for (vector<UnitTest *>::iterator it = testGroup.begin(); it != testGroup.end(); ++it) {
		message((*it)->getNom());
		printf("\t %d (%3.1f%%)\n", (*it)->getNbSuccess(), ((double)(*it)->getNbSuccess() / ((*it)->getNbSuccess() + (*it)->getNbFails())) * 100.0);
	}
	titre("Recapitulatif des tests");
	UnitTest::resultat();
	
}

void UnitTestSet::addTest(UnitTest * test) {
	testGroup.push_back(test);
}
