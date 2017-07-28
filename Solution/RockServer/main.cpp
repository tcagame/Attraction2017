#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Device.h"
#include "Server.h"
#include "Command.h"
#include "StatusSender.h"
#include "TableDrawer.h"
#include "Log.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( )		 , TaskPtr( new Drawer( "Resource" ) ) );
	app->addTask( Keyboard::getTag( )	 , TaskPtr( new Keyboard ) );
	app->addTask( Device::getTag( )		 , TaskPtr( new Device ) );
	app->addTask( Command::getTag( )	 , TaskPtr( new Command ) );
	app->addTask( Log::getTag( )		 , TaskPtr( new Log ) );
	app->addTask( StatusSender::getTag( ), TaskPtr( new StatusSender ) );
	app->addTask( TableDrawer::getTag( ) , TaskPtr( new TableDrawer ) );
	app->addTask( Server::getTag( )		 , TaskPtr( new Server ) );
}