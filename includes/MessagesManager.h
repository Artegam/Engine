#ifndef MESSAGE
#define MESSAGE

#include <stdio.h>

using namespace std;

#define MM_INFO "INFO"
#define MM_ERR "ERREUR"


class MessagesManager {
	
	public:
		MessagesManager();
		void message(const char * typeMess, const char* className, const char * mess);
		void setVerbose(bool v);
		
	private:
		bool verbose;
		
};

#endif