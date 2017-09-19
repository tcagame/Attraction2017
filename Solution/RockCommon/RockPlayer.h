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
	bool wish( );
	void resetBubble( );
	ModelMV1Ptr getModel( ) const;
	void resetPos( const Vector& pos );
	bool isDead( ) const;
	bool isBubble( ) const;
	void setAdmissionPos( const Vector& camera_pos );
	int getId( ) const;
	void speedDown( );
protected:
	void act( );
	void updateInCamera( );
private:
	enum ACTION {
		ACTION_BUBBLE,
		ACTION_WAIT,
		ACTION_JUMP,
		ACTION_WALK,
		ACTION_BRAKE,
		ACTION_CHARGE,
		ACTION_BURST,
		ACTION_DEAD,
		ACTION_WISH
	};
private:
	void setAction( ACTION action );
	void actOnBubble( );
	void actOnWaiting( );
	void actOnJumping( );
	void actOnWalking( );
	void actOnAttacking( );
	void actOnCharging( );
	void actOnBurst( );
	void actOnBraking( );
	void actOnDead( );
	void actOnWish( );
	void updateEffect( );
	void updeteState( );
	void sendDamage( );
	void move( );
	Vector getApproachesVec( );
private:
	StatusPtr _status;
	ACTION _action;
	int _id;
	int _attack_count;
	int _bubble_count;
	int _damage;
	int _damage_count;
	int _interval;
	int _charge_effect_handle;
	int _speed_down_effect_handle;
	bool _continue;
	bool _speed_down;
	RockAncestorsPtr _ancestors;
};

