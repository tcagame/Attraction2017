#include "EventTurtle.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int HEIGHT = 32;
const int RADIUS = 128;
const double ANIM_SPEED = 0.9;

EventTurtle::EventTurtle( const Vector& pos ) :
RockEventCharacter( pos, DOLL_TURTLE, RADIUS, HEIGHT, false ) {
}


EventTurtle::~EventTurtle( ) {
}

double EventTurtle::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void  EventTurtle::act( ) {
}
