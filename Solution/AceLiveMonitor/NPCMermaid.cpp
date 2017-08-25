#include "NPCMermaid.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 10;

NPCMermaid::NPCMermaid( const Vector& pos ) :
NPC( pos, BIG_CHAR_GRAPH_SIZE ) {
}


NPCMermaid::~NPCMermaid( ) {
}

void NPCMermaid::act( ) {
}

void NPCMermaid::setSynchronousData( ) const {
	const int ANIM[ ] = {
		40, 41, 42, 43
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