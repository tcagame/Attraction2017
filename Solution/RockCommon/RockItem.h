#pragma once
#include "RockCharacter.h"
class RockItem : public RockCharacter {
public:
	RockItem( const Vector& pos, DOLL doll );
	virtual ~RockItem( );
protected:
	void act( );
};

