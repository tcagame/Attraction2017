#include "NPCMiko.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 10;

NPCMiko::NPCMiko( const Vector& pos ) :
NPC( pos, BIG_CHAR_GRAPH_SIZE ) {
	_solt = false;
}


NPCMiko::~NPCMiko( ) {
}

void NPCMiko::act( ) {
}

void NPCMiko::startSolt( ) {
	_solt = true;
}

void NPCMiko::setSynchronousData( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3
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
	int change_anim = _solt ? 1 : 0;
	data->addObject( AREA_EVENT, SynchronousData::TYPE_LAKE, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] + ( 4 * change_anim ), attribute, x, y, getChipSize( ) );
	if ( _solt ) {
		data->addObject( AREA_EVENT, SynchronousData::TYPE_LAKE, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] + 8, attribute, x, y, getChipSize( ) );
	}
}