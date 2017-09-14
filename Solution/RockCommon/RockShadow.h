#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "mathmatics.h"

PTR( RockShadow );
PTR( ModelMDL );

class RockShadow : public Task {
public:
	static std::string getTag( ) { return "SHADOW"; };
	static RockShadowPtr getTask( );
public:
	RockShadow( );
	virtual ~RockShadow( );
public:
	void update( );
	void reset( );
	void set( const Vector& pos, const double scale );
	int getSetNum( ) const;
	ModelMDLPtr getModel( int idx ) const;
private:
	static const int MAX_SHADOW_NUM = 100;
private:
	void createShadow( ModelMDLPtr model, const Vector& pos, const double scale );
	Vector getAdjustPos( const Vector& pos );
private:
	std::array< ModelMDLPtr, MAX_SHADOW_NUM > _models;
	int _set_num;
};

