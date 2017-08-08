#include "RockMapTest.h"



RockMapTest::RockMapTest( ) {
	_filenames = { };
	_filenames.push_back( "Resource/Rock/map/map01.mv1" );
}


RockMapTest::~RockMapTest( ) {
}

std::vector< std::string > RockMapTest::getFilenames( ) const {
	return _filenames;
}


