#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "StatusDrawer.h"
#include "StatusReceiver.h"

void main( ) {
	TaskPtr drawer( new Drawer( "Resource" ) );
	TaskPtr client( new Client );
	TaskPtr status_receiver( new StatusReceiver );
	TaskPtr status_drawer( new StatusDrawer );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Client::getTag( ), client );
	app->addTask( StatusReceiver::getTag( ), status_receiver );
	app->addTask( StatusDrawer::getTag( ), status_drawer );
}