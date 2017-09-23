#include "Item.h"

const int NORMAL_COUNT = 120;//�A�C�e�����ʏ�ʂ葶�݂ł��鎞��
const int FLASH_COUNT = 60; //�A�C�e�����_�ł��鎞��

Item::Item( const Vector& pos, AREA area, int chip_size ) :
Character( pos, chip_size, 0, false ),
_phase( PHASE_NORMAL ) {
	setArea( area );
}

Item::~Item( ) {
}

void Item::setDrop( ) {
	setMass( true );
	setVec( Vector( 0, -6 ) );
}

void Item::updateDropItem( ) {
	if ( !isMass( ) ) {
		return;
	}
	switch ( _phase ) {
	case PHASE_NORMAL:
		if ( getActCount( ) > NORMAL_COUNT ) {
			_phase = PHASE_FLASH;
		}
		break;
	case PHASE_FLASH:
		if ( getActCount( ) > NORMAL_COUNT + FLASH_COUNT ) {
			_phase = PHASE_ERASE;
		}
		break;
	case PHASE_ERASE:
		break;
	}
}

bool Item::isFinished( ) const {
	return _phase == PHASE_ERASE;
}

Item::PHASE Item::getPhase( ) const {
	return _phase;
}

int Item::getFlashWaitTime( ) const {
	return 3;
}

