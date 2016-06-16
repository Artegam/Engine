//$Author$
//$Date$
//$Version$
//$Rev$

#include <Terrain.h>

Terrain::Terrain(ShaderManager* sm): ObjetDeScene(sm) {
	chargerFichier(".\\ressources\\terrain.obj");
}
/*
void Terrain::draw() {
	//printf("Je dessine le terrain\n");
}*/