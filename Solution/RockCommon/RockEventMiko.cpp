#include "RockEventMiko.h"
#include "RockPlayer.h"
#include "RockFamily.h"
#include "MessageSender.h"
#include "RockStudio.h"
#include "Effect.h"

const int RADIUS = 30;
const int HEIGHT = 30;

RockEventMiko::RockEventMiko( const Vector& pos ) :
RockEventCharacter( pos, DOLL_MIKO, RADIUS, HEIGHT, true ) {
}


RockEventMiko::~RockEventMiko( ) {
}

void RockEventMiko::act( ) {
	EffectPtr effect = Effect::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		Vector player_pos = player->getPos( );
		player_pos.y += 60;
		if ( isOverLapped( player ) ) {
			effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_MIKO ) ), player_pos );
			unsigned int item = ITEM_HEART;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_ITEM, &item );
		}
	}
}
