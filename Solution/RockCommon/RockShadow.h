#pragma once
#include "Task.h"
#include <string>
#include <vector>
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
	int create( const Vector& pos, const double scale );
	void set( const int idx, const Vector& pos, const double scale );
	std::vector< ModelMDLPtr > getShadows( ) const;
private:
	void createShadow( ModelMDLPtr model, const Vector& pos, const double scale );
	Vector getAdjustPos( const Vector& pos );
private:
	std::vector< ModelMDLPtr > _models;
};

