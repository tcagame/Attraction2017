#include "RockTheaterResult.h"
#include "Drawer.h"


RockTheaterResult::RockTheaterResult( ) {
}


RockTheaterResult::~RockTheaterResult( ) {
}

void RockTheaterResult::initialize( ) {
	MoviePtr movie = Drawer::getTask( )->createMovie( "UI/ui_main_title_tall.mov" );
	setMovie( movie );
	playMovie( );
}

void RockTheaterResult::update( ) {
}