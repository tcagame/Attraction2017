#include "Speaker.h"
#include "Application.h"
#include "Sound.h"
#include "Status.h"

SpeakerPtr Speaker::getTask( ) {
	return std::dynamic_pointer_cast< Speaker >( Application::getInstance( )->getTask( getTag( ) ) );
}

Speaker::Speaker( StatusPtr status ) :
_status( status ),
_normal_bgm( false ) {
}


Speaker::~Speaker( ) {
}

void Speaker::update( ) {
	SoundPtr sound = Sound::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _status->getPlayer( i ).area == AREA_RESULT ) {
			if ( _normal_bgm ) {
				sound->playBGM( "yokai_music_08.wav" );
				_normal_bgm = false;
				return;
			}
		}
	}

	// ’Êí‚É–ß‚·‚©‚Ì”»’f
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( _status->getPlayer( i ).area == AREA_RESULT ) {
			return;
		}
	}

	if ( !_normal_bgm ) {
		sound->playBGM( "yokai_music_12.wav" );
		_normal_bgm = true;
	}
	
}
