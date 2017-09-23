#include "EventGamble.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 640;
const int START_POS_Y = 200;

EventGamble::EventGamble( ) :
Event( EVENT_GAMBLE, DIR_LEFT ),
_audience( false ) {
}


EventGamble::~EventGamble( ) {
}

void EventGamble::update( ) {
}

void EventGamble::join( PLAYER target ) {
	return; //‰c‹Æ’âŽ~
	//’èˆõˆê–¼
	if ( _audience ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
	start( );
	_audience = true;
}