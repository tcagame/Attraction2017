#include "RockMapStreet.h"

const int STREET_MODEL_NUM = 3;


RockMapStreet::RockMapStreet( ) {
	_filenames = { };
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		char filename[ 256 ];
		sprintf_s( filename, "Resource/Rock/map/map02_0%d.mv1", i + 1 );
		_filenames.push_back( filename );
	}
}

RockMapStreet::~RockMapStreet( ) {
}

std::vector< std::string > RockMapStreet::getFilenames( ) const {
	return _filenames;
}

void RockMapStreet::update( ) {
}