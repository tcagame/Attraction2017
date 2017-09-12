#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "StatusDrawer.h"
#include "Status.h"
#include "Message.h"
#include "RockViewer.h"
#include "RockMapTest.h"
#include "RockMilitary.h"
#include "RockCameraTest.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockClientInfo.h"
#include "MessageSender.h"
#include "RockArmoury.h"
#include "Effect.h"
#include "RockStorage.h"
#include "RockTheaterTest.h"
#include "RockStudio.h"
#include "RockShadow.h"
#include "Sound.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Effect::getTag( ), TaskPtr( new Effect( "Resource/Rock/effect" ) ) );
	app->addTask( Sound::getTag( ), TaskPtr( new Sound ( "Resource/Sound" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( RockStorage::getTag( ), TaskPtr( new RockStorage( status ) ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitary ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapTest ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status, Vector( 0, 10, 160 ) ) ) );
	app->addTask( RockArmoury::getTag( ), TaskPtr( new RockArmoury ) );
	app->addTask( RockCamera::getTag( ), TaskPtr( new RockCameraTest ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	//app->addTask( RockTheater::getTag( ), TaskPtr( new RockTheaterTest( ) ) );
	app->addTask( RockShadow::getTag( ), TaskPtr( new RockShadow( ) ) );
	app->addTask( RockStudio::getTag( ), TaskPtr( new RockStudio( ) ) );

	std::vector< unsigned char > state = { };
	state.push_back( AREA_TEST );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( state ) ) );
	
	//通常描画orステータス描画
	bool status_draw = false;
	if ( status_draw ) {
		app->addTask( StatusDrawer::getTag( ), TaskPtr( new StatusDrawer( status ) ) );
	} else {
		app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	}
}