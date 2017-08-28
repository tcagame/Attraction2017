#include "Application.h"
#include "define.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "Message.h"
#include "RockFamily.h"
#include "RockViewer.h"
#include "RockClientInfo.h"
#include "RockMapBoss.h"
#include "RockMapBossCamera.h"
#include "RockMilitatyBoss.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockDollHouse.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );

	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapBoss ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( 0, 100, 0 ) ) ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury( ) ) );
	app->addTask( RockMilitatyBoss::getTag( ), TaskPtr( new RockMilitatyBoss ) );
	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( ) ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( AREA_STREET_2 ) ) );
	app->addTask( RockMapBossCamera::getTag( ), TaskPtr( new RockMapBossCamera ) );
}
