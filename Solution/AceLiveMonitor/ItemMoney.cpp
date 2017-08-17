#include "ItemMoney.h"

const int WAIT_ANIM_TIME = 150;
const int MAX_ANIM_NUM = 2;

ItemMoney::ItemMoney( const Vector& pos, TYPE type ) :
Item( pos ),
_type( type ) {
}


ItemMoney::~ItemMoney( ) {
}

Chip ItemMoney::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	int anim = getActCount( ) / WAIT_ANIM_TIME % MAX_ANIM_NUM;
	switch ( _type ) {
	case TYPE_PETTY:
		chip.tx = anim * chip.size;
		chip.ty = 164;
		break;
	case TYPE_BAG:
		chip.tx = anim * chip.size;
		chip.ty = 128;
		break;
	case TYPE_500:
		chip.tx = 128 + anim * chip.size;
		chip.ty = 228;
		break;
	}
	return chip;
}

void ItemMoney::act( ) {

}

int ItemMoney::getValue( ) const {
	int result = 0;
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