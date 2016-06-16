//$Author$
//$Date$
//$Version$
//$Rev$

#include <ShaderManager.h>

ShaderManager::ShaderManager() {
	className = (char*)"ShaderManager";
	
	vbo = 0;
	vbo_c = 0;
	vbo_Ka = 0;
	vbo_Kd = 0;
	vbo_Ks = 0;	
	
	m = new MessagesManager();
}

void ShaderManager::init() {
	m->message(MM_INFO, className, "Initialisation des shaders...");
	// get version info
	const GLubyte* vendor = glGetString (GL_VENDOR); // Fournisseur
  const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version as a string	
  const GLubyte* glslversion = glGetString (GL_SHADING_LANGUAGE_VERSION); // version as a string	
	
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	
	m->message(MM_INFO, className, (const char*) vendor);
	m->message(MM_INFO, className, (const char*) renderer);
	m->message(MM_INFO, className, (const char*) version);
	sprintf(mBuffer, "GLSL %s", glslversion);
	m->message(MM_INFO, className, mBuffer);
	
	sprintf(mBuffer, "OpenGL %d.%d", major, minor);
	m->message(MM_INFO, className, mBuffer);
	
	//Affichage des extensions
	/*
		GLint nExtensions;
		glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
		for( int i = 0; i < nExtensions; i++ )
		printf("%s\n", glGetStringi( GL_EXTENSIONS, i )	);
	*/
	//fin affichage des extensions
	
	
	
	// FIN get version info		

	
	//Creation des shaders	
	vertShader = glCreateShader (GL_VERTEX_SHADER);
	fragShader = glCreateShader (GL_FRAGMENT_SHADER);

	//glShaderSource (fs, 1, &fragment_shader, NULL);
	
	const GLchar* ShaderSource = loadshader(".\\basic.vert");
	// printf("%s\n", ShaderSource);
	glShaderSource (vertShader, 1, &ShaderSource, NULL);
	
	glCompileShader (vertShader);
	
	//vertex shader
	GLint IsCompiled_VS;
	
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if(IsCompiled_VS == FALSE) {
		m->message(MM_ERR, className, "Erreur de compilation de shader (vertShader)");
		GLint logSize = 0;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logSize);
		// The logSize includes the NULL character
		GLchar errorLog[logSize];
		glGetShaderInfoLog(vertShader, logSize, &logSize, &errorLog[0]);
		printf("%s\n", errorLog);
		glDeleteShader(vertShader);
	}
	else	
		m->message(MM_INFO, className, "vertShader shader OK");
		
	//Fragment shader
	
	const GLchar* fragShaderSource = loadshader(".\\basic.frag");
	// printf("%s\n", fragShaderSource);
	glShaderSource (fragShader, 1, &fragShaderSource, NULL);	
	
	glCompileShader (fragShader);
	
	
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if(IsCompiled_VS == FALSE) {
		m->message(MM_ERR, className, "Erreur de compilation de shader (fragShader)");
		GLint logSize = 0;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logSize);
		// The logSize includes the NULL character
		GLchar errorLog[logSize];
		glGetShaderInfoLog(fragShader, logSize, &logSize, &errorLog[0]);
		printf("%s\n", errorLog);
		glDeleteShader(fragShader);		
	}
	else
		m->message(MM_INFO, className, "fragShader shader OK");
	
	//FIN Creation des shaders
	
	//Shader programme
	//create program
	shader_programme = glCreateProgram ();
	//Attach vertex and fragment shader
	glAttachShader (shader_programme, vertShader);
	glAttachShader (shader_programme, fragShader);
	//glBindAttribLocation(shader_programme, 0, "in_Position");	

	// insert location binding code here
	glBindAttribLocation (shader_programme, 0, "vp");
	glBindAttribLocation (shader_programme, 1, "vn");
	glBindAttribLocation (shader_programme, 2, "Kd");
	
	
	glLinkProgram(shader_programme);
	
	int linked;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &linked);
	//Make sure linked==TRUE	
	if(linked == FALSE)
	 m->message(MM_ERR, className, "Erreur de linkage shader !!");	
	
	
	glUseProgram(shader_programme);
	
	 
	//pour exercice 2 - Attention glLinkProgram doit être exécuté avant
	
	locColor = glGetUniformLocation(shader_programme, "vKa");
	if (locColor == -1)
		m->message(MM_ERR, className, "variable uniform vKa");
	
	//fin exrcice 2	 
	
	//FIN Shader programme	
	m->message(MM_INFO, className, "Initialisation terminee");

}

void ShaderManager::cleanShaders() {
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
	//glDisableVertexAttribArray(4);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glUseProgram(0);
	
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vbo_c);
	//glDeleteBuffers(1, &vbo_Ka);
	//glDeleteBuffers(1, &vbo_Kd);
	//glDeleteBuffers(1, &vbo_Ks);
	
	//glDeleteVertexArrays(objets.size(), vao);
	
	glDetachShader(shader_programme, vertShader);
	glDetachShader(shader_programme, fragShader);
	
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	
	glDeleteProgram(shader_programme);	
}

GLuint ShaderManager::getFragShader() {
	return fragShader;
}

GLuint ShaderManager::getVertexShader() {
	return vertShader;
}

GLuint ShaderManager::getShader_programme() {
	return shader_programme;
}

GLint ShaderManager::getLocColor() {
	return locColor;
}

const GLchar* ShaderManager::loadshader(const char* filename)
{
	const int NB_CHAR_MAX = 255;
	FILE* fichier;
	char ligne[NB_CHAR_MAX];
	string contenuFichier = "";
	
	fichier = fopen(filename, "r");
	
	while(!feof(fichier)) {
		ligne[0] = '\0';
		fgets(ligne, 255, fichier);
		if (contenuFichier == "")
			contenuFichier = ligne;
		else
			contenuFichier += ligne;
	}
	
	fclose(fichier);
	return contenuFichier.c_str();
}
