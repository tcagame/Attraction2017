#include "RockCameraTest.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 0, 80, -180 );

RockCameraTest::RockCameraTest( ) :
RockCamera( INIT_POS, Vector( ) ){
}


RockCameraTest::~RockCameraTest( ) {
}


void RockCameraTest::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	Vector target = RockFamily::getTask( )->getCameraPos( );
	Vector pos = getPos( ) + target - getTarget( );
	setPos( pos );
	setTarget( target );
	drawer->setCamera( pos, target );
}
