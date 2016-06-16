//$Author$
//$Date$
//$Version$
//$Rev$
#include <KeyboardManager.h>

KeyboardManager::KeyboardManager() {
		className = (char*)"KeyboardManager";
		
		tX = 0.0;
		tY = 0.0;
		tZ = 0.0;
		
		tXCumule = 0.0;
		tYCumule = -5.0;
		tZCumule = 0.0;
		
		angle = 1.0;
		angleCumule = 0.0;
		
		azimut = 1.0;
		azimutCumule = 0.0;
}		

KeyboardManager::KeyboardManager(ShaderManager s) {
		KeyboardManager();
		sm = s;
}

void KeyboardManager::executer(unsigned char c, int x, int y) {

	// ASCH - 29/09/2014 - La touche 27 est la touche echap
	if (c == 27) {
		//Desallocation
		//desallocation();
		mm.message(MM_INFO, className, "Sortie du programme");
		sm.cleanShaders();		
		mm.message(MM_INFO, className, "fin");
		glutLeaveMainLoop();
		glutDestroyWindow(windowID);
		exit(0);
	}		

	if (c == 'l') {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		displayWireMode = !displayWireMode;
	}
	
	if (c == 'p') {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		displayWireMode = !displayWireMode;
	}
	
	if (c == 'f') {		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		displayWireMode = !displayWireMode;
	} 		
	
	if (c == 'r')
		rotateScene = !rotateScene;


	//Déplacement standart dans la scene.
	if (c == 'q') {
		angleCumule -= angle;
		if (angleCumule < 0) angleCumule += 360;
		angleCumule = fmod(angleCumule, 360.0);
	}
	
	if (c == 'd') {
		angleCumule += angle;
		angleCumule = fmod(angleCumule, 360.0);
	}
		
	if (c == 's') {
		tX = sin(angleCumule*PI/180);
		tZ = -cos(angleCumule*PI/180);
		tXCumule += tX;
		tZCumule += tZ;
	}
		
	if (c == 'z') {
		tX = -sin(angleCumule*PI/180);
		tZ = cos(angleCumule*PI/180);	
		tXCumule += tX;
		tZCumule += tZ;
	}
	
	//Palonnnier
	if (c == 'a') {
		tX = sin((angleCumule+90%360)*PI/180);
		tZ = -cos((angleCumule+90%360)*PI/180);	
		tXCumule += tX;
		tZCumule += tZ;		
	}
	
	if (c == 'e') {	
		tX = -sin((angleCumule+90%360)*PI/180);
		tZ = cos((angleCumule+90%360)*PI/180);	
		tXCumule += tX;
		tZCumule += tZ;		
	}
	
	//Elevation
	if (c == 'w') {
		tY = 1.0;
		tYCumule += tY;
		//glTranslatef(0.0, tY, 0.0);
	}
		
	if (c == 'x') {
		tY = -1.0;
		tYCumule += tY;
		//glTranslatef(0.0, tY, 0.0);
	}
	
	//Azimut
	if (c == 'c')
		azimutCumule += azimut;		
	
	if (c == 'v')
		azimutCumule -= azimut;
	
	applyMoves();
}

void KeyboardManager::setShaderManager(ShaderManager s) {
	sm = s;
}

void KeyboardManager::applyMoves() {
	glLoadIdentity();
	glRotatef(azimutCumule, 1.0, 0.0, 0.0);
	glRotatef(angleCumule, 0.0, 1.0, 0.0);
	glTranslatef(tXCumule, tYCumule, tZCumule);	
}