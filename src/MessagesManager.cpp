#include <MessagesManager.h>


MessagesManager::MessagesManager() {
	verbose = true;
}

void MessagesManager::message(const char * typeMess, const char* className, const char * mess) {
	//ASCH 26/05/2016 - Affiche obligatoirement les messages d'erreurs
	if (typeMess == "ERREUR") {
		printf("%s (%s) %s\n", typeMess, className, mess);
		return;
	}
	
	if (verbose) 
		printf("%s (%s) %s\n", typeMess, className, mess);
}

void MessagesManager::setVerbose(bool v) {
	verbose = v;
}