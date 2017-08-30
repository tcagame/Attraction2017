#include "RockTheaterResult.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"

RockTheaterResult::RockTheaterResult( ) :
_play( true ) {
}


RockTheaterResult::~RockTheaterResult( ) {
}

void RockTheaterResult::initialize( ) {
	MoviePtr movie = Drawer::getTask( )->createMovie( "UI/ui_main_title_tall.mov" );
	setMovie( movie );
	playMovie( );
}

void RockTheaterResult::update( ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if( player->isActive( ) ) {
			stopMovie( );
			_play = false;
			return;
		}
	}
	if ( !_play ) {
		playMovie( );
	}
}
