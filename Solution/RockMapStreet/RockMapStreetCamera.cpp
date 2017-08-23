#include "RockMapStreetCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const Vector INIT_POS = Vector( 0, 300, -450 ) * 2;
const Vector INIT_TARGET = Vector( 0, 60, 0 );


RockMapStreetCamera::RockMapStreetCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
}


RockMapStreetCamera::~RockMapStreetCamera( ) {
}
void RockMapStreetCamera::update( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	Vector target = RockFamily::getTask( )->getCameraPos( );
	Vector pos = getPos( ) + target - getTarget( );
	setPos( pos );
	setTarget( target );
	drawer->setCamera( pos, target );
}
