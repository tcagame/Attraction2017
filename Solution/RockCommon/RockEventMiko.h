#pragma once
#include "RockEventCharacter.h"
#include "Status.h"

PTR( Status );

class RockEventMiko : public RockEventCharacter {
public:
	RockEventMiko( const Vector& pos, StatusPtr status );
	virtual ~RockEventMiko( );
public:
	bool isFinished( ) const;
protected:
	void act( );
	double getAnimTime( ) const { return 0; };
private:
	StatusPtr _status;
	bool _used;
	int _erase_count;
};

