#include "Event.h"
#include "Family.h"
#include "Player.h"

Event::Event( EVENT type ) :
_type( type ) {
}


Event::~Event( ) {
}

EVENT Event::getType( ) const {
	return _type;
}

void Event::exit( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->getArea( ) == AREA_EVENT ) {
			player->leaveEvent( );
		}
	}
}