#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "Status.h"
#include "Message.h"
#include "RockViewer.h"
#include "RockStreet.h"
#include "RockMilitaryStreet.h"
#include "RockMapStreetCamera.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockClientInfo.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockStreet ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitaryStreet ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status ) ) );
	app->addTask( RockMapStreetCamera::getTag( ), TaskPtr( new RockMapStreetCamera ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( STATE_STREET_1 ) ) );
}