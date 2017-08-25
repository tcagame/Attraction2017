#include "NPCShaker.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 10;

NPCShaker::NPCShaker( const Vector& pos ) :
NPC( pos, NORMAL_CHAR_GRAPH_SIZE ) {
}


NPCShaker::~NPCShaker( ) {
}

void NPCShaker::act( ) {
}

void NPCShaker::damage( int force ) {
	if ( force < 0 ) {
		Character::damage( force );
	}
}

void NPCShaker::setSynchronousData( ) const {
	const int ANIM[ ] = {
		16, 17, 18, 19, 20
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( AREA_EVENT, SynchronousData::TYPE_NPC, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y, getChipSize( ) );
}
