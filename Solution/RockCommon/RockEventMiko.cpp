#include "RockEventMiko.h"
#include "RockPlayer.h"
#include "RockFamily.h"
#include "MessageSender.h"
#include "RockStudio.h"
#include "Effect.h"
#include "RockOffice.h"
#include "Status.h"
#include "Sound.h"

const int RADIUS = 30;
const int HEIGHT = 30;
const int MAX_ERASE_COUNT = 50;

RockEventMiko::RockEventMiko( const Vector& pos, StatusPtr status ) :
RockEventCharacter( pos, DOLL_MIKO, RADIUS, HEIGHT, true ),
_status( status ),
_used( false ),
_erase_count( 0 ) {
}


RockEventMiko::~RockEventMiko( ) {
}

void RockEventMiko::act( ) {
	if ( _used ) {
		_erase_count++;
		return;
	}
	EffectPtr effect = Effect::getTask( );
	Vector pos = getPos( );
	pos.y += 50;
	pos.z -= 30;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( isOverLapped( player ) && !( _status->getPlayer( i ).item & ITEM_HEART ) ) {
			effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_MIKO ) ), pos );
			Sound::getTask( )->playSE( "yokai_se_05.wav" );
			unsigned char item = ITEM_HEART;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_ITEM, &item );
		}
		if ( _status->getPlayer( i ).item & ITEM_HEART ) {
			_used = true;
		}
	}
}

bool RockEventMiko::isFinished( ) const {
	return _erase_count > MAX_ERASE_COUNT;
}

