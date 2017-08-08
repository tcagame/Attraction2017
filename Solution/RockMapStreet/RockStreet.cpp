#include "RockStreet.h"

const int STREET_MODEL_NUM = 3;


RockStreet::RockStreet( ) {
	_filenames = { };
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		char filename[ 256 ];
		sprintf_s( filename, "Resource/Rock/map/map02_0%d.mv1", i + 1 );
		_filenames.push_back( filename );
	}
}

RockStreet::~RockStreet( ) {
}

std::vector< std::string > RockStreet::getFilenames( ) const {
	return _filenames;
}

