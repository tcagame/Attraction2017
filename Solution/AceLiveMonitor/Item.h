#pragma once
#include "Character.h"
PTR( Item );

class Item : public Character {
public:
	Item( const Vector& pos, AREA area, int chip_size = 32 );
	virtual ~Item( );
public:
	void updateDropItem( );
	void setDrop( );
	bool isFinished( ) const;
	virtual void setSynchronousData( int camera_pos ) const { };
protected:
	enum PHASE {
		PHASE_NORMAL,
		PHASE_FLASH,
		PHASE_ERASE,
	};
protected:
	PHASE getPhase( ) const;
	int getFlashWaitTime( ) const;
private:
	PHASE _phase;
};

