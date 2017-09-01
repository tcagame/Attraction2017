#include "RockMapBossCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 400, 500, -1200 );
const Vector INIT_TARGET = Vector( 400, 125, 0 );
const Vector DIR = Vector( 0, 0.8, -1 ).normalize( );
const double LENGTH = 300;

RockMapBossCamera::RockMapBossCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
}

RockMapBossCamera::~RockMapBossCamera( ) {
}

void RockMapBossCamera::setCamera( ) {
	Vector target = RockFamily::getTask( )->getCameraPos( );
	if ( target.isOrijin( ) ) {
		setPos( INIT_POS );
		setTarget( INIT_TARGET );
	} else {
		Vector pos = target + DIR * LENGTH;
		setPos( pos );
		setTarget( target );
	}
}
