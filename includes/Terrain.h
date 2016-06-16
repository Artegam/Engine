#ifndef TERRAIN
#define TERRAIN

#include <GL/glee.h>
#include <vector>

#include <ObjParser.h>
#include <ObjetDeScene.h>
#include <ShaderManager.h>

using namespace std;

class Terrain: public ObjetDeScene {
	public:
		Terrain(ShaderManager* sm);		
		//void draw();
};

#endif