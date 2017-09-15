#pragma once
#include "RockCharacter.h"
class RockCasket : public RockCharacter {
public:
	enum RESULT {
		RESULT_SUCCESS,
		RESULT_BAD
	};
public:
	RockCasket( const Vector& pos );
	virtual ~RockCasket( );
public:
	ModelMV1Ptr getModel( ) const;
	RESULT getOpenResult( ) const;
protected:
	void act( );
private:
	double _rot;
};

