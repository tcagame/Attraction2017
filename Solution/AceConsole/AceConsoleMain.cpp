#include "Application.h"
#include "Client.h"
#include "SynchronousData.h"
#include "Drawer.h"
#include "Device.h"
#include "Keyboard.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( 640, 480 );

	SynchronousDataPtr data( new SynchronousData );
	ClientPtr client( new Client( data, DataPtr( ) ) );

	app->addTask( SynchronousData::getTag( ), data );
	app->addTask( Client::getTag( ), client );

	app->addTask( Drawer  ::getTag( ), DrawerPtr( new Drawer( "Resource/Ace" ) ) );
	app->addTask( Device  ::getTag( ), DevicePtr( new Device( ) ) );
	app->addTask( Keyboard::getTag( ), KeyboardPtr( new Keyboard( ) ) );
}
