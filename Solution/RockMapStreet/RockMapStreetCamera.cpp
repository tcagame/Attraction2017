#include "RockMapStreetCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const Vector INIT_POS = Vector( 0, 500, -1000 );
const Vector INIT_TARGET = Vector( 0, 60, -500 );
const Vector DIR = Vector( 0, 0.8, -1 ).normalize( );
const double LENGTH = 300;


RockMapStreetCamera::RockMapStreetCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
}


RockMapStreetCamera::~RockMapStreetCamera( ) {
}

void RockMapStreetCamera::update( ) {
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
