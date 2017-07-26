#include "EnemyFaceAndHand.h"

const int ANIM_WAIT_TIME = 6;
const int FADE_IN_TIME = 15;

EnemyFaceAndHand::EnemyFaceAndHand( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_act( ACTION_FADE_IN ){
}


EnemyFaceAndHand::~EnemyFaceAndHand( ) {
}

Chip EnemyFaceAndHand::getChip( ) const {
	Chip chip = Chip( );
	int cx = 0;
	int cy = 7;
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 0, 1 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		cx = ANIM[ getActCount( ) / ANIM_WAIT_TIME % anim_size ];
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 2, 3 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		cx = ANIM[ getActCount( ) / ANIM_WAIT_TIME % anim_size ];
	}
		break;
	}
	chip.size = getChipSize( );
	chip.tx = cx * chip.size;
	chip.ty = cy * chip.size;
	Vector pos = getPos( );
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sy2 = chip.sy1 + chip.size; 
	if ( getDir( ) == DIR_LEFT ) {
		chip.sx1 = ( int )pos.x - chip.size / 2;
		chip.sx2 = chip.sx1 + chip.size;	
	} else {
		chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
		chip.sx2 = chip.sx1 - chip.size;
	}
	return chip;
}

void EnemyFaceAndHand::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
		break;
	}
}
