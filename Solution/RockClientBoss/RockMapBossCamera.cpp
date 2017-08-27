#include "RockMapBossCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( -1500, 1000, 1000 );
const Vector INIT_TARGET = Vector( 0, 60, 0 );
const Vector DIR = Vector( 0, 0.8, -1 ).normalize( );
const double LENGTH = 300;

RockMapBossCamera::RockMapBossCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
}

RockMapBossCamera::~RockMapBossCamera( ) {
}

void RockMapBossCamera::update( ) {
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
