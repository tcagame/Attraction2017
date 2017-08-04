#include "Application.h"
#include "define.h"
#include "Task.h"
#include "Drawer.h"
#include "Client.h"
#include "Status.h"
#include "StatusDrawer.h"
#include "StatusReceiver.h"
#include "Status.h"
#include "Message.h"
#include "RockViewer.h"
#include "RockMap.h"
#include "RockMilitary.h"
#include "RockCamera.h"
#include "RockDollHouse.h"
#include "RockFamily.h"

void main( ) {

	StatusPtr status( new Status );
	MessagePtr message( new Message );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), TaskPtr( new Drawer( "Resource/Rock" ) ) );
	app->addTask( Client::getTag( ), TaskPtr( new Client( status, message ) ) );
	app->addTask( StatusReceiver::getTag( ), TaskPtr( new StatusReceiver ) );
	app->addTask( RockMap::getTag( ), TaskPtr( new RockMap ) );
	app->addTask( RockMilitary::getTag( ), TaskPtr( new RockMilitary ) );
	app->addTask( RockDollHouse::getTag( ), TaskPtr( new RockDollHouse ) );
	app->addTask( RockFamily::getTag( ), TaskPtr( new RockFamily( status ) ) );
	app->addTask( RockCamera::getTag( ), TaskPtr( new RockCamera ) );
	//debug•`‰æ(status)
	//app->addTask( StatusDrawer::getTag( ), TaskPtr( new StatusDrawer( status ) ) );
	//’Êí•`‰æ
	app->addTask( StatusDrawer::getTag( ), TaskPtr( new RockViewer( ) ) );
}