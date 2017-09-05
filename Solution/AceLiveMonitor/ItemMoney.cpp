#include "ItemMoney.h"
#include "SynchronousData.h"
#include "Sound.h"

const int WAIT_ANIM_TIME = 150;
const int MAX_ANIM_NUM = 2;

ItemMoney::ItemMoney( const Vector& pos, TYPE type ) :
Item( pos ),
_type( type ) {
}


ItemMoney::~ItemMoney( ) {
}

void ItemMoney::act( ) {
}

void ItemMoney::setSynchronousData( unsigned char type, int camera_pos ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	int anim = getActCount( ) / WAIT_ANIM_TIME % MAX_ANIM_NUM;
	int pattern = -1;
	switch ( _type ) {
	case TYPE_PETTY:
		pattern = anim + 40;
		break;
	case TYPE_BAG:
		pattern = anim + 32;
		break;
	case TYPE_500:
		pattern = anim + 60;
		break;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, pattern, attribute, x, y );
}

int ItemMoney::getValue( ) const {
	int result = 0;
	Sound::getTask( )->playSE( "yokai_voice_30.wav" );
	switch ( _type ) {
	case TYPE_PETTY:
		result = 100;
		break;
	case TYPE_BAG:
		result = 200;
		break;
	case TYPE_500:
		result = 500;
		break;
	}
	return result;
}