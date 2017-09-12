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
#include "RockMilitary.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockDollHouse.h"
#include "RockStudio.h"
#include "MessageSender.h"
#include "Sound.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );

	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );
	app->addTask( Sound::getTag( ), TaskPtr( new Sound ( "Resource/Sound" ) ) );

	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapBoss( status ) ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( -700, 75, -25 ) ) ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury( ) ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitary ) );
	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( status ) ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	app->addTask( RockStudio::getTag( ), TaskPtr( new RockStudio( ) ) );
	app->addTask( RockMapBossCamera::getTag( ), TaskPtr( new RockMapBossCamera ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	std::vector< unsigned char > state = { };
	state.push_back( AREA_STREET_2 );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( state ) ) );
}
