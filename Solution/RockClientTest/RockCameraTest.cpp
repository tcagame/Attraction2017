#include "RockCameraTest.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 0, 80, -180 );
const Vector DIR = Vector( 0, 0.8, -1 ).normalize( );
const double LENGTH = 300;

RockCameraTest::RockCameraTest( ) :
RockCamera( INIT_POS, Vector( ) ){
}


RockCameraTest::~RockCameraTest( ) {
}


void RockCameraTest::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	Vector target = RockFamily::getTask( )->getCameraPos( );
	if ( target.isOrijin( ) ) {
		return;
	}
	Vector pos = target + DIR * LENGTH;
	setPos( pos );
	setTarget( target );
	drawer->setCamera( pos, target );
}
