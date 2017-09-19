#include "RockEventStartFace.h"
#include "RockDollHouse.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int RADIUS = 32;
const int HEIGHT = 30;
const double ANIM_SPEED = 0.9;

RockEventStartFace::RockEventStartFace( const Vector pos ) :
RockEventCharacter( pos, DOLL_START, RADIUS, HEIGHT, false ) {

}


RockEventStartFace::~RockEventStartFace( ) {
}

void RockEventStartFace::act( ) {
	Vector near_distance( 800, 800, 800 );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( !player->isActive( ) || player->isBubble( ) ) {
			continue;
		}
		Vector dir = player->getPos( ) - getPos( );
		if ( near_distance.getLength( ) > dir.getLength( ) ) {
			 near_distance = dir;
		}
		setDir( near_distance );
	}
}

double RockEventStartFace::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}