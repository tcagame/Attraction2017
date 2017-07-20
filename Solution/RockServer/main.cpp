#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Device.h"
#include "Server.h"

void main( ) {
	TaskPtr drawer( new Drawer( "Resource" ) );
	TaskPtr keyboard( new Keyboard );
	TaskPtr device( new Device );
	TaskPtr controller( new Controller );
	TaskPtr server( new Server );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Keyboard::getTag( ), keyboard );
	app->addTask( Device::getTag( ), device );
	app->addTask( Controller::getTag( ), controller );
	app->addTask( Server::getTag( ), server );
}