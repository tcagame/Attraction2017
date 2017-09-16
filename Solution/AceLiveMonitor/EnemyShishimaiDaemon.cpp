#include "EnemyShishimaiDaemon.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int ESCAPE_RANGE = 150;
const int MOVE_SPEED = -4;

EnemyShishimaiDaemon::EnemyShishimaiDaemon( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_escape( false ),
_befor_pos( pos ) {
	setOverlappedRadius( 36 );
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyShishimaiDaemon::~EnemyShishimaiDaemon( ) {
}

void EnemyShishimaiDaemon::act( ) {
	FamilyPtr family( Family::getTask( ) );
	PlayerPtr near = family->getPlayer( 0 );
	for ( int i = 0; i < MAX_PLAYER - 1; i++ ) {
		PlayerPtr player = family->getPlayer( i + 1 );
		Vector diff_player = player->getPos( ) - getPos( );
		Vector diff_near = near->getPos( ) - getPos( );
		if ( diff_player.getLength2( ) < diff_near.getLength2( ) ) {
			near = player;
		}
	}

	if ( _escape && getPos( ) == _befor_pos && getDir( ) == DIR_RIGHT ) {
		setVec( Vector( MOVE_SPEED * 2, getVec( ).y ) );
	}
	if ( !_escape ) {
		Vector vec = getVec( );
		Vector diff_near = near->getPos( ) - getPos( );
		if ( diff_near.getLength( ) < ESCAPE_RANGE && near->getPos( ).x < getPos( ).x ) {
			vec.x *= -1;
			_escape = true;
		}
		setVec( vec );
	}
	_befor_pos = getPos( );
}

void EnemyShishimaiDaemon::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		289, 290, 291, 292, 293, 294
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
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
