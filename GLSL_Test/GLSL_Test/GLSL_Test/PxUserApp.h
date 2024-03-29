// This class is your Application
// Add code to this file
// 
// display() is called as the DisplayFunction in main.cpp
// OnRender() includes PhysX functions with OpenGL
// make sure OnRender() is called in display()
//
// namespace "physx", "std", "kzsGL" are activated
// 
//

#pragma once

#include "kzsGLSL.h"
#include "kzsPhysXFramework.h"
#include "kzsGLObject.h"
#include "DrawPxShapes.h"
#include "GLCamera.h"

//#include "GLOBAL_VARIABLES.h"

//+++++++++++++++++++++++++++++++
		// add includes
//+++++++++++++++++++++++++++++++

const int Max_Path = 16384;


class PxUserApp : public kzsPhysXFramework,
	              public kzsGLObject
{
public:
	PxUserApp();
	~PxUserApp(void);

	// Rendering Functions
	void			RenderFramerate();
	void			resize( int nw, int nh );
	void			mouse ( int button, int s, int x, int y );
	void			motion( int x, int y );
	void			display();
	void			idle();
	void			keyboard( unsigned char key, int x, int y );
	void			mousewheel( int wheel_number, int direction, int x, int y );
	void			initGL();

	// PhysX Functions
	void			initPhysX();

	//User Functions
	void			scene();

	// Variables
	char			buffer[ Max_Path ]; // message buffer

	const PxVec3	globalGravity;

	DrawPxShapes	drawObj;
	GLCamera		camera;
	kzsGLSL			simpleShader;


	// light status
	GLfloat lightpos[ 4 ];
	GLfloat lightcol[ 4 ];
	GLfloat lightamb[ 4 ];
	

};

