#include "EventEnma.h"
#include "Family.h"
#include "Player.h"


const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventEnma::EventEnma( ) :
Event( EVENT_ENMA, DIR_RIGHT ),
_audience( false ) {
}


EventEnma::~EventEnma( ) {
}

void EventEnma::update( ) {
	// 運び終わったら、イベントへ
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( START_POS_X, START_POS_Y );
		}
	}
}

bool EventEnma::isJoining( ) const {
	return true;
}

void EventEnma::join( PLAYER target ) {
	//定員一名
	if ( _audience ) {
		return;
	}
	FamilyPtr family( Family::getTask( ) );
	family->getPlayer( target )->setActionEnteringSanzo( );
	start( );
	_audience = true;
}