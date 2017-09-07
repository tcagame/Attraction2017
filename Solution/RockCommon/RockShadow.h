#pragma once
#include "Task.h"
#include <string>
#include <list>
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
	void set( const Vector& pos, const double scale, const bool adjust );
	std::list< ModelMDLPtr > getShadows( ) const;
	void clear( );
private:
	Vector getAdjustPos( const Vector& pos );
private:
	std::list< ModelMDLPtr > _models;
};

