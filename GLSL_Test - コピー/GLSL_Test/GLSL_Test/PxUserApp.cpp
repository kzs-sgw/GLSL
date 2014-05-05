#include "PxUserApp.h"


PxUserApp::PxUserApp() : globalGravity( 0.0f, -9.81f, 0.0f ),
						 light( GL_LIGHT0 )
{	
	initPhysX();

	// light initialize
	glDisable(GL_CULL_FACE);
	 
	GLColor    amb( 0.1f, 0.1f, 0.1f, 1.0f );
	GLColor    dif( 1.0f, 1.0f, 1.0f, 1.0f );
	GLColor    spc( 1.0f, 1.0f, 1.0f, 1.0f );
	GLPosition pos( 0.0f, 0.0f, 5.0f, 1.0f );

	light.SetParams( amb, dif, spc, pos );
	
	light.showLightInfo();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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

	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	camera.MulCameraMatrix();

	glUtil.drawAxes(); 
	
	GLColor gray( 0.7, 0.7, 0.7 );
	glUtil.drawGrid( 10, gray );
	
	//-------------------------------------------------
	// add Object to draw
	
	cooktorrance.BeginShader();
	scene();
	cooktorrance.EndShader();
	
	//-------------------------------------------------
	
	glUtil.RenderFramerate( WINDOW_WIDTH, WINDOW_HEIGHT );

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

		case 'k':
			camera.ZoomIn();
			break;
			
		case 'j':
			camera.ZoomOut();
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
	
	// GLSL shader Initialization
	//simpleShader.initShaderProgram( "simple.vert", "simple.frag" ); // be careful to use CORRECT FILENAME!!
	//gouraud.initShaderProgram( "shader/gouraud/gouraud.vert", "shader/gouraud/gouraud.frag" );
	//phong.initShaderProgram( "shader/phong/phong.vert", "shader/phong/phong.frag" );
	cooktorrance.initShaderProgram( "shader/cooktorrance/cooktorrance.vert", "shader/cooktorrance/cooktorrance.frag" );

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
void PxUserApp::scene(void)
{
  static GLfloat diffuse[] = { 0.6f, 0.1f, 0.1f, 1.0f };
  static GLfloat specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };

  // material settings
  material.SetFaceType( GL_FRONT_AND_BACK );
  material.ActivateMaterial( diffuse, diffuse, specular );

#if 0
  // draw a square
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3d(-1.0, -1.0,  0.0);
  glVertex3d( 1.0, -1.0,  0.0);
  glVertex3d( 1.0,  1.0,  0.0);
  glVertex3d(-1.0,  1.0,  0.0);
  glEnd();
#else
  glutSolidTeapot(1.0);
#endif
}

