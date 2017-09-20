#pragma once
#include "RockCharacter.h"

class RockShot : public RockCharacter {
public:
	RockShot( const Vector& pos, const Vector& dir, const int power );
	virtual ~RockShot( );
public:
	double getAnimTime( ) const { return 0; };
	bool isFinished( ) const;
	void setFinished( );
	int getPower( ) const;
	int getEffectHandle( ) const;
	void stopEffect( );
protected:
	void setSize( double size );
	void setEffectHandle( int effect_handle );
	double getSize( );
	void setPower( int power );
private:
	int _effect_handle;
	int _power;
	double _size;
	bool _finished;
};

