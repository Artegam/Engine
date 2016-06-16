#ifndef KEYBOARDMANAGER
#define KEYBOARDMANAGER

#include <GL/glee.h>
#include <GL/freeglut.h>

#include <math.h>
#include <stdio.h>

#include <ShaderManager.h>
#include <MessagesManager.h>

using namespace std;


#define PI 3.14159265

class KeyboardManager {
	
	public:
		KeyboardManager();
		KeyboardManager(ShaderManager s);
		void executer(unsigned char c, int x, int y);
		void setShaderManager(ShaderManager s);
		
	protected:	
		
	private:
		MessagesManager mm;
		ShaderManager sm;
		char* className;
		
		double angle;
		double angleCumule;
		double azimut;
		double azimutCumule;
		double tX;
		double tY;
		double tZ;
		double tXCumule;
		double tYCumule;
		double tZCumule;
		bool displayWireMode;
		bool rotateScene;
		int windowID;
		
		void applyMoves();
		
};

#endif