#include <qapplication.h>
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

#include "MainView.h"

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	
	// The main window
	QWidget win;

	// The GL view
	QGLFormat format;
	format.setVersion( 4, 0 );
	format.setProfile( QGLFormat::CoreProfile );
	MainView *glView = new MainView( format );

	QVBoxLayout *mainLayout = new QVBoxLayout( &win );
	mainLayout->addWidget( glView );

	QWidget *cPanel = new QWidget( &win );
	QHBoxLayout *cPanelLayout = new QHBoxLayout();
	cPanel->setLayout( cPanelLayout );

	QPushButton *sShotButton = new QPushButton( "Screen Shot" );
	cPanelLayout->addWidget( sShotButton );
	QObject::connect( sShotButton, SIGNAL( clicked() ),glView, SLOT( takeScreenShot() ) );
	
	QPushButton *animButton = new QPushButton( "Start/Stop Animation" );
	cPanelLayout->addWidget( animButton );
	QObject::connect( animButton, SIGNAL( clicked() ), glView, SLOT( toggleAnimation() ) );

	mainLayout->addWidget( cPanel );

	win.setLayout( mainLayout );
	win.setWindowTitle( "Qt Test Application" );
	win.show();

	return app.exec();	
}