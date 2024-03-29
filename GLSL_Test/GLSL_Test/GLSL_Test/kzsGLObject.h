#pragma once
#ifndef KZSGLOBJECT_H
#define KZSGLOBJECT_H

#include <gl/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include "kzsGLUtil.h"

// **AddIncludes**
//+++++++++++++++++++++++++++++++
// additional include files

#include "GLOBAL_VARIABLES.h"
//#include "kzsPhysXFramework.h"
//#include "BouncingObject.h"

//
//+++++++++++++++++++++++++++++++

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
	#include <GL\glut.h>
#endif 


using namespace kzsGL;

//========================================================================
class kzsGLObject
{
private:	
	// disallow copy
	kzsGLObject( const kzsGLObject& rhs );
	kzsGLObject& operator=( const kzsGLObject& rhs );

protected:
	char* m_title;
public:
	kzsGLObject() {
		printf( "kzsGLObject Constructor called\n" );
		printf( "GLUT Initializing\n\n" );

		int _argc = 1;
		m_title = ( char* ) "OpenGLWindow";
		glutInit( &_argc, &m_title ); 
	};

	~kzsGLObject( void ) {
		printf( "kzsGLObject Destructor called\n" );
		
	};
	
	// ****UserDef****
	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	//
			// e.g) class declaration
	//
	//++++++++++++++++++++++++++++++++++++++++++++++++++++
		
	
	// ****kzsGLUtil****
	//----------------------------------------------------
			kzsGLUtil glUtil;
	//----------------------------------------------------
	
	
	//----------------------------------------------------
	void			display ( void );
	void 			resize  ( int w, int h );
	void			mouse   ( int button, int state, int x, int y );
	void			motion  ( int x, int y );
	void			keyboard( unsigned char key, int x, int y );
	void			idle( void );
	void            mousewheel( int wheel_number, int direction, int x, int y );
	void			initGL( void );
	void			kzsGlutInit( void );
	//----------------------------------------------------
		
	// ****runOpenGL****
	//--------------------------------------
	void runOpenGL( void ( *displayFunc    )(),
			        void ( *resizeFunc     )( int, int ),
		            void ( *mouseFunc      )( int, int, int, int ),
			        void ( *motionFunc     )( int, int ),
					void ( *keyboardFunc   )( unsigned char, int, int ),
			        void ( *idleFunc       )(),
					void ( *mousewheelFunc ) ( int, int, int, int ),
					const char window_title[] = "New Window" ) { // use default HIKISUU to avoid mess


		kzsGlutInit();
		
		glutCreateWindow( window_title );
		
		glutDisplayFunc   ( displayFunc    );
		glutReshapeFunc   ( resizeFunc     );
		glutMouseFunc     ( mouseFunc      );
		glutMotionFunc    ( motionFunc     );
		glutKeyboardFunc  ( keyboardFunc   );
		glutIdleFunc      ( idleFunc       );
		glutMouseWheelFunc( mousewheelFunc );
		initGL(); std::cout<< "initGL called in runOpenGL()" <<std::endl;

		glutMainLoop();
	}
	//--------------------------------------
	
};

#endif