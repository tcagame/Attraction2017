#include "RockTheaterTest.h"
#include "Drawer.h"


RockTheaterTest::RockTheaterTest( ) {
}


RockTheaterTest::~RockTheaterTest( ) {
}

void RockTheaterTest::initialize( ) {
	MoviePtr movie = Drawer::getTask( )->createMovie( "UI/ui_main_title_tall.mov" );
	setMovie( movie );
	playMovie( );
}

void RockTheaterTest::update( ) {

}