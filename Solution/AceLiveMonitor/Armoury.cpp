#include "Armoury.h"
#include "Shot.h"
#include "Application.h"

ArmouryPtr Armoury::getTask( ) {
	return std::dynamic_pointer_cast< Armoury >( Application::getInstance( )->getTask( getTag( ) ) );
}

Armoury::Armoury( ) {
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
		( *ite )->update( );
		ite++;
	}
}

ShotConstPtr Armoury::getShot( int idx ) const {
	return _shot_list[ idx ];
}

void Armoury::add( ShotPtr shot ) {
	for ( int i = 0; i < MAX_SHOT_NUM; i++ )  {
		if ( _shot_list[ i ] ) {
			continue;
		}

		_shot_list[ i ] = shot;
		break;
	}
}

