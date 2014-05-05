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



class kzsGLSL
{
private:
	int				readShaderSource( GLuint shader, const char* filename );
	void			CompileShader( GLuint shader, const char* errorMessage );
	void			CreateProgramObject( bool IsFragExist );
	void			LinkProgram();

	GLuint			vertShader;
	GLuint			fragShader;
	GLuint			shaderProgram;

	GLint			compiled;
	GLint			linked;

	enum			{ FRAG_EXIST = 1 }; // true
	enum			{ FRAG_NONE  = 0 }; // false


public:
	kzsGLSL(void);
	~kzsGLSL(void);

	void			initShaderProgram( const char* vertFile ); // call in initGL()
	void			initShaderProgram( const char* vertFile, const char* fragFile ); // call in initGL()
	void			BeginShader(); // call before drawing
	void			EndShader(); // call after drawing
};

