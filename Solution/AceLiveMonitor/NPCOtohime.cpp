#include "NPCOtohime.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 7;

NPCOtohime::NPCOtohime( const Vector& pos ):
NPC( pos, BIG_CHAR_GRAPH_SIZE ) {
}


NPCOtohime::~NPCOtohime( ) {
}

void NPCOtohime::act( ) {
}

void NPCOtohime::setSynchronousData( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
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
	data->addObject( AREA_EVENT, SynchronousData::TYPE_RYUGU, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y, getChipSize( ) );
}
