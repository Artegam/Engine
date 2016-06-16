#ifndef SHADERMANAGER
#define SHADERMANAGER

#include <GL/glee.h>
#include <stdio.h>
#include <fstream>

#include <MessagesManager.h>

using namespace std;

		
class ShaderManager {
	public:
		ShaderManager();		
		void init();
		void cleanShaders();
		
		GLuint getFragShader();
		GLuint getVertexShader();
		GLuint getShader_programme();
		GLint getLocColor();
		
		
	private:
		MessagesManager* m;
		char mBuffer[150];
		char* className;
		
		GLuint vertShader;
		GLuint fragShader;
		GLuint shader_programme;
		GLint locColor;
		
		GLuint* vao;
		GLuint vbo;
		GLuint vbo_c;
		GLuint vbo_Ka;
		GLuint vbo_Kd;
		GLuint vbo_Ks;
		
		const GLchar* loadshader(const char* filename);
		int unloadshader(GLubyte** ShaderSource);

};

#endif