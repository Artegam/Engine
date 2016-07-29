// $Author$
// $Date$
// $Version$
// $Rev$

#include <Animation.h>

Animation::Animation(char pType, double pV1, double pV2, double pV3, double pV4, int vDuree) {
	
	type = pType;
	lV1 = 0.0;
	lV2 = 0.0;
	lV3 = 0.0;
	lV4 = 0.0;
	v1 = pV1;
	v2 = pV2;
	v3 = pV3;
	v4 = pV4;
	
	duree = vDuree;
}

void Animation::Executer() { 

	if(duree != 0) {
		lV1 += v1;
		lV2 += v2;
		lV3 += v3;
		lV4 += v4;

		t = new Transformation(type, lV1, lV2, lV3, lV4);
		t->Executer();
		if (duree > 0)
			duree--;
	}
}


