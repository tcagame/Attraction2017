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
#include "RockMilitaryResult.h"
#include "RockCameraResult.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockClientInfo.h"
#include "MessageSender.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockTheaterResult.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( status ) ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapResult ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitaryResult ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( 0, 10, 160 ) ) ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury ) );
	app->addTask( RockCamera::getTag( ), TaskPtr( new RockCameraResult ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	//app->addTask( RockTheater::getTag( ), TaskPtr( new RockTheaterResult( ) ) );
	app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	
	std::vector< unsigned int > state = { };
	state.push_back( STATE_RESULT );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( state ) ) );
}