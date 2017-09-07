#include "EnemyShishimai.h"
#include "Player.h"
#include "Family.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_SPEED = -4;
const int RANGE = 100;
const int RANGE_SUB = 300;

EnemyShishimai::EnemyShishimai( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_origin_pos( pos ),
_attack( false ) {
	setRadius( 36 );
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyShishimai::~EnemyShishimai( ) {
}

void EnemyShishimai::act( ) {
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

	if ( !_attack ) {
		Vector vec = getVec( );
		Vector diff_near = near->getPos( ) - getPos( );
		if ( diff_near.getLength( ) < RANGE && near->getPos( ).x < getPos( ).x ) {
			vec.x *= -1;
		}
		if ( diff_near.getLength( ) > RANGE_SUB && getActCount( ) % 30 == 0 && getDir( ) == DIR_RIGHT ) {
			vec = Vector( MOVE_SPEED * 3, 0 );
			_attack = true;
		}
		setVec( vec );
	}
}

void EnemyShishimai::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		280, 281, 282, 283, 284, 285, 286, 287, 288
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