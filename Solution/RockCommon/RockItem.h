#pragma once
#include "RockCharacter.h"
class RockItem : public RockCharacter {
public:
	RockItem( const Vector& pos, DOLL doll );
	virtual ~RockItem( );
public:
	void setRepop( bool repop );
	bool isRepop( ) const;
protected:
	void act( );
private:
	bool _repop;
};

