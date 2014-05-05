#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "kzsGLUtil.h"


#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
	#include <GL\glut.h>
#endif 

namespace kzsGL{

	class GLCamera
	{
	public:
		GLCamera(void);
		GLCamera( GLPosition cPos, GLPosition tPos, GLPosition vuVec = GLPosition( 0.0f, 1.0f, 0.0f ) );
		~GLCamera(void);


		GLPosition		cameraPos;
		GLPosition		targetPos;
		GLPosition		viewUpVec;

		int				oldX;
		int				oldY;
		int				camera_state;

		float			rX;
		float			rY;
		float			dist;

		void			SetCameraPosition( GLPosition cPos  );
		void			SetTargetPosition( GLPosition tPos  );
		void			SetViewUpVector  ( GLPosition vuVec );
		void			MulCameraMatrix();
		void			InReshape( int nw, int nh, GLdouble persAngular );
		void			InMouse( int button, int state, int x, int y );
		void			InMotion( int x, int y, bool doRedisplay = true );
		void			InMouseWheel( int wheel_number, int direction, int x, int y );
		void			ZoomIn();
		void			ZoomOut();

	};

}