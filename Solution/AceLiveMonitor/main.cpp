#include "Application.h"
#include "Drawer.h"
#include "Device.h"
#include "ace_define.h"
#include "Family.h"
#include "Armoury.h"
#include "Viewer.h"


void main( ) {
	TaskPtr drawer( new Drawer( "../Resource/Ace" ) );
	TaskPtr device( new Device( ) );
	
	TaskPtr family = FamilyPtr( new Family( ) );
	TaskPtr armoury = ArmouryPtr( new Armoury( ) );
	TaskPtr viewer = ViewerPtr( new Viewer( ) );
	ApplicationPtr app( Application::getInstance( ) );
	app->setWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Device::getTag( ), device );
	app->addTask( Family::getTag( ), family );
	app->addTask( Armoury::getTag( ), armoury );
	app->addTask( Viewer::getTag( ), viewer );
}