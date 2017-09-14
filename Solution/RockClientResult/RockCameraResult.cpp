#include "RockCameraResult.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 0, 200, -180 );
const Vector DIR = Vector( -5, 1, -1 ).normalize( );
const double LENGTH = 300;


RockCameraResult::RockCameraResult( ) :
RockCamera( INIT_POS, Vector( ) ){
}


RockCameraResult::~RockCameraResult( ) {
}


void RockCameraResult::setCamera( ) {
	Vector target = RockFamily::getTask( )->getCameraPos( );
	if ( target.isOrijin( ) ) {
		setPos( INIT_POS );
		setTarget( Vector( ) );
	} else {
		Vector pos = target + DIR * LENGTH;
		setPos( pos );
		setTarget( target );
	}
}