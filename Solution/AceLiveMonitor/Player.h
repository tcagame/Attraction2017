#pragma once
#include "mathmatics.h"
#include "Character.h"

PTR( Enemy );
PTR( Monmotaro );

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
		ACTION_CALL,
	};
public:
	Player( Vector pos );
	virtual ~Player( );
public:
	void act( );
	void setDeviceId( int id );
	int getDeviceId( ) const;
	void damage( int force );
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
	void setSynchronousData( PLAYER player, int camera_pos ) const;
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
	void actOnDead( );
	void actOnCall( );
	void updateState( );
	void setAction( ACTION action );
private:
	MonmotaroPtr _monmo;
	ACTION _action;
	int _id;
	int _money;
	int _toku;
	int _over_charge_time;
	int _charge_count;
	int _unrivaled_count;
};

