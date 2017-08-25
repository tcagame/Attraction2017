#pragma once
#include "RockCharacter.h"

class RockShot : public RockCharacter {
public:
	RockShot( const int id_, const Vector& pos, const Vector& dir, const int power );
	virtual ~RockShot( );
public:
	double getAnimTime( ) const;
	bool isBack( ) const;
	bool isFinished( ) const;
	void setBack( );
	void setFinished( );
	int getPower( );
	ModelMV1Ptr getModel( ) const;
protected:
	void act( );
private:
	void actOutBack( );
private:
	int _player_id;
	int _effect_handle;
	int _power;
	double _size = 1.0;
	bool _back;
	bool _finished;
	Vector _rotate = Vector( 0, 0, 0 );
};

