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

	public:
		Vertex();

		void setX(double pX);
		void setY(double pY);
		void setZ(double pZ);
		void setW(double pW);

		double getX();
		double getY();
		double getZ();
		double getW();

		void dessiner();
};

#endif
