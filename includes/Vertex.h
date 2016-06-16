#ifndef VERTEX_H
#define VERTEX_H

#include <windows.h>
#include <stdio.h>
#include <GL/freeglut.h>

class Vertex {
	private:
		double x;
		double y;
		double z;
		double w;
		char materialName[255];

	public:
		Vertex();

		void setX(double pX);
		void setY(double pY);
		void setZ(double pZ);
		void setW(double pW);
		void setMaterialName(char* pMaterialName);

		double getX();
		double getY();
		double getZ();
		double getW();
		const char* getMaterialName();

		void dessiner();
};

#endif
