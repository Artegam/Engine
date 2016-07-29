

// Qu'est ce qu'une animation ?

// c'est une transformation qui possède une durée.
// J'utilise cette classe comme container

#ifndef ANIMATION
#define ANIMATION

#include "Transformation.h"

#include <MessagesManager.h>

class Animation {
	public:
		Animation(char pType, double pV1, double pV2, double pV3, double pV4, int vDuree);
		void Executer();
	
	private:
		char type;
		double lV1;
		double lV2;
		double lV3;
		double lV4;
		double v1;
		double v2;
		double v3;
		double v4;
		int duree;
		Transformation * t;
};

#endif
