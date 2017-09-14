#include "RockEventTurtle.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int HEIGHT = 16;
const int RADIUS = 64;
const double ANIM_SPEED = 0.9;

RockEventTurtle::RockEventTurtle( const Vector& pos ) :
RockEventCharacter( pos, DOLL_TURTLE, RADIUS, HEIGHT, false ) {
}


RockEventTurtle::~RockEventTurtle( ) {
}

double RockEventTurtle::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEventTurtle::act( ) {
}
