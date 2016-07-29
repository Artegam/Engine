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

void Transformation::Executer() {
		
	double rAngle = 0.0;
	double rX = 0.0;
	double rY = 0.0;
	double rZ = 0.0;
	double tX = 0.0;
	double tY = 0.0;
	double tZ = 0.0;

		switch(type) {
			case 'R':
				rAngle += values[0];
				rX += values[1];
				rY += values[2];
				rZ += values[3];
				break;
				
			case 'T':
				tX += values[0];
				tY += values[1];
				tZ += values[2];
				break;
		}	
		
	if (rAngle != 0.0)
		glRotatef(rAngle, rX, rY, rZ);
	
	glTranslatef(tX, tY, tZ);			
	
}