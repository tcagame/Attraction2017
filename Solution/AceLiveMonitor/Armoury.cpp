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
	std::vector< ShotPtr >::iterator ite = _shot_list.begin( );
	while ( ite != _shot_list.end( ) ) {
		if ( !( *ite ) ) {
			ite++;
			continue;
		}
		( *ite )->update( );
		ite++;
	}
}

ShotPtr Armoury::getShot( int index ) const {
	return _shot_list[ index ];
}

int Armoury::getShotNum( ) const {
	return ( int )_shot_list.size( );
}

void Armoury::shot( Vector pos, Player::DIR dir ){
	ShotPtr shot = ShotPtr( new Shot( pos, dir ) );
	_shot_list.push_back( shot );
}

