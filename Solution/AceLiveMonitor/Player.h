#pragma once
#include "mathmatics.h"
#include "Character.h"

class Player : public Character {
public:
	enum ACTION {
		ACTION_WAIT,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_FLOAT,
		ACTION_ATTACK,
	};
public:
	Player( int player_id, Vector pos );
	virtual ~Player( );
public:
	void act( );
	ACTION getAction( ) const;
	int getActCount( ) const;
private:
	void actOnWaiting( );
	void actOnWalking( );
	void actOnBreaking( );
	void actOnFloating( );
	void actOnAttack( );
	void checkDir( );
private:
	int _act_count;
	ACTION _action;
	int _id;
};

