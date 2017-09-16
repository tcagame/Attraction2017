#include "Event.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"

Event::Event( EVENT type ) :
_type( type ) {
}


Event::~Event( ) {
}

EVENT Event::getType( ) const {
	return _type;
}

void Event::reset( ) {
	// “GA‚m‚o‚bAƒAƒCƒeƒ€‚ğÁ‹
	Military::getTask( )->eraseEventEnemy( );
	Office::getTask( )->eraseEventNPC( );
	Storage::getTask( )->eraseEventItem( );
}

