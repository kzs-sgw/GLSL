#include <Qt\qapplication.h>
#include <Qt\qwidget.h>


int main( int argc, char** argv )
{
	QApplication window( argc, argv );
	
	QWidget *mainwindow = new QWidget;

	//window.setActiveWindow( mainwindow );
	
	mainwindow->show();

	return window.exec();
}