#include "PsychicManager.h"

PsychicManager::PsychicManager( ) {
}


PsychicManager::~PsychicManager( ) {
}

void PsychicManager::update( ) {
	for ( int i = 0; i < _psychic_list.size( ); i++ ) {
		_psychic_list[ i ]->update( );
	}
}

PsychicPtr PsychicManager::getPsychic( int index ) const {
	return _psychic_list[ index ];
}

int PsychicManager::getPsychicNum( ) const {
	return _psychic_list.size( );
}

void PsychicManager::shot( Vector pos, Player::DIR dir ){
	PsychicPtr psychic = PsychicPtr( new Psychic( pos, dir ) );
	_psychic_list.push_back( psychic );
}

