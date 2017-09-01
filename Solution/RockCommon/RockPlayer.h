#pragma once
#include "RockCharacter.h"
#include "smart_ptr.h"

PTR( Status );
PTR( RockAncestors );

class RockPlayer : public RockCharacter {
public:
	RockPlayer( StatusPtr status, const Vector& pos, int id, RockAncestorsPtr ancestors );
	virtual ~RockPlayer( );
public:
	bool isActive( ) const;
	void bound( );
	void damage( int force );
	void back( );
	void wish( );
	void resetBubble( );
	ModelMV1Ptr getModel( ) const;
	void resetPos( const Vector& pos );
	bool isDead( ) const;
	bool isBubble( ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_BUBBLE,
		ACTION_WAIT,
		ACTION_JUMP,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_CHARGE,
		ACTION_DEAD,
		ACTION_WISH
	};
private:
	void setAction( ACTION action );
	void actOnEntry( );
	void actOnWaiting( );
	void actOnJumping( );
	void actOnWalking( );
	void actOnAttacking( );
	void actOnCharging( );
	void actOnBraking( );
	void actOnDead( );
	void actOnWish( );
	void updateEffect( );
	void updeteState( );
private:
	StatusPtr _status;
	ACTION _action;
	int _id;
	int _attack_count;
	int _effect_handle;
	int _entry_count;
	RockAncestorsPtr _ancestors;
};

