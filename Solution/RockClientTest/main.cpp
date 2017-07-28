#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"

void main( ) {
	TaskPtr drawer( new Drawer( "Resource" ) );
	TaskPtr client( new Client );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Client::getTag( ), client );
}