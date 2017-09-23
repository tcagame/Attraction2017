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
		ACTION_CONTINUE_FADE,
		ACTION_WAIT,
		ACTION_WALK,
		ACTION_FLOAT,
		ACTION_ATTACK,
		ACTION_CHARGE,
		ACTION_OVER_CHARGE,
		ACTION_DAMEGE,
		ACTION_BLOW_AWAY,
		ACTION_DEAD,
		ACTION_CALL,
		ACTION_ENTERING_FADEOUT,
		ACTION_ENTERING_SANZO,
		ACTION_AUDIENCE,
		ACTION_ENDING,
		ACTION_OPENING,
		MAX_ACTION,
	};
	enum ITEM {
		ITEM_DANGO,
		ITEM_HEART,
		ITEM_HYPERTROPHY,
		ITEM_SHORTENING,
		ITEM_WOOD,
		ITEM_FLAME,
		ITEM_MINERAL,
		ITEM_BOX,
		MAX_ITEM,
	};
	enum MODE {
		MODE_NORMAL,
		MODE_ENMA,
		MODE_VIRTUE,
	};
	enum ENTER {
		ENTER_SANZO,
		ENTER_FADEOUT,
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
	bool pickUpVirtue( );
	void setSynchronousData( PLAYER player, int camera_pos ) const;
	bool isExist( ) const;
	void enterEvent( const Vector& pos, ENTER enter );
	void leaveEvent( );
	EVENT getOnEvent( ) const;
	void pickUpItem( ITEM item );
	bool isWearingItem( ITEM item ) const;
	MODE getMode( ) const;
	void autoMove( int target_x );
	bool isFinishedAutomoving( ) const;
	void audience( );
	void free( );
	void setModeVirtue( );
	void setActionEnding( );
	bool isLeaveAlone( ) const;
	void recoverPower( );
	bool isEntering( ) const;
private:
	void actOnEntry( );
	void actOnContinue( );
	void actOnContinueFade( );
	void actOnWaiting( );
	void actOnWalking( );
	void actOnFloating( );
	void actOnAttack( );
	void actOnCharge( );
	void actOnOverCharge( );
	void actOnCamera( );
	void actOnDamege( );
	void actOnBlowAway( );
	void actOnDead( );
	void actOnCall( );
	void actOnEnteringFadeOut( );
	void actOnEnteringSanzo( );
	void actOnAudience( );
	void actOnEnding( );
	void actOnOpening( );
	void setAction( ACTION action );
	void adjustToCamera( );
	void updateProgressBar( );
	void updateProgressEffect( );
	void appear( );
	void updateShowMoney( );
	void setProgressType( unsigned char type );
	void jump( );
	int getDeviceDirX( );
	int getDeviceDirY( );
	unsigned char getDevicePush( );
	unsigned char getDeviceButton( );
	void debugItem( );
	void checkSandwichedWall( );
private:
	PLAYER _player;
	ACTION _action;
	MODE _mode;
	int _auto_move_target_x;
	int _device_id;
	int _money;
	int _show_money;
	int _virtue;
	int _charge_count;
	int _unrivaled_count;
	int _cool_time;
	unsigned char _progress_type;
	int _progress_count;
	int _redo;
	int _jump_power;
	int _max_charge_phase_count;
	int _max_virtue;
	int _sandwiched_count;
	std::array< bool, MAX_ITEM > _item;
	Vector _entering_pos;
	bool _entering;
};

