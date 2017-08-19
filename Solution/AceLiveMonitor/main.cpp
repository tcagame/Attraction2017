#include "Application.h"
#include "Drawer.h"
#include "Device.h"
#include "Keyboard.h"
#include "ace_define.h"
#include "Family.h"
#include "Armoury.h"
#include "Viewer.h"
#include "Map.h"
#include "MapEvent.h"
#include "Military.h"
#include "NPC.h"
#include "Storage.h"
#include "Popper.h"
#include "SynchronousData.h"
#include "Debug.h"
#include "Server.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) ); 
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );

	SynchronousDataPtr data( new SynchronousData );
	ServerPtr server( new Server( data ) );
	server->saveIP( );

	app->addTask( Server::getTag( ), server );
	app->addTask( SynchronousData::getTag( ), data );

	app->addTask( Drawer  ::getTag( ), DrawerPtr( new Drawer( "Resource/Ace" ) ) );
	app->addTask( Device  ::getTag( ), DevicePtr( new Device( ) ) );
	app->addTask( Keyboard::getTag( ), KeyboardPtr( new Keyboard( ) ) );

	app->addTask( Map     ::getTag( ), MapPtr     ( new Map     ( ) ) );
	app->addTask( MapEvent::getTag( ), MapEventPtr( new MapEvent( ) ) );
	app->addTask( Family  ::getTag( ), FamilyPtr  ( new Family  ( ) ) );
	app->addTask( Armoury ::getTag( ), ArmouryPtr ( new Armoury ( ) ) );
	app->addTask( Storage ::getTag( ), StoragePtr ( new Storage ( ) ) );
	app->addTask( Popper  ::getTag( ), PopperPtr  ( new Popper  ( ) ) );
	app->addTask( Military::getTag( ), MilitaryPtr( new Military( ) ) );
	app->addTask( NPC	  ::getTag( ), NPCPtr	  ( new NPC		( ) ) );
	app->addTask( Debug	  ::getTag( ), DebugPtr   ( new Debug   ( ) ) );
	app->addTask( Viewer  ::getTag( ), ViewerPtr  ( new Viewer  ( ) ) );
}