#include "Event.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const int OVERAREA = 1280 / 2 - 256;

Event::Event( EVENT type, DIR exit_dir ) :
_type( type ),
_exist_dir( exit_dir ),
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

void Event::escape( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->getArea( ) == AREA_STREET ) {
			continue;
		}
		int area = ( int )player->getPos( ).x - 640;
		if ( _exist_dir == DIR_LEFT ) {
			if ( area < -OVERAREA ) {
				player->leaveEvent( );
			}
		} else {
			if ( area > OVERAREA ) {
				player->leaveEvent( );
			}
		}
	}
	if ( !family->isExistOnEvent( ) ) {
		_exiting = true;
	}
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
		_fade_count++;
		if ( _fade_count >= 100 ) {
			_fade_count = 100;
		}
		break;
	}
	SynchronousData::getTask( )->setFade( _fade_count );
}

bool Event::isFinished( ) {
	return _fade_type == FADE_OUT && _fade_count >= 100;
}

Event::FADE Event::getFade( ) const {
	return _fade_type;
}
