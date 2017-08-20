#include "EnemyShishimaiDemon.h"
#include "Family.h"
#include "Player.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int ESCAPE_RANGE = 150;
const int MOVE_SPEED = -4;

EnemyShishimaiDemon::EnemyShishimaiDemon( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_escape( false ),
_befor_pos( pos ) {
	setRadius( 36 );
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyShishimaiDemon::~EnemyShishimaiDemon( ) {
}

void EnemyShishimaiDemon::act( ) {
	FamilyPtr family( Family::getTask( ) );
	PlayerPtr near = family->getPlayer( 0 );
	for ( int i = 0; i < ACE_PLAYER_NUM - 1; i++ ) {
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

Chip EnemyShishimaiDemon::getChip( ) const {
	const int ANIM[ ] = {
		8, 9, 10, 11, 12, 13
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 12 * 64;
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
