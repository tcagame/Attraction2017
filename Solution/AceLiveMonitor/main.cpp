#include "Application.h"
#include "Drawer.h"
#include "Device.h"
#include "ace_define.h"
#include "Family.h"
#include "Armoury.h"
#include "Viewer.h"
#include "Map.h"
#include "Military.h"

void main( ) {
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );

	app->addTask( Drawer::getTag( ), DrawerPtr( new Drawer( "../Resource/Ace" ) ) );
	app->addTask( Device::getTag( ), DevicePtr( new Device( ) ) );

	app->addTask( Map     ::getTag( ), MapPtr     ( new Map    ( ) ) );
	app->addTask( Family  ::getTag( ), FamilyPtr  ( new Family ( ) ) );
	app->addTask( Armoury ::getTag( ), ArmouryPtr ( new Armoury( ) ) );
	app->addTask( Military::getTag( ), MilitaryPtr( new Military( ) ) );
	app->addTask( Viewer  ::getTag( ), ViewerPtr  ( new Viewer ( ) ) );
}