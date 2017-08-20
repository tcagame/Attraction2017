#include "EnemyWind.h"
#include "Drawer.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 10;
const int MAX_HP = 6;
const int MOVE_TIME = WAIT_ANIM_TIME * 17;
const int ANIM_LOOP_TIME = WAIT_ANIM_TIME * 24;
const int MOVE_SPEED = 8;

const int MAX_DESTINATION_POS = 8;
Vector DESTINATION_POS[ MAX_DESTINATION_POS ] = {
	Vector( ),
	Vector( 547, 71 ),
	Vector( 260, 62 ),
	Vector( 365, 86 ),
	Vector( 558, 75 ),
	Vector( 444, 82 ),
	Vector( 625, 73 ),
	Vector( 887, 21 ),
};

EnemyWind::EnemyWind( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP, false ),
_count( 0 ) {
	setRadius( 32 );
	DESTINATION_POS[ 0 ].y = pos.y;
	for ( int i = 0; i < MAX_DESTINATION_POS; i++ ) {
		DESTINATION_POS[ i ].x += pos.x;
	}
}


EnemyWind::~EnemyWind( ) {
}

void EnemyWind::act( ) {
	setForce( 0 );
	if ( ( getActCount( ) + WAIT_ANIM_TIME * 8 ) % ANIM_LOOP_TIME < MOVE_TIME ) {
		Vector dir( ( DESTINATION_POS[ _count + 1 ] - DESTINATION_POS[ _count ] ).normalize( ) );
		setVec( dir * MOVE_SPEED );
	}

	if ( getPos( ).y + getVec( ).y < 0 ) {
		Vector vec = getVec( );
		vec.y *= -1;
		setVec( vec );
	}
	if ( getPos( ).y + getVec( ).y > GRAPH_SIZE - 50 ) {
		Vector vec = getVec( );
		vec.y *= -1;
		DESTINATION_POS[ _count + 1 ].y -= 10;
		setVec( vec );
	}

	if ( ( getActCount( ) + WAIT_ANIM_TIME * 8 ) % ANIM_LOOP_TIME > MOVE_TIME ) {
		setVec( Vector( ) );
		setForce( 3 );
	}
	if ( !( getActCount( ) % ( WAIT_ANIM_TIME * 13 ) ) ) {
		_count = ( _count++ ) % MAX_DESTINATION_POS;
	}
}

Chip EnemyWind::getChip( ) const {
	const int ANIM[ ] = {
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21
	};
	const int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ( ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] % GRAPH_WIDTH_NUM ) * 128;
	chip.ty = ( ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] / GRAPH_WIDTH_NUM ) * 128;
	chip.size = getChipSize( );
	
	Vector pos = getPos( );
	DIR dir = getDir( );
	if ( dir == DIR_RIGHT ){
		chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 - chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	} else {
		chip.sx1 = ( int )pos.x - chip.size / 2;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 + chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	}
	return chip;
}

void EnemyWind::damage( int force ) {
	if ( force < 0 ) {
		Enemy::damage( force );
	}
	if ( getVec( ) != Vector( ) ) {
		return;
	}
	Enemy::damage( force );
}
