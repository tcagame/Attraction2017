#include "EnemyHugDaemon.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int JUMP_POWER = -13;
const int RANGE = 150;
const int MOVE_SPEED = -2;

EnemyHugDaemon::EnemyHugDaemon( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
}


EnemyHugDaemon::~EnemyHugDaemon( ) {
}

void EnemyHugDaemon::act( ) {
	Vector vec = getVec( );
	vec.x = MOVE_SPEED;
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		 PlayerPtr player = Family::getTask( )->getPlayer( i );
		 Vector diff = player->getPos( ) - getPos( );
		 if ( diff.getLength( ) < RANGE &&
			  player->getPos( ).x < getPos( ).x &&
			  player->getPos( ).y < getPos( ).y &&
			  isStanding( ) ) {
				vec.y = JUMP_POWER;
		 }
	}
	setVec( vec );
}

void EnemyHugDaemon::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		227, 228, 229, 230, 231, 232, 233, 234, 235, 236
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