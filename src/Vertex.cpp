
#include <Vertex.h>


Vertex::Vertex() {
	w = 1.0;
}

void Vertex::setX(double pX) {
	x = pX;
}

void Vertex::setY(double pY) {
	y = pY;
}

void Vertex::setZ(double pZ) {
	z = pZ;
}

void Vertex::setW(double pW) {
	w = pW;
}

double Vertex::getX() {
	return x;
}

double Vertex::getY() {
	return y;
}

double Vertex::getZ(){
	return z;
}

double Vertex::getW(){
	return w;
}

void Vertex::dessiner() {
	glVertex3d(x, y, z);
}
