#include "NPCAngel.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;


NPCAngel::NPCAngel( const Vector& pos ) :
NPC( pos, BIG_CHAR_GRAPH_SIZE ) {
}


NPCAngel::~NPCAngel( ) {
}

void NPCAngel::act( ) {
}

void NPCAngel::setSynchronousData( ) const {
	const int ANIM[ ] = {
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
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
