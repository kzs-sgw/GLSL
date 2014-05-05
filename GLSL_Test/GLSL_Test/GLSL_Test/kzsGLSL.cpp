#include "kzsGLSL.h"

kzsGLSL::kzsGLSL(void)
{
}


kzsGLSL::~kzsGLSL(void)
{
}


void kzsGLSL::initGlew()
{
	GLenum err = glewInit();
	if ( err != GLEW_OK ) printf( "Error: %s\n", glewGetErrorString( err ) );
	
	if ( glslInit() )  printf("error in glslInit" ); //exit( 1 );
}


void kzsGLSL::initShader( const char* vertFile, const char* fragFile )
{
	//initGlew();

	vertShader = glCreateShader( GL_VERTEX_SHADER );
	fragShader = glCreateShader( GL_FRAGMENT_SHADER );

	 
	if ( readShaderSource( vertShader, vertFile ) ) exit( 1 );
	if ( readShaderSource( fragShader, fragFile ) ) exit( 1 );

	
	CompileShader( vertShader, "Compile error in vertex shader.\n" );
	CompileShader( fragShader, "Compile error in fragment shader.\n" );
	
	CreateProgramObject();
	LinkProgram();
}


void kzsGLSL::CompileShader( GLuint shader, const char* errorMessage )
{
	glCompileShader( shader );
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	printShaderInfoLog( shader );
	if ( compiled == GL_FALSE )
	{
		fprintf( stderr, errorMessage );
		exit( 1 );
	}
}


void kzsGLSL::CreateProgramObject()
{
	shaderProgram = glCreateProgram();

	glAttachShader( shaderProgram, vertShader );
	glAttachShader( shaderProgram, fragShader );

	glDeleteShader( vertShader );
	glDeleteShader( fragShader );
}


void kzsGLSL::LinkProgram()
{
	glLinkProgram( shaderProgram );
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &linked );
	printProgramInfoLog( shaderProgram );
	if ( linked == GL_FALSE )
	{
		fprintf( stderr, "Link error.\n" );
		exit( 1 );
	}
}


void kzsGLSL::BeginShader()
{
	glUseProgram( shaderProgram );
}


void kzsGLSL::EndShader()
{
	glUseProgram( 0 );
}