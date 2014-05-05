#pragma once

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 
#if defined(WIN32)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma comment( lib, "glew32.lib" )

#include <glew.h>
#  include <gl/glut.h>
#  include "GLSL\glext.h"
#elif defined(__APPLE__) || defined(MACOSX)
#  include <GLUT/glut.h>
#else
#  define GL_GLEXT_PROTOTYPES
#  include <GL/glut.h>
#endif

#include "glsl.h"


class kzsGLSL
{
private:
	
	void			CompileShader( GLuint shader, const char* errorMessage );
	void			CreateProgramObject();
	void			LinkProgram();

	GLuint			vertShader;
	GLuint			fragShader;
	GLuint			shaderProgram;

	GLint			compiled;
	GLint			linked;

public:
	kzsGLSL(void);
	~kzsGLSL(void);

	void			initGlew();
	void			initShader( const char* vertFile, const char* fragFile );
	void			BeginShader(); // call before drawing
	void			EndShader(); // call after drawing
};

