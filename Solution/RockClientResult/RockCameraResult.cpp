#include "RockCameraResult.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"

const Vector INIT_POS = Vector( 100, 80, -180 );
const Vector TARGET = Vector( 170, 250, 45 );
const Vector DIR = Vector( -1, -0.3, -0.3 ).normalize( );
const double LENGTH = 300;


RockCameraResult::RockCameraResult( ) :
RockCamera( INIT_POS, TARGET ){
}


RockCameraResult::~RockCameraResult( ) {
}


void RockCameraResult::setCamera( ) {
	Vector pos = TARGET + DIR * LENGTH;
	setPos( pos );
	setTarget( TARGET );
}