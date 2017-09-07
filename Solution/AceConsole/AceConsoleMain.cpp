#include "Application.h"
#include "Client.h"
#include "SynchronousData.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "ViewerConsole.h"
#include "ace_define.h"
#include "Sound.h"

extern PLAYER getPlayer( );
void main( ) {
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( 640, 480 );

	SynchronousDataPtr data( new SynchronousData );
	ClientPtr client( new Client( data, DataPtr( ) ) );

	app->addTask( SynchronousData::getTag( ), data );
	app->addTask( Client::getTag( ), client );

	app->addTask( Drawer  ::getTag( )	  , DrawerPtr	    ( new Drawer( "Resource/Ace" ) ) );
	app->addTask( Sound   ::getTag( )     , SoundPtr        ( new Sound ( "Resource/Sound" ) ) );
	app->addTask( Keyboard::getTag( )	  , KeyboardPtr	    ( new Keyboard( ) ) );
	app->addTask( ViewerConsole::getTag( ), ViewerConsolePtr( new ViewerConsole( getPlayer( ) ) ) );
}
