#include "EnemyArcher.h"
#include "EnemyArcherAttack.h"
#include "Military.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 0;
const int MOVE_SPEED = -2;
const int MOVE_TIME = WAIT_ANIM_TIME * 12;
const int ANIM_LOOP_TIME = WAIT_ANIM_TIME * 21;
const int SHOT_TIMING = ( MOVE_TIME + WAIT_ANIM_TIME * 5 ) - 2;

EnemyArcher::EnemyArcher( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_act( ACTION_MOVE ) {
	setRadius( 36 );
}

EnemyArcher::~EnemyArcher( ) {
}

void EnemyArcher::act( ) {
	setVec( Vector( MOVE_SPEED, getVec( ).y ) );
	if ( ( getActCount( ) % ANIM_LOOP_TIME ) >= MOVE_TIME ) {
		setVec( Vector( ) );
	}
	if ( ( getActCount( ) % ANIM_LOOP_TIME ) == SHOT_TIMING ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyArcherAttack( getPos( ) + Vector( -11, -18, 0 ) ) ) );
	}
}

void EnemyArcher::setSynchronousData( unsigned char type, int camera_pos ) const {
	int ANIM[ ] = { /*move*/ 260, 261, 262, 261, 260, 261, 262, 261, 260, 261, 262, 261, /*shot*/ 263, 264, 265, 266, 267, 268, 269, 270, 271 };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_MAIN ) {
		x -= camera_pos;
		area = AREA_MAIN;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}

Chip EnemyArcher::getChip( ) const {
	return Chip( );
}
