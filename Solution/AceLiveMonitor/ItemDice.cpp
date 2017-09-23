#include "ItemDice.h"
#include "SynchronousData.h"


ItemDice::ItemDice( const Vector& pos, AREA area ) :
Item( pos, area ),
_num( 0 ),
_stop( false ) {
}


ItemDice::~ItemDice( ) {
}


void ItemDice::setSynchronousData( int camera_pos ) const {
	if ( getPhase( ) == PHASE_FLASH ) {
		if ( getActCount( ) / getFlashWaitTime( ) % 2 == 0 ) {
			return;
		}
	}
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	int anim = _num;
	if ( _stop ) {
		anim += 7;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ITEM2, anim, attribute, x, y, 32 );
}

void ItemDice::act( ) {
	//–Ú‚ÌŒvŽZ‚ð‚·‚é
	if ( _stop ) {
		return;
	}
	_num = rand( ) % 14;
}

int ItemDice::getNum( ) const {
	return _num;
}

void ItemDice::stop( ) {
	_stop = true;
	_num %= 6 + 1;
}