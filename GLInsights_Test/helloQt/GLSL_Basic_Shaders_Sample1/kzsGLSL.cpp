#include "kzsGLSL.h"

kzsGLSL::kzsGLSL(void)
{
}


kzsGLSL::~kzsGLSL(void)
{
}


int kzsGLSL::readShaderSource( GLuint shader, const char* file )
{
	FILE *fp;
	char *buf;
	GLsizei size;

	// Open File
	fp = fopen( file, "rb" );
	if ( !fp ) 
	{
		printf( "do not exist file %s\n", file );
		return -1;
	}

	// move to the end of file
	fseek( fp, 0, SEEK_END );
	size = ftell( fp ); // get file size

	// reserve memory
	buf = ( GLchar* ) malloc( size );
	if ( buf == NULL )
	{
		printf( "could not allocate read buffer\n" );
		return -1;
	}

	// read file from head
	fseek( fp, 0, SEEK_SET );
	fread( buf, 1, size, fp );

	// set program to shader object
	glShaderSource( shader, 1, ( const GLchar** ) &buf, &size );

	free( buf );
	fclose( fp );

	return 0;
}


void kzsGLSL::CompileShader( GLuint shader, const char* errorMessage )
{
	glCompileShader( shader );
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	//printShaderInfoLog( shader );
	if ( compiled == GL_FALSE )
	{
		fprintf( stderr, errorMessage );

		// get error log length
		int logLen, charsWritten;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );

		// get error log
		char* infoLog = new char[ logLen ];
		glGetShaderInfoLog( shader, logLen, &charsWritten, infoLog );

		printf( "%s", infoLog );
		delete[] infoLog;


		exit( 1 );
	}
}


void kzsGLSL::CreateProgramObject( bool IsFragExist )
{
	shaderProgram = glCreateProgram();

	glAttachShader( shaderProgram, vertShader );
	if ( IsFragExist )
	{
	glAttachShader( shaderProgram, fragShader );
	}


	glDeleteShader( vertShader );
	if ( IsFragExist )
	{
	glDeleteShader( fragShader );
	}
}


void kzsGLSL::LinkProgram()
{
	glLinkProgram( shaderProgram );
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &linked );
	//printProgramInfoLog( shaderProgram );
	if ( linked == GL_FALSE )
	{
		fprintf( stderr, "Link error.\n" );
		exit( 1 );
	}
}


void kzsGLSL::initShaderProgram( const char* vertFile )
{
	vertShader = glCreateShader( GL_VERTEX_SHADER );
	 
	if ( readShaderSource( vertShader, vertFile ) ) exit( 1 );
	
	CompileShader( vertShader, "Compile error in vertex shader.\n\n" );
	
	CreateProgramObject( FRAG_NONE );
	LinkProgram();
}


void kzsGLSL::initShaderProgram( const char* vertFile, const char* fragFile )
{	
	vertShader = glCreateShader( GL_VERTEX_SHADER );
	fragShader = glCreateShader( GL_FRAGMENT_SHADER );

	 
	if ( readShaderSource( vertShader, vertFile ) ) exit( 1 );
	if ( readShaderSource( fragShader, fragFile ) ) exit( 1 );

	
	CompileShader( vertShader, "Compile error in vertex shader.\n\n" );
	CompileShader( fragShader, "Compile error in fragment shader.\n\n" );
	
	CreateProgramObject( FRAG_EXIST );
	LinkProgram();
}


void kzsGLSL::BeginShader()
{
	glUseProgram( shaderProgram );
}


void kzsGLSL::EndShader()
{
	glUseProgram( 0 );
}