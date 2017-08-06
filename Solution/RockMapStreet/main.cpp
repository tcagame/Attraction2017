#include "Application.h"
#include "RockStreet.h"
#include "define.h"
#include "Drawer.h"

void main( ) {

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( RockStreet::getTag( ), TaskPtr( new RockStreet ) );

}