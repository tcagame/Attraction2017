#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "ModelMV1.h"
#include "define.h"

PTR( RockDollHouse );

class RockDollHouse : public Task {
public:
	static std::string getTag( ) { return "ROCKDOLLHOUSE"; };
	static RockDollHousePtr getTask( );
public:
	RockDollHouse( );
	virtual ~RockDollHouse( );
public:
	void initialize( );
	void update( );
	ModelMV1Ptr getModel( DOLL id ) const;
private:
	std::array< ModelMV1Ptr, MAX_DOLL > _dolls;
};

