#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "StatusDrawer.h"
#include "StatusReceiver.h"
#include "Status.h"
#include "Message.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );

	TaskPtr drawer( new Drawer( "Resource" ) );
	TaskPtr client( new Client( status, message ) );
	TaskPtr status_receiver( new StatusReceiver );
	TaskPtr status_drawer( new StatusDrawer( status ) );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Client::getTag( ), client );
	app->addTask( StatusReceiver::getTag( ), status_receiver );
	app->addTask( StatusDrawer::getTag( ), status_drawer );
}