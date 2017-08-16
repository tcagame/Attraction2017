#pragma once
#include "mathmatics.h"
#include "ace_define.h"
#include "smart_ptr.h"

PTR( Character );

class Character {
public:
	enum STATE {
		STATE_MAIN,
		STATE_EVENT,
	};
public:
	Character( const Vector& pos, const int chip_size, const int hp, bool mass = true );
	virtual ~Character( );
public:
	Vector getVec( ) const;
	Vector getPos( ) const;
	void update( );
	virtual void damage( int force );
	virtual Chip getChip( ) const = 0;
	virtual Chip getChip2( ) const { return Chip( ); };
	bool isOverlapped( CharacterConstPtr target ) const;
	double getRadius( ) const;
	bool isFinished( ) const;
	STATE getState( ) const;
	void setState( STATE state );
	int getChipSize( ) const;
	int getHp( ) const;
protected:
	void setDir( DIR dir );
	DIR getDir( ) const;
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	bool isStanding( ) const;
	virtual void act( ) = 0;
	int getActCount( ) const;
	void setRadius( int radius );
	void setFinished( );
private:
	void updateDir( );
private:
	Vector _pos;
	Vector _vec;
	int _chip_size;
	int _hp;
	int _act_count;
	bool _mass;
	bool _standing;
	bool _finished;
	double _radius;
	DIR _dir;
	STATE _state;
};

