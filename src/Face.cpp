
#include <Face.h>

void Face::setMaterialName(char* pMaterialName) {
	sprintf(materialName, "%s", pMaterialName);
}

char* Face::getMaterialName(){
	return materialName;
}

long Face::getNbVertex() {
	if (!vertexNums.empty())
		return vertexNums.size();
	else
		return 0;
}

void Face::ajouterNumVertex(long numVertex) {
	vertexNums.insert(vertexNums.end(), numVertex);
}

void Face::ajouterNumVertexTexture(long numVertexTexture) {
	vertexTextNums.insert(vertexTextNums.end(), numVertexTexture);
}


void Face::ajouterNumVertexNormal(long numVertexNormal) {
	vertexNormalNums.insert(vertexNormalNums.end(), numVertexNormal);
}


void Face::dessiner(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal){
}


void Face::charger(vector<Vertex> pVertices, vector<VertexNormal> pVerticesNormal, vector<Vertex> *pVerticesResult, int *nbVertex){
//ASCH - 24/04/2015 - Correction du calcul des triangles
	int cpt = 0;

	*nbVertex = vertexNums.size();
	
	switch(vertexNums.size()) {
		case 3:
			//Premier triangle
			for(int i = 0; i < 3; i++) {
				int index = (int)vertexNums[i];
				pVertices[index-1].setMaterialName(materialName);
				pVerticesResult->insert(pVerticesResult->end(), pVertices[index-1]);
			}
			break;

		case 4:
			//Premier triangle
			for(int i = 0; i <= 2; i++) {
				int index = (int)vertexNums[i];
				pVertices[index-1].setMaterialName(materialName);
				pVerticesResult->insert(pVerticesResult->end(), pVertices[index-1]);
			}
			
			//Second triangle (2 derniers points + origine)
			for(int i = 3; i >= 2; i--) {
				int index = (int)vertexNums[i];
				pVertices[index-1].setMaterialName(materialName);
				pVerticesResult->insert(pVerticesResult->end(), pVertices[index-1]);
			}
			
			//Origine
			int index = (int)vertexNums[0];
			pVertices[index-1].setMaterialName(materialName);
			pVerticesResult->insert(pVerticesResult->end(), pVertices[index-1]);			
	}	
}

void Face::chargerNormales(vector<VertexNormal> pVerticesNormal, vector<VertexNormal> *pVerticesResult, int *nbVertex){
	//ASCH - 24/04/2015 - Correction du calcul des triangles
	int cpt = 0;
	*nbVertex = vertexNormalNums.size();
	
	switch(vertexNormalNums.size()) {		
		case 3:
			//Premier triangle		
			for(int i = 0; i < 3; i++) {
				int index = (int)vertexNormalNums[i];
				pVerticesResult->insert(pVerticesResult->end(), pVerticesNormal[index-1]);
			}			
			break;
		
		case 4:
			int index;
			//Premier triangle
			for(int i = 0; i <= 2; i++) {
				index = (int)vertexNormalNums[i];
				pVerticesResult->insert(pVerticesResult->end(), pVerticesNormal[index-1]);
			}
			
			//Second triangle (2 derniers points + origine)
			for(int i = 3; i >= 2; i--) {
				index = (int)vertexNormalNums[i];
				pVerticesResult->insert(pVerticesResult->end(), pVerticesNormal[index-1]);
			}
			
			//Origine
			index = (int)vertexNormalNums[0];
			pVerticesResult->insert(pVerticesResult->end(), pVerticesNormal[index-1]);
			break;			
	}	
}

void Face::chargerIndicesDansTabMemoire(int* tabMemoire, int &pointeur){
	for(int i = 0;i < vertexNums.size(); i++) {
		tabMemoire[pointeur] = vertexNums[i];
		pointeur++;
	}
}