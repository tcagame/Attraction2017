#include "EnemyArcherAttack.h"
#include "SynchronousData.h"

const int MAX_HP = 2;
const Vector MOVE_SPEED( -6, 0 );

EnemyArcherAttack::EnemyArcherAttack( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setVec( MOVE_SPEED );
}

EnemyArcherAttack::~EnemyArcherAttack( ) {
}

void EnemyArcherAttack::act( ) {
}

void EnemyArcherAttack::setSynchronousData( unsigned char type, int camera_pos ) const {
	
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
	data->addObject( area, type, 14, attribute, x, y );
}
