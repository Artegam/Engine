
#include <Vertex.h>


Vertex::Vertex() {
	w = 1.0;
	sprintf(materialName, "%s", "");
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

void Vertex::setMaterialName(char* pMaterialName) {
	sprintf(materialName, "%s", pMaterialName);
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

const char* Vertex::getMaterialName() {
	return materialName;
}

void Vertex::dessiner() {
	glVertex3d(x, y, z);
}
