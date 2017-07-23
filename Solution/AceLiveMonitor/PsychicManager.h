#pragma once
#include "Psychic.h"
#include "Player.h"
#include "Psychic.h"
#include "smart_ptr.h"
#include <vector>

PTR( Psychic );
PTR( PsychicManager );

class PsychicManager {
public:
	PsychicManager( );
	virtual ~PsychicManager( );
	void shot( Vector pos, Player::DIR dir );
	void update( );
	PsychicPtr getPsychic( int index ) const;
	int getPsychicNum( ) const;
private:
	std::vector< PsychicPtr> _psychic_list;
};

