#include "Impact.h"

const int IMPACT_CHIP_SIZE = 128;
const int MAX_ANIM_COUNT = 30;
const int ANIM_WIDTH_NUM = 2;

Impact::Impact( const Vector& pos ) :
_pos( pos ),
_anim_count( 0 ) {
}


Impact::~Impact( ) {
}

void Impact::update( ) {
	_anim_count++;
}

Chip Impact::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3
	};
	int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.sx1 = ( int )_pos.x - IMPACT_CHIP_SIZE / 2;
	chip.sx2 = chip.sx1 + IMPACT_CHIP_SIZE;
	chip.sy1 = ( int )_pos.y - IMPACT_CHIP_SIZE;
	chip.sy2 = chip.sy1 + IMPACT_CHIP_SIZE;
	int cx = ANIM[ ( _anim_count * anim_num ) / MAX_ANIM_COUNT ] % ANIM_WIDTH_NUM;
	int cy = ANIM[ ( _anim_count * anim_num ) / MAX_ANIM_COUNT ] / ANIM_WIDTH_NUM;
	chip.size = IMPACT_CHIP_SIZE;
	chip.tx = cx * chip.size;
	chip.ty = cy * chip.size;
	return chip;
}

bool Impact::isFinished( ) const {
	return ( _anim_count > MAX_ANIM_COUNT );
}