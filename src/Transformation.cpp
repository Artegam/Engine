//$Author$
//$Date$
//$Version$
//$Rev$

#include <Transformation.h>


char Transformation::getType(){
	return type;
}

double* Transformation::getValues(){
	return values;
}

Transformation::Transformation(char pType, double pV1, double pV2, double pV3, double pV4){
	type = pType;
	values[0] = pV1;
	values[1] = pV2;
	values[2] = pV3;
	values[3] = pV4;
}