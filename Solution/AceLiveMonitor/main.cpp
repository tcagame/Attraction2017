#include "Application.h"
#include "Drawer.h"
#include "Device.h"
#include "ace_define.h"
#include "Game.h"

void main( ) {
	TaskPtr drawer( new Drawer( "../Resource/Ace" ) );
	TaskPtr device( new Device( ) );
	TaskPtr game( new Game( ) );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Device::getTag( ), device );
	app->addTask( Game::getTag( ), game );
}