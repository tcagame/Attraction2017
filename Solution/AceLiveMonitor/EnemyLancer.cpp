#include "EnemyLancer.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 2;
const int MAX_HP = 3;
const int MOVE_SPEED = -3;
const int RANGE = 150;

EnemyLancer::EnemyLancer( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
	setVec( Vector( MOVE_SPEED, 0 ) );
}

EnemyLancer::~EnemyLancer( ) {
}

void EnemyLancer::act( ) {
	Vector vec = getVec( );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		 PlayerPtr player = Family::getTask( )->getPlayer( i );
		 Vector diff = player->getPos( ) - getPos( );
		 if ( diff.getLength( ) < RANGE &&
			  player->getPos( ).x < getPos( ).x ) {
				vec.x = MOVE_SPEED * 3;
		 }
	}
	setVec( vec );
}

void EnemyLancer::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		140, 141, 142, 143, 144
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
