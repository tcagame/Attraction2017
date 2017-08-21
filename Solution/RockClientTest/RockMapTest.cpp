#include "RockMapTest.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"

const Vector ENTRY_POS = Vector( 200, 0, 270 );
const double ENTRY_RADIUS = 40;

RockMapTest::RockMapTest( ) {
	_filenames = { };
	_filenames.push_back( "Resource/Rock/map/map01.mv1" );
	_filenames.push_back( "Resource/Rock/object/obj06/obj06.mv1" );
	_filename_col = "Resource/Rock/map/map01_col.mv1";
}


RockMapTest::~RockMapTest( ) {
}

std::vector< std::string > RockMapTest::getFilenames( ) const {
	return _filenames;
}

std::string RockMapTest::getFilenameCol( ) const {
	return _filename_col;
}

void RockMapTest::update( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		Vector pos = player->getPos( );
		if ( isNext( pos ) ) {
			unsigned int state = STATE_STREET_1;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_STATE, &state );
		}
	}
}

bool RockMapTest::isNext( const Vector& pos ) const {
	bool result = false;
	double length = ( pos - ENTRY_POS ).getLength( );
	if ( ENTRY_RADIUS > length ) {
		result = true;
	}
	return result;
}