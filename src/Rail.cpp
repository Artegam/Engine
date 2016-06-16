//$Author$
//$Date$
//$Version$
//$Rev$

#include <Rail.h>

Rail::Rail(ShaderManager* sm): ObjetDeScene(sm) {
	chargerFichier(".\\ressources\\rail_triangles.obj");
}

/*
void Rail::draw() {
	//printf("Rail draw()\n");
}*/