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
	Player( PLAYER player, Vector pos );
	virtual ~Player( );
public:
	void act( );
	void setDeviceId( int id );
	int getDeviceId( ) const;
	void damage( int force );
	ACTION getAction( ) const;
	int getChargeCount( ) const;
	bool isOnHead( CharacterPtr target ) const;
	void bound( );
	void blowAway( );
	int getMoney( ) const;
	int getVirtue( ) const;
	void pickUpMoney( int money );
	void pickUpVirtue( );
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
	PLAYER _player;
	ACTION _action;
	int _id;
	int _money;
	int _virtue;
	int _over_charge_time;
	int _charge_count;
	int _unrivaled_count;
};

