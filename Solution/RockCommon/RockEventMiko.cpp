#include "RockEventMiko.h"
#include "RockPlayer.h"
#include "RockFamily.h"
#include "MessageSender.h"

const int RADIUS = 30;
const int HEIGHT = 30;

RockEventMiko::RockEventMiko( const Vector& pos ) :
RockEventCharacter( pos, DOLL_MIKO, RADIUS, HEIGHT, true ) {
}


RockEventMiko::~RockEventMiko( ) {
}

void RockEventMiko::act( ) {
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( isOverLapped( player ) ) {
			unsigned int item = ITEM_HEART;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_ITEM, &item );
		}
	}
}
