#ifndef TRANSFORMATION
#define TRANSFORMATION

#include <ShaderManager.h>

class Transformation {
	
	public:
		Transformation(char pType, double pV1, double pV2, double pV3, double pV4);
		char getType();
		double* getValues();
		void Executer();
		
	private:	
		char type; // R ou T
		double values[4];
			/*pour R : angle, x, y, z
				pour T : x, y, z, 0 */
				
};

#endif