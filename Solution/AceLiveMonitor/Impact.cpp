#include "Impact.h"



Impact::Impact( const Vector& pos ) :
_pos( pos ),
_anim_count( 0 ) {
}


Impact::~Impact( ) {
}

void Impact::update( ) {

}

Chip Impact::getChip( ) const {
	Chip chip = Chip( );
	return chip;
}
