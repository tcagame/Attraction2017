#include "NPCObaba.h"
#include "SynchronousData.h"

static const int TIME = 60;
static const int WAIT_ANIM_TIME = 10;

NPCObaba::NPCObaba( const Vector& pos ) :
NPC( pos, BIG_CHAR_GRAPH_SIZE ) {
	setVec( Vector( 1, 0 ) );
}


NPCObaba::~NPCObaba( ) {
}

void NPCObaba::act( ) {
	if ( !( getActCount( ) % TIME ) ) {
		setVec( getVec( ) * -1 );
	}
}

void NPCObaba::setSynchronousData( ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	unsigned char attribute = 0;

	int anim = 0;
	if ( getDir( ) == DIR_LEFT ) {
		const int ANIM[ ] = {
			18, 19
		};
		const int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	} else {
		const int ANIM[ ] = {
			16, 17
		};
		const int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( AREA_EVENT, SynchronousData::TYPE_NPC, anim, attribute, x, y, getChipSize( ) );
}