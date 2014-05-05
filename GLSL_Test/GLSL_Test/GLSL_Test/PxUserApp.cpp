#include "PxUserApp.h"


PxUserApp::PxUserApp() : globalGravity( 0.0f, -9.81f, 0.0f )
{
	startTime	= 0;
	totalFrames	= 0;
	fps			= 0;

	initPhysX();


	// light initialize
	GLfloat Lpos[] = { 0.0f, 0.0f, 5.0f, 1.0f }; /* à íuÅ@Å@Å@ */
	GLfloat Lcol[] = { 1.0f, 1.0f, 1.0f, 1.0f }; /* íºê⁄åıã≠ìx */
	GLfloat Lamb[] = { 0.1f, 0.1f, 0.1f, 1.0f }; /* ä¬ã´åıã≠ìx */

	for (int i = 0; i < 3; i++)
	{
		lightpos[ i ] = Lpos[ i ];
		lightcol[ i ] = Lcol[ i ];
		lightamb[ i ] = Lamb[ i ];
	}

	 glDisable(GL_CULL_FACE);
	 
	 /* åıåπÇÃèâä˙ê›íË */
	 glEnable(GL_LIGHTING);
	 glEnable(GL_LIGHT0);
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	 glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
	 glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
	 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}


PxUserApp::~PxUserApp(void)
{
}


//===============================================================================
// Rendering Functions

void PxUserApp::RenderFramerate()
{
	totalFrames++;

	int current = glutGet( GLUT_ELAPSED_TIME );
	
	if ( ( current - startTime ) > 1000 )
	{
		float elapsedTime = float ( current - startTime );
		fps = ( ( totalFrames * 1000.0f ) / elapsedTime );
		startTime = current;
		totalFrames = 0;
	}


	sprintf_s( buffer, " *** ROTATE WITH MOUSE RIGHT_BUTTON  |  FPS: %3.2f",fps);

	glUtil.setOrthoForFont( WINDOW_WIDTH, WINDOW_HEIGHT );
	glColor3f( 1, 1, 1 );
	glUtil.RenderSpacedBitmapString( 20, 20, 0, GLUT_BITMAP_HELVETICA_12, buffer );
	glUtil.ResetPerspectiveProjection();
}


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
	
	
	glUtil.drawGrid( 10 );
	
	//simpleShader.BeginShader();
	scene();
	//simpleShader.EndShader();

	//-------------------------------------------------

			// add Object to draw

	//-------------------------------------------------
	
	RenderFramerate();

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


void PxUserApp::initGL()
{
	kzsGLObject::initGL();
	simpleShader.initGlew();
	simpleShader.initShader( "simple.vert", "simple.frag" ); cout<< "initShader" <<endl;
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
	
	printf( "**PhysX initialized**\n" );
}


//===============================================================================
//===============================================================================
// User Added Funcitons
void PxUserApp::scene(void)
{
  static const GLfloat diffuse[] = { 0.6f, 0.1f, 0.1f, 1.0f };
  static const GLfloat specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };

  /* çﬁéøÇÃê›íË */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);

#if 1
  /* ÇPñáÇÃÇSäpå`Çï`Ç≠ */
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

