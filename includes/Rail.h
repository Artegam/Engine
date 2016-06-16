#ifndef RAIL
#define RAIL

#include <GL/glee.h>
#include <vector>

#include <ObjParser.h>
#include <ObjetDeScene.h>
#include <ShaderManager.h>

using namespace std;

class Rail: public ObjetDeScene {
	public:
		Rail(ShaderManager* sm);
		//void draw();
};

#endif

