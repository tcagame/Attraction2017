#pragma once
#include "mathmatics.h"
#include "Character.h"

PTR( Enemy );

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
		ACTION_BLOW_AWAY,
		ACTION_DAED,
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
	bool isOnHead( EnemyPtr target ) const;
	void bound( );
	void blowAway( );
	int getMoneyNum( ) const;
	int getTokuNum( ) const;
	void pickUpMoney( int money );
	void pickUpToku( );
	void setSynchronousData( unsigned char type, int camera_pos ) const;
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
	void actOnBlowAway( );
	void updateState( );
	void setAction( ACTION action );
private:
	ACTION _action;
	int _id;
	int _money;
	int _toku;
	int _over_charge_time;
	int _charge_count;
	int _unrivaled_count;
};

