#include "Event.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

Event::Event( EVENT type ) :
_type( type ),
_fade_type( FADE_IN ),
_fade_count( 100 ),
_exiting( false ) {
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
	_exiting = true;
}

void Event::fade( ) {
	switch ( _fade_type ) {
	case FADE_IN:
		if ( _fade_count > 0 ) {
			_fade_count--;
		}
		if ( _exiting &&
			!Family::getTask( )->isExistOnEvent( ) &&
			 _type != EVENT_NONE ) {
			_fade_type = FADE_OUT;
			_fade_count = 0;
		}
		break;
	case FADE_OUT:
		if ( _fade_count < 100 ) {
			_fade_count++;
		}
		break;
	}
	SynchronousData::getTask( )->setFade( _fade_count );
}

bool Event::isFinished( ) {
	return _fade_count >= 100 && _fade_type == FADE_OUT;
}

Event::FADE Event::getFade( ) const {
	return _fade_type;
}
