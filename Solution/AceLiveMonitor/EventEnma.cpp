#include "EventEnma.h"
#include "Family.h"
#include "Player.h"



EventEnma::EventEnma( ) :
Event( EVENT_ENMA, DIR_RIGHT ),
_audience( false ) {
}


EventEnma::~EventEnma( ) {
}

void EventEnma::update( ) {
}

bool EventEnma::isJoining( ) const {
	return false;
}

void EventEnma::join( PLAYER target ) {
	//’èˆõˆê–¼
	if ( _audience ) {
		return;
	}
	FamilyPtr family( Family::getTask( ) );
	family->getPlayer( target )->setActionEnteringSanzo( );
	_audience = true;
}