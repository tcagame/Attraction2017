#include "Armoury.h"
#include "Shot.h"
#include "Application.h"
#include <assert.h>

ArmouryPtr Armoury::getTask( ) {
	return std::dynamic_pointer_cast< Armoury >( Application::getInstance( )->getTask( getTag( ) ) );
}

Armoury::Armoury( ) :
_shot_id( 0 ) {
}

Armoury::~Armoury( ) {
}

void Armoury::update( ) {
	std::array< ShotPtr, MAX_SHOT_NUM >::iterator ite = _shot_list.begin( );
	while ( ite != _shot_list.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}
		if ( ( *ite )->isFinish( ) ) {
			( *ite ) = ShotPtr( );
		} else {
			( *ite )->update( );
		}
		ite++;
	}
}

ShotConstPtr Armoury::getShot( int idx ) const {
	assert( idx < MAX_SHOT_NUM );
	assert( idx >= 0 );
	return _shot_list[ idx ];
}

int Armoury::getMaxShotNum( ) const {
	return MAX_SHOT_NUM;
}

void Armoury::add( ShotPtr shot ) {
	_shot_list[ _shot_id ] = shot;
	_shot_id++;
	_shot_id %= MAX_SHOT_NUM;
}

