#include "EnemyShishimai.h"
#include "Player.h"
#include "Family.h"

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
	for ( int i = 0; i < ACE_PLAYER_NUM - 1; i++ ) {
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

Chip EnemyShishimai::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7
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