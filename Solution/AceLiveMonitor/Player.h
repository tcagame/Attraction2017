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
		ACTION_CHARGE,
		ACTION_OVER_CHARGE,
		ACTION_DAMEGE,
	};
public:
	Player( int player_id, Vector pos );
	virtual ~Player( );
public:
	void act( );
	void damage( int force );
	Chip getChip( ) const;
	ACTION getAction( ) const;
	int getChargeCount( ) const;
	Chip getChargeChip( ) const;
private:
	void actOnWaiting( );
	void actOnWalking( );
	void actOnBreaking( );
	void actOnFloating( );
	void actOnAttack( );
	void actOnCharge( );
	void actOnOverCharge( );
	void actOnCamera( );
	void actOnDamege( );
private:
	ACTION _action;
	int _id;
	int _charge_count;
	int _damege_count;
	int _over_charge_time;
};

