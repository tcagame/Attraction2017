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
	for ( int i = 0; i < _shot_list.size( ); i++ ) {
		_shot_list[ i ]->update( );
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

