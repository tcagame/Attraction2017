#pragma once
#include "mathmatics.h"
#include "Character.h"
#include <array>

PTR( Enemy );
PTR( Monmotaro );

class Player : public Character {
public:
	enum ACTION {
		ACTION_ENTRY,
		ACTION_CONTINUE,
		ACTION_WAIT,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_FLOAT,
		ACTION_ATTACK,
		ACTION_CHARGE,
		ACTION_OVER_CHARGE,
		ACTION_DAMEGE,
		ACTION_BLOW_AWAY,
		ACTION_DEAD,
		ACTION_CALL,
		MAX_ACTION,
	};
public:
	Player( PLAYER player, Vector pos );
	virtual ~Player( );
public:
	void act( );
	void updatetDevice( );
	int getDeviceId( ) const;
	void damage( int force );
	ACTION getAction( ) const;
	int getChargeCount( ) const;
	bool isOnHead( CharacterPtr target ) const;
	void bound( );
	void blowAway( );
	int getMoney( ) const;
	int getVirtue( ) const;
	void addMoney( int money );
	void pickUpVirtue( );
	void setSynchronousData( PLAYER player, int camera_pos ) const;
	bool isExist( ) const;
private:
	void actOnEntry( );
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
	void adjustToCamera( );
	void updateProgress( );
	void appear( );
private:
	enum ITEM {
		ITEM_DANGO,
		ITEM_HEART,
		ITEM_HYPERTROPHY,
		ITEM_SHORTENING,
		ITEM_WOOD,
		ITEM_FLAME,
		ITEM_MINERAL,
		MAX_ITEM,
	};
private:
	PLAYER _player;
	ACTION _action;
	int _device_id;
	int _money;
	int _virtue;
	int _over_charge_time;
	int _charge_count;
	int _unrivaled_count;
	int _progress_count;
	std::array< bool, MAX_ITEM > _item;
};

