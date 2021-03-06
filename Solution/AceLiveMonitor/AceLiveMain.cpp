#include "Application.h"
#include "Drawer.h"
#include "Device.h"
#include "Keyboard.h"
#include "ace_define.h"
#include "Family.h"
#include "Armoury.h"
#include "ViewerLive.h"
#include "World.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"
#include "Popper.h"
#include "SynchronousData.h"
#include "Debug.h"
#include "Server.h"
#include "Sender.h"
#include "Magazine.h"
#include "Sound.h"
#include "Property.h"
#include "Monmotaro.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) ); 
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );

	SynchronousDataPtr data( new SynchronousData );
	ServerPtr server( new Server( DataPtr( ) ) );
	server->saveIP( );

	app->addTask( Server::getTag( ), server );
	app->addTask( SynchronousData::getTag( ), data );

	app->addTask( Drawer  ::getTag( ), DrawerPtr( new Drawer( "Resource/Ace" ) ) );
	app->addTask( Sound   ::getTag( ), SoundPtr( new Sound( "Resource/Sound" ) ) );
	app->addTask( Device  ::getTag( ), DevicePtr( new Device( ) ) );
	app->addTask( Keyboard::getTag( ), KeyboardPtr( new Keyboard( ) ) );
	
	app->addTask( World     ::getTag( ), WorldPtr     ( new World     ( ) ) );
	app->addTask( Family    ::getTag( ), FamilyPtr    ( new Family    ( ) ) );
	app->addTask( Armoury   ::getTag( ), ArmouryPtr   ( new Armoury   ( ) ) );
	app->addTask( Magazine  ::getTag( ), MagazinePtr  ( new Magazine  ( ) ) );
	app->addTask( Storage   ::getTag( ), StoragePtr   ( new Storage   ( ) ) );
	app->addTask( Popper    ::getTag( ), PopperPtr    ( new Popper    ( ) ) );
	app->addTask( Military  ::getTag( ), MilitaryPtr  ( new Military  ( ) ) );
	app->addTask( Office    ::getTag( ), OfficePtr	  ( new Office    ( ) ) );
	app->addTask( Debug	    ::getTag( ), DebugPtr     ( new Debug     ( ) ) );
	app->addTask( Property  ::getTag( ), PropertyPtr  ( new Property  ( ) ) );
	app->addTask( ViewerLive::getTag( ), ViewerLivePtr( new ViewerLive( ) ) );
	app->addTask( Sender    ::getTag( ), SenderPtr    ( new Sender    ( data ) ) );

}