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
#include "RockMilitaryTest.h"
#include "RockCamera.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockClientInfo.h"
#include "MessageSender.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockMapTest ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitaryTest ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status ) ) );
	app->addTask( RockCamera::getTag( ), TaskPtr( new RockCamera ) );
	app->addTask( RockClientInfo::getTag( ), TaskPtr( new RockClientInfo( STATE_TEST ) ) );
	app->addTask( MessageSender::getTag( ), TaskPtr( new MessageSender( message ) ) );
	
	//通常描画orステータス描画
	bool status_draw = false;
	if ( status_draw ) {
		app->addTask( StatusDrawer::getTag( ), TaskPtr( new StatusDrawer( status ) ) );
	} else {
		app->addTask( RockViewer::getTag( ), TaskPtr( new RockViewer( status ) ) );
	}
}