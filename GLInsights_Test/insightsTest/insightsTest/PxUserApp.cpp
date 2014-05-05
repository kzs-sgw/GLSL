#include "PxUserApp.h"




PxUserApp::PxUserApp() : globalGravity( 0.0f, -9.81f, 0.0f )
{	
	initPhysX();
}


PxUserApp::~PxUserApp(void)
{
}


//===============================================================================
// Rendering Functions

// **resize**
void PxUserApp::resize( int nw, int nh )
{
	camera.InReshape( nw, nh, 50 );
}


// **mouse**
void PxUserApp::mouse( int button, int s, int x, int y )
{
	camera.InMouse( button, s, x, y );
}


// **motion**
void PxUserApp::motion( int x, int y )
{
	camera.InMotion( x, y );
}


// **display**
void PxUserApp::display()
{
	camera.SetCameraPosition( GLPosition( 20 * sin( 0.0 ), 20, 20 * cos( 0.0 ) ) );
	

	if ( gScene ) StepPhysX();
	glClear( GL_COLOR_BUFFER_BIT );//| GL_DEPTH_BUFFER_BIT );
	
	//-------------------------------------------------
	// add Object to draw
	/*camera.SetModelViewProjectionMatrix( testShader, "ModelViewProjectionMatrix" );
	mat4 mv = camera.modelview;
	cout<< "mv: " << mv[1][0] << ", " << mv[1][1] << ", "
				  << mv[1][2] << ", " << mv[1][3] <<endl;
	testShader.setUniform( "ModelViewMatrix", mv );
	testShader.setUniform( "NormalMatrix", mat3( vec3( mv[0] ), vec3( mv[1] ), vec3( mv[2] ) ) );
	*/
	camera.updataMatrices();

	glDrawArrays( GL_TRIANGLES, 0, 6 );
	
	//-------------------------------------------------
	
	//glUtil.RenderFramerate( WINDOW_WIDTH, WINDOW_HEIGHT );

	glutSwapBuffers();


}


// **idle**
void PxUserApp::idle()
{
	glutPostRedisplay();
}


// **keyboard**
void PxUserApp::keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case '\033':
			exit( 0 );
			break;

		case 'n':
			glUtil.toggleFaceDirection();
			break;

		default:
			break;  
	}
}


// **mousewheel**
void PxUserApp::mousewheel( int wheel_number, int direction, int x, int y )
{
	camera.InMouseWheel( wheel_number, direction, x, y );
}


// **initGL**
void PxUserApp::initGL()
{
	ActivateGLSL();

	kzsGLObject::initGL();
	cout << "GLSL version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << endl;
	cout << "" << endl;

	cout << "Vendor :"<<glGetString(GL_VENDOR)<<'\n';
	cout << "GPU : "<<glGetString(GL_RENDERER) <<'\n';
	cout << "OpenGL ver. " <<glGetString(GL_VERSION)<<'\n';
	//cout << "yŠg’£‹@”\ˆê——z"<<endl;
	//cout << glGetString(GL_EXTENSIONS) <<endl;
	cout << endl;
	//----------------------------------------------------------------

	vec2 points[ 6 ] =
	{
		vec2( -5, -5 ), vec2(  5, -5 ),
		vec2(  5,  5 ), vec2(  5,  5 ),
		vec2( -5,  5 ), vec2( -5, -5 ) 
	};

	
	vec3 colors[ 6 ] = 
	{
		vec3( 1.0, 0.0, 0.0 ), vec3( 0.0, 1.0, 0.0 ),
		vec3( 0.0, 0.0, 1.0 ), vec3( 1.0, 1.0, 0.0 ),
		vec3( 1.0, 0.0, 1.0 ), vec3( 0.0, 1.0, 1.0 )
	};

	GLuint vao, buffer[ 2 ];
	
	glGenBuffers( 2, buffer );
	GLuint positionVBO = buffer[ 0 ];
	GLuint colorVBO    = buffer[ 1 ];
	
	glBindBuffer( GL_ARRAY_BUFFER, positionVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), points, GL_STATIC_DRAW );
	
	glBindBuffer( GL_ARRAY_BUFFER, colorVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colors ), colors, GL_STATIC_DRAW );

	//----------------------------------------------------------------
	
	// GLSL shader Initialization
	testShader.initShaderProgram( "shader/test/simple.vert", "shader/test/simple.frag" );
	testShader.printActiveAttribs();
	testShader.printActiveUniforms();
	testShader.BeginShader();

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	GLuint pos_loc = testShader.getAttribLocation( "vPosition" );
	glBindBuffer( GL_ARRAY_BUFFER, positionVBO );
	glEnableVertexAttribArray( pos_loc );
	glVertexAttribPointer( pos_loc, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	GLuint clr_loc = testShader.getAttribLocation( "vColor" );
	glBindBuffer( GL_ARRAY_BUFFER, colorVBO );
	glEnableVertexAttribArray( clr_loc );
	glVertexAttribPointer( clr_loc, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	
	glBindVertexArray( vao );


	camera.SetMatrices( testShader );


	glClearColor( 0.0, 0.0, 0.0, 1.0 );
}


//===============================================================================
//===============================================================================
// PhysX simulation Functions
void PxUserApp::initPhysX()
{
	printf( "**initializing PhysX**\n" );
	initPx_Foundation_Physics_Extensions();
	initPx_CreateScene( globalGravity );

	//-------------------------------------------------
			// add code to initialize
	//-------------------------------------------------
	
	printf( "**PhysX initialized**\n\n" );
}


//===============================================================================
//===============================================================================
// User Added Funcitons
