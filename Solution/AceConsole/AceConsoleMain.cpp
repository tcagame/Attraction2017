#include "Application.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( 640, 480 );
}
