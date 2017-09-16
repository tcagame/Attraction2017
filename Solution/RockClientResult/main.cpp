#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "Status.h"
#include "Message.h"
#include "RockViewer.h"
#include "RockMapResult.h"
#include "RockMilitary.h"
#include "RockCameraResult.h"
#include "RockDollHouse.h"
#include "RockStudio.h"
#include "RockFamily.h"
#include "RockClientInfo.h"
#include "MessageSender.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockTheaterResult.h"
#include "Sound.h"
#include "RockShadow.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( Sound::getTag( ), TaskPtr( new Sound ( "Resource/Sound" ) ) );

	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( status ) ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapResult ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitary ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( 0, 30, 160 ) ) ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury ) );
	app->addTask( RockCamera::getTag( ), TaskPtr( new RockCameraResult ) );
	app->addTask( RockStudio::getTag( ), TaskPtr( new RockStudio( ) ) );
	app->addTask( RockShadow::getTag( ), TaskPtr( new RockShadow( ) ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	app->addTask( RockTheater::getTag( ), TaskPtr( new RockTheaterResult( status ) ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	
	std::vector< unsigned char > state = { };
	state.push_back( AREA_RESULT );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( state ) ) );
}