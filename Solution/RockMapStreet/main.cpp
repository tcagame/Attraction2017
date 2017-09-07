#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "Message.h"
#include "RockViewer.h"
#include "RockMapStreet.h"
#include "RockMilitaryStreet.h"
#include "RockMapStreetCamera.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockClientInfo.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockStudio.h"
#include "MessageSender.h"
#include "sound.h"
#include "RockOffice.h"
#include "RockShadow.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );
	app->addTask( Sound::getTag( ), TaskPtr( new Sound ( "Resource/Sound" ) ) );

	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapStreet( status ) ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitaryStreet ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( 0, 30, -500 ) ) ) );
	app->addTask( RockMapStreetCamera::getTag( ), TaskPtr( new RockMapStreetCamera ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury( ) ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( status ) ) );
	app->addTask( RockOffice::getTag( ), TaskPtr( new RockOffice( ) ) );
	app->addTask( RockStudio::getTag( ), TaskPtr( new RockStudio( ) ) );
	app->addTask( RockShadow::getTag( ), TaskPtr( new RockShadow( ) ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	std::vector< unsigned int > state = { };
	state.push_back( AREA_STREET_1 );
	state.push_back( AREA_STREET_3 );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( state ) ) );
}