#include "EnemyGhost.h"
#include "Family.h"

static const int WAIT_ANIM_TIME = 5;
static const int FADE_IN_TIME = WAIT_ANIM_TIME * 2;
static const int MAX_HP = 3;
static const int MOVE_SPEED = -3;
static const double ASCEND_SPEED = -0.1;

EnemyGhost::EnemyGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_act( ACTION_FADE_IN ),
_ascend_speed( 0 ) {
	setRadius( 36 );
	setVec( Vector ( MOVE_SPEED, MOVE_SPEED / 2 ) );
}

EnemyGhost::~EnemyGhost( ) {
}

void EnemyGhost::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
	{
		Vector vec = getVec( );
		int ascend_pos = ( int )Family::getTask( )->getCameraPos( ) + 150;
		if ( getPos( ).x < ascend_pos ) {
			vec.y += ASCEND_SPEED;
			setVec( vec );
		} else {
			setVec( vec );
		}
		break;
	}
	}
}

Chip EnemyGhost::getChip( ) const {
	Chip chip = Chip( );
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 8, 9, 10, 11, 12, 13 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 14, 15, 16, 17, 18 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	}
		break;
	}
	chip.ty = 11 * 64;
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