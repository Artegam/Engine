#include <stdio.h>
#include <cstring>
#include <map>
#include <string>


#include <Material.h>


using namespace std;


class MtlParser{

	private:
		map<string, Material> materials;
		Material * vMat;
	
	public:
		map<string, Material> readMaterials(const char* filename);

};