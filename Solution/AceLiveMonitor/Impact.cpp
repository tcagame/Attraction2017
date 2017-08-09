#include "Impact.h"

const int IMPACT_CHIP_SIZE = 128;
const int MAX_ANIM_COUNT = 30;
const int ANIM_WIDTH_NUM = 2;

Impact::Impact( const Vector& pos, Character::STATE state, int sprite_size ) :
_pos( pos ),
_anim_count( 0 ),
_state( state ),
_sprite_size( sprite_size ) {
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
	chip.sx1 = ( int )_pos.x - _sprite_size / 2;
	chip.sx2 = chip.sx1 + _sprite_size;
	chip.sy1 = ( int )_pos.y - _sprite_size;
	chip.sy2 = chip.sy1 + _sprite_size;
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

Character::STATE Impact::getState( ) const {
	return _state;
}
