#include "ItemMoney.h"
#include "SynchronousData.h"
#include "Sound.h"

const int WAIT_ANIM_TIME = 150;
const int MAX_ANIM_NUM = 2;

ItemMoney::ItemMoney( const Vector& pos, unsigned char type, AREA area ) :
Item( pos, area ),
_type( type ) {
}


ItemMoney::~ItemMoney( ) {
}

void ItemMoney::act( ) {
}

void ItemMoney::setSynchronousData( int camera_pos ) const {
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
	case OBJECT_MONEY_PURSE:
		pattern = 0;
		break;
	case OBJECT_MONEY_BAG:
		pattern = anim + 1;
		break;
	case OBJECT_MONEY_500:
		pattern = 3;
		break;
	case OBJECT_MONEY_1000:
		pattern = 4;
		break;
	case OBJECT_MONEY_5000:
		pattern = 5;
		break;
	case OBJECT_MONEY_10000:
		pattern = 6;
		break;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ITEM, pattern, attribute, x, y );
}

int ItemMoney::getValue( ) const {
	int value = 0;
	Sound::getTask( )->playSE( "yokai_voice_30.wav" );
	switch ( _type ) {
	case OBJECT_MONEY_PURSE:
		value = 100;
		break;
	case OBJECT_MONEY_BAG:
		value = 300;
		break;
	case OBJECT_MONEY_500:
		value = 500;
		break;
	case OBJECT_MONEY_1000:
		value = 1000;
		break;
	case OBJECT_MONEY_5000:
		value = 5000;
		break;
	case OBJECT_MONEY_10000:
		value = 10000;
		break;
	}
	return value;
}